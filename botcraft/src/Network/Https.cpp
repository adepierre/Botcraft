#ifdef USE_ENCRYPTION

#include "botcraft/Network/Https.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <asio/connect.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/read.hpp>
#include <asio/read_until.hpp>
#include <asio/ssl.hpp>
#include <asio/streambuf.hpp>
#include <openssl/x509.h>

#include <algorithm>
#include <sstream>
#include <stdexcept>

#if defined(_WIN32)
#include <wincrypt.h>
#include <windows.h>
// wincrypt.h #defines names that clash with OpenSSL's, so undo them
#undef X509_NAME
#undef X509_EXTENSIONS
#undef X509_CERT_PAIR
#undef PKCS7_ISSUER_AND_SERIAL
#undef PKCS7_SIGNER_INFO
#undef OCSP_REQUEST
#undef OCSP_RESPONSE
#elif defined(__APPLE__)
#include <Security/Security.h>
#include <CoreFoundation/CoreFoundation.h>
#endif


namespace Botcraft
{
    namespace
    {
        void AddDERCert(X509_STORE* store, const unsigned char* data, const long len)
        {
            X509* x509 = d2i_X509(nullptr, &data, len);
            if (x509 != nullptr)
            {
                X509_STORE_add_cert(store, x509);
                X509_free(x509);
            }
        }

        void LoadSystemCertificates(asio::ssl::context& ctx)
        {
            ctx.set_default_verify_paths();

#ifdef _WIN32
            X509_STORE* store = SSL_CTX_get_cert_store(ctx.native_handle());
            for (const char* name : { "ROOT", "CA" })
            {
                HCERTSTORE hStore = CertOpenSystemStoreA(0, name);
                if (!hStore)
                {
                    continue;
                }
                PCCERT_CONTEXT cert = nullptr;
                while ((cert = CertEnumCertificatesInStore(hStore, cert)) != nullptr)
                {
                    AddDERCert(store, cert->pbCertEncoded, cert->cbCertEncoded);
                }

                CertCloseStore(hStore, 0);
            }
#elif defined __APPLE__
            X509_STORE* store = SSL_CTX_get_cert_store(ctx.native_handle());
            CFArrayRef certs = nullptr;
            if (SecTrustCopyAnchorCertificates(&certs) == errSecSuccess && certs)
            {
                for (CFIndex i = 0; i < CFArrayGetCount(certs); ++i)
                {
                    auto cert = (SecCertificateRef)CFArrayGetValueAtIndex(certs, i);
                    CFDataRef der = SecCertificateCopyData(cert);
                    if (der)
                    {
                        AddDERCert(store, CFDataGetBytePtr(der), CFDataGetLength(der));
                        CFRelease(der);
                    }
                }
                CFRelease(certs);
            }
#else
            for (const char* path : {"/etc/ssl/certs/ca-certificates.crt", "/etc/pki/tls/certs/ca-bundle.crt", "/etc/ssl/ca-bundle.pem", "/etc/ssl/cert.pem" })
            {
                asio::error_code ec;
                ctx.load_verify_file(path, ec);
            }
#endif
        }

        WebRequestResponse WebRequest(
            const std::string& host,
            const std::string& raw_request
        )
        {
            asio::io_context io_context;

            // Get a list of endpoints corresponding to the server name.
            asio::ip::tcp::resolver resolver(io_context);
            asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, "https");

            // Create a permanent context with system certificates loaded
            static asio::ssl::context ctx = []() {
                asio::ssl::context c(asio::ssl::context::tls_client);
                c.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::no_sslv2 | asio::ssl::context::no_sslv3);
                LoadSystemCertificates(c);
                return c;
            }();

            asio::ssl::stream<asio::ip::tcp::socket> socket(io_context, ctx);
            socket.set_verify_mode(asio::ssl::verify_none);
            socket.set_verify_callback(asio::ssl::host_name_verification(host));
            SSL_set_tlsext_host_name(socket.native_handle(), host.c_str());
            asio::connect(socket.lowest_layer(), endpoints);
            asio::error_code ec{};
            socket.handshake(socket.client, ec);
            if (ec)
            {
                LOG_ERROR("Error while performing Web SSL handshake: " << ec << "(" << ec.message() << ")");
                return WebRequestResponse{
                    ProtocolCraft::Json::Value(),
                    418, // "I'm a teapot"
                    ec.message()
                };
            }
            socket.lowest_layer().set_option(asio::ip::tcp::no_delay(true));

            // Send the request
            asio::streambuf request;
            std::ostream request_stream(&request);
            request_stream << raw_request;

            asio::write(socket, request);

            WebRequestResponse web_response;

            // Read the response status line. The response streambuf will automatically
            // grow to accommodate the entire line. The growth may be limited by passing
            // a maximum size to the streambuf constructor.
            asio::streambuf response;
            asio::read_until(socket, response, "\r\n");

            // Check that response is OK.
            std::istream response_stream(&response);
            std::string http_version;
            response_stream >> http_version;
            response_stream >> web_response.status_code;
            std::getline(response_stream, web_response.status_message);

            // Remove any \r in status message
            web_response.status_message.erase(std::remove(web_response.status_message.begin(), web_response.status_message.end(), '\r'),
                web_response.status_message.end());

            if (!response_stream || http_version.substr(0, 5) != "HTTP/")
            {
                LOG_ERROR("Invalid response during web request");
                web_response.response = {};
                return web_response;
            }

            // Empty response
            if (web_response.status_code == 204)
            {
                web_response.response = {};
                return web_response;
            }

            // Read the response headers, which are terminated by a blank line.
            asio::read_until(socket, response, "\r\n\r\n");

            // Process the response headers.
            long long int data_length = -1;
            bool chunked = false;
            std::string header;
            while (std::getline(response_stream, header) && header != "\r")
            {
                // Remove trailing \r
                if (!header.empty() && header.back() == '\r')
                {
                    header.pop_back();
                }

                if (header.find("Content-Length: ") == 0)
                {
                    data_length = std::stoll(header.substr(16));
                }
                else if (header.find("Transfer-Encoding:") == 0 && header.find("chunked") != std::string::npos)
                {
                    chunked = true;
                }
            }

            // Write whatever content we already have to output.
            std::stringstream output_stringstream;
            if (response.size() > 0)
            {
                output_stringstream << &response;
            }

            // Read until EOF, writing data to output as we go.
            asio::error_code error;
            while (asio::read(socket, response, asio::transfer_at_least(1), error))
            {
                output_stringstream << &response;
            }
            const std::string raw_body = output_stringstream.str();

            if (error != asio::error::eof && (data_length < 0 || raw_body.size() != static_cast<size_t>(data_length)))
            {
                LOG_ERROR("Error trying to read web request response, Error:\n " << error);
                web_response.response = {};
                return web_response;
            }

            if (chunked)
            {
                std::string decoded_body;
                bool decode_ok = false;
                size_t pos = 0;

                while (pos < raw_body.size())
                {
                    const size_t line_end = raw_body.find("\r\n", pos);
                    if (line_end == std::string::npos)
                    {
                        // This means the response is probably malformed
                        break;
                    }

                    std::string size_line = raw_body.substr(pos, line_end - pos);
                    const size_t semicolon = size_line.find(";");
                    if (semicolon != std::string::npos)
                    {
                        size_line.resize(semicolon);
                    }

                    const size_t chunk_size = std::stoull(size_line, nullptr, 16);

                    pos = line_end + 2;
                    if (chunk_size == 0)
                    {
                        decode_ok = true;
                        break;
                    }

                    if (pos + chunk_size > raw_body.size())
                    {
                        break;
                    }

                    decoded_body.append(raw_body, pos, chunk_size);
                    // Skip chunk data + "\r\n"
                    pos += chunk_size + 2;
                }

                if (!decode_ok)
                {
                    LOG_ERROR("Malformed chunked web request response");
                    web_response.response = {};
                    return web_response;
                }

                web_response.response = ProtocolCraft::Json::Parse(decoded_body, true);
            }
            else
            {
                web_response.response = ProtocolCraft::Json::Parse(raw_body, true);
            }

            return web_response;
        }
    }

    WebRequestResponse POSTRequest(
        const std::string& host, const std::string& endpoint,
        const std::string& content_type, const std::string& accept,
        const std::string& authorization, const std::string& data
    )
    {
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        std::string raw_request = "";
        raw_request += "POST " + endpoint + " HTTP/1.1 \r\n";
        raw_request += "Host: " + host + "\r\n";
        raw_request += "User-Agent: C/1.0\r\n";
        raw_request += "Content-Type: " + content_type + " \r\n";
        raw_request += "Accept: " + accept + "\r\n";
        if (!authorization.empty())
        {
            raw_request += "Authorization: " + authorization + "\r\n";
        }
        raw_request += "Content-Length: " + std::to_string(data.length()) + "\r\n";
        raw_request += "Connection: close\r\n\r\n";
        raw_request += data;

        return WebRequest(host, raw_request);
    }

    WebRequestResponse GETRequest(
        const std::string& host,
        const std::string& endpoint,
        const std::string& authorization)
    {
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        std::string raw_request = "";
        raw_request += "GET " + endpoint + " HTTP/1.1 \r\n";
        raw_request += "Host: " + host + "\r\n";
        if (!authorization.empty())
        {
            raw_request += "Authorization: " + authorization + "\r\n";
        }
        raw_request += "User-Agent: C/1.0\r\n";
        raw_request += "Connection: close\r\n\r\n";

        return WebRequest(host, raw_request);
    }

    ProtocolCraft::Json::Value CheckJsonResponse(
        const WebRequestResponse& response,
        const std::string& s,
        const std::vector<std::string>& fields,
        const unsigned int expected_status
    )
    {
        if (response.status_code != expected_status)
        {
            throw std::runtime_error("Status " + std::to_string(response.status_code) + " (" + response.status_message + ") during " + s + ":\n" + response.response.Dump(4));
        }
        for (const std::string& f : fields)
        {
            if (!response.response.contains(f))
            {
                throw std::runtime_error("No " + f + " in " + s + " response");
            }
        }
        return response.response;
    }
}
#endif // USE_ENCRYPTION
