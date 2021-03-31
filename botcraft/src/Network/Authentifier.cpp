#include <picojson/picojson.h>
#include <asio.hpp>

#ifdef USE_ENCRYPTION
#include <asio/ssl.hpp>
#include <openssl/sha.h>
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "botcraft/Network/Authentifier.hpp"

namespace Botcraft
{
    const std::string Authentifier::auth_server_URL = "authserver.mojang.com";
    const std::string Authentifier::session_server_URL = "sessionserver.mojang.com";


    Authentifier::Authentifier()
    {

    }

    Authentifier::~Authentifier()
    {

    }

    bool Authentifier::AuthToken(const std::string& login, const std::string& password)
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        const std::string data = "{"
            "\"agent\":{\"name\":\"Minecraft\",\"version\":1},"
            "\"username\":\"" + login + "\","
            "\"password\":\"" + password + "\""
            "}";

        asio::io_context io_context;

        // Get a list of endpoints corresponding to the server name.
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(auth_server_URL, "https");

        asio::ssl::context ctx(asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();
        ctx.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::verify_none);

        asio::ssl::stream<asio::ip::tcp::socket> socket(io_context, ctx);
        socket.set_verify_mode(asio::ssl::verify_none);
        socket.set_verify_callback([](bool, asio::ssl::verify_context&) {return true; });
        asio::connect(socket.lowest_layer(), endpoints);
        socket.handshake(socket.client);
        socket.lowest_layer().set_option(asio::ip::tcp::no_delay(true));

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "POST /authenticate HTTP/1.1 \r\n";
        request_stream << "Host: " << auth_server_URL << "\r\n";
        request_stream << "User-Agent: C/1.0\r\n";
        request_stream << "Content-Type: application/json; charset=utf-8 \r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Content-Length: " << data.length() << "\r\n";
        request_stream << "Connection: close\r\n\r\n";
        request_stream << data;

        asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        asio::streambuf response;
        asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::stringstream output_string;
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);


        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cerr << "Invalid response during authentication\n";
            return false;
        }
        if (status_code != 200)
        {
            std::cerr << "Authentication response returned with status code " << status_code << "\n";
            return false;
        }

        // Read the response headers, which are terminated by a blank line.
        asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
        {

        }

        // Write whatever content we already have to output.
        if (response.size() > 0)
        {
            output_string << &response;
        }

        // Read until EOF, writing data to output as we go.
        asio::error_code error;
        while (asio::read(socket, response, asio::transfer_at_least(1), error))
        {
            output_string << &response;
        }
        if (error != asio::error::eof)
        {
            std::cerr << "Error trying to read authentication response" << std::endl;
            return false;
        }

        picojson::value raw_json;
        output_string >> raw_json;

        const picojson::value::object& json = raw_json.get<picojson::object>();

        if (!picojson::get_last_error().empty())
        {
            std::cerr << "Error trying to parse authentication response" << std::endl;
            return false;
        }

        if (json.find("error") != json.end())
        {
            std::cerr << "Error trying to authenticate: " << json.at("errorMessage").get<std::string>() << std::endl;
            return false;
        }

        if (json.find("accessToken") == json.end())
        {
            std::cerr << "Error trying to authenticate, no accessToken returned" << std::endl;
            return false;
        }
        access_token = json.find("accessToken")->second.get<std::string>();

        if (json.find("selectedProfile") == json.end())
        {
            std::cerr << "Error trying to authenticate, no selectedProfile item found" << std::endl;
            return false;
        }

        const picojson::object& profile = json.at("selectedProfile").get<picojson::object>();

        if (profile.find("name") == profile.end())
        {
            std::cerr << "Error trying to authenticate, no name in selected profile" << std::endl;
            return false;
        }

        player_display_name = profile.at("name").get<std::string>();
        player_uuid = profile.at("id").get<std::string>();

        return true;
#endif
    }

    bool Authentifier::AuthToken(const std::string& launcher_accounts_path)
    {

#ifndef USE_ENCRYPTION
        return false;
#else
        std::stringstream ss;
        std::ifstream file;

        file.open(launcher_accounts_path);
        if (!file.is_open())
        {
            std::cerr << "Error reading launcher accounts file at " << launcher_accounts_path << std::endl;
            return false;
        }

        ss << file.rdbuf();
        file.close();

        picojson::value raw_json;
        ss >> raw_json;
        std::string err = picojson::get_last_error();

        if (!err.empty())
        {
            std::cerr << "Error parsing launcher accounts file at " << launcher_accounts_path << "\n";
            std::cerr << err << std::endl;
            return false;
        }

        const picojson::value::object& json = raw_json.get<picojson::object>();

        if (!picojson::get_last_error().empty())
        {
            std::cerr << "Error trying to parse launcher accounts file at " << launcher_accounts_path << std::endl;
            return false;
        }

        if (json.find("accounts") == json.end() || json.find("activeAccountLocalId") == json.end())
        {
            std::cerr << "No active account in launcher accounts file at " << launcher_accounts_path << std::endl;
            return false;
        }

        const picojson::object& account = json.at("accounts").get<picojson::object>().at(json.at("activeAccountLocalId").get<std::string>()).get<picojson::object>();

        if (account.find("accessToken") == account.end())
        {
            std::cerr << "Error trying to authenticate, no accessToken found" << std::endl;
            return false;
        }
        access_token = account.find("accessToken")->second.get<std::string>();

        if (account.find("minecraftProfile") == account.end())
        {
            std::cerr << "Error trying to authenticate, no minecraftProfile item found" << std::endl;
            return false;
        }

        const picojson::object& profile = account.at("minecraftProfile").get<picojson::object>();

        if (profile.find("name") == profile.end())
        {
            std::cerr << "Error trying to authenticate, no name in profile" << std::endl;
            return false;
        }

        if (profile.find("id") == profile.end())
        {
            std::cerr << "Error trying to authenticate, no id in profile" << std::endl;
            return false;
        }

        player_display_name = profile.at("name").get<std::string>();
        player_uuid = profile.at("id").get<std::string>();

        return true;
#endif
    }

    bool Authentifier::JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& public_key)
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        if (player_uuid.empty())
        {
            std::cerr << "Error, trying to join a server before authentication" << std::endl;
            return false;
        }

        SHA_CTX sha_context;
        SHA1_Init(&sha_context);

        SHA1_Update(&sha_context, server_id.c_str(), server_id.length());
        SHA1_Update(&sha_context, shared_secret.data(), shared_secret.size());
        SHA1_Update(&sha_context, public_key.data(), public_key.size());

        std::vector<unsigned char> digest(SHA_DIGEST_LENGTH);
        SHA1_Final(digest.data(), &sha_context);
        
        // Compute minecraft special hexdigest (see https://wiki.vg/Protocol_Encryption#Client)

        bool is_negative = digest[0] & (1 << 7);

        // Take two complement
        if (is_negative)
        {
            // Revert bits
            for (int i = 0; i < digest.size(); ++i)
            {
                digest[i] = ~digest[i];
            }

            // add 1
            int position = digest.size() - 1;
            while (digest[position] == 255 && position > 0)
            {
                digest[position] = 0;
                position -= 1;
            }
            digest[position] += 1;
        }

        // Get hex representation
        std::stringstream ss;
        for (int i = 0; i < digest.size(); ++i)
        {
            ss << std::hex << std::setfill('0') << std::setw(2) << (int)(digest[i] & 0xFF);
        }

        std::string server_hash = ss.str();
        // Remove leading 0
        int start = server_hash.find_first_not_of('0');
        if (start != std::string::npos)
        {
            server_hash = server_hash.substr(start);
        }
        else
        {
            server_hash = "";
        }

        if (is_negative)
        {
            server_hash = "-" + server_hash;
        }

        // Prepare the data to send to the server
        const std::string data = "{"
            "\"accessToken\":\"" + access_token + "\","
            "\"selectedProfile\":\"" + player_uuid + "\","
            "\"serverId\":\"" + server_hash +
            "\"}";

        asio::io_context io_context;

        // Get a list of endpoints corresponding to the server name.
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(session_server_URL, "https");

        asio::ssl::context ctx(asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();
        ctx.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::verify_none);

        asio::ssl::stream<asio::ip::tcp::socket> socket(io_context, ctx);
        socket.set_verify_mode(asio::ssl::verify_none);
        socket.set_verify_callback([](bool, asio::ssl::verify_context&) {return true; });
        asio::connect(socket.lowest_layer(), endpoints);
        socket.handshake(socket.client);
        socket.lowest_layer().set_option(asio::ip::tcp::no_delay(true));

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "POST /session/minecraft/join HTTP/1.1 \r\n";
        request_stream << "Host: " << session_server_URL << "\r\n";
        request_stream << "User-Agent: C/1.0\r\n";
        request_stream << "Content-Type: application/json; charset=utf-8 \r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Content-Length: " << data.length() << "\r\n";
        request_stream << "Connection: close\r\n\r\n";
        request_stream << data;

        asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        asio::streambuf response;
        asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::stringstream output_string;
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cerr << "Invalid response during server join\n";
            return false;
        }
        if (status_code != 204)
        {
            std::cerr << "Response returned with status code " << status_code << "(" << status_message << ") during server join\n";
            std::cerr << "If you tried to connect with the json file, restart your official MC launcher to refresh the access token and then retry." << std::endl;
            return false;
        }

        return true;
#endif
    }

    const std::string& Authentifier::GetPlayerDisplayName() const
    {
        return player_display_name;
    }
}