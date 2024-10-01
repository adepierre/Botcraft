//
// Created by ws01 on 24-9-29.
//

#include "botcraft/Network/Yggdrasil_Authentifier.h"
#include <asio/ssl.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/connect.hpp>
#include <asio/streambuf.hpp>
#include <asio/read_until.hpp>
#include <asio/read.hpp>
#include <regex>
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    Botcraft::Yggdrasil_Authentifier::Yggdrasil_Authentifier(const std::string &url, const std::string &email,
                                                             const std::string &password)
    {
        this->email = email;
        this->password = password;
        this->yggdrasil_rul = url;

        std::regex url_pattern(R"(^(https?|ftp)://([^:/]+)(?::(\d+))?(/.*)?$)");
        std::smatch url_parts;
        if (std::regex_match(url, url_parts, url_pattern))
        {
            std::string protocol = url_parts[1];
            std::string host = url_parts[2];
            yggdrasil_port = url_parts[3];

            int default_port = (protocol == "https") ? 443 : 80;
            std::string effective_port = (yggdrasil_port.empty()) ? std::to_string(default_port) : yggdrasil_port;

            this->yggdrasil_port = effective_port;
            this->yggdrasil_host = host;
        }
    }

    const bool Botcraft::Yggdrasil_Authentifier::AuthMicrosoft(const std::string &login)
    {
        const Json::Value cached = GetCachedCredentials(login);
        if (!cached.contains("mc_token") || !cached["mc_token"].is_string() || !cached.contains("expires_date") ||
            !cached["expires_date"].is_number() || !cached.contains("name") || !cached["name"].is_string() ||
            !cached.contains("id") || !cached["id"].is_string())
        {
            LOG_WARNING("Missing or malformed cached credentials account, starting auth flow...");
            if (!AuthenticateToken())
            {
                return false;
            }
            UpdateUUIDBytes();
            LOG_INFO("Authentication successful");
            return true;
        }
        mc_access_token = cached["mc_token"].get_string();
        player_display_name = cached["name"].get_string();
        mc_player_uuid = cached["id"].get_string();
        if (ValidateToken())
        {
            UpdateUUIDBytes();
            LOG_INFO("Cached token account still valid.");
            return true;
        }

        if (password.empty())
        {
            LOG_INFO("Invalid token, trying to refresh token...");
            if (!RefreshToken())
            {
                return false;
            }
            LOG_INFO("Refresh token successful");
            UpdateUUIDBytes();
        }
        else
        {
            LOG_INFO("Invalid token, trying to starting auth flow...");
            if (!AuthenticateToken())
            {
                return false;
            }
            LOG_INFO("Authentication successful");
            UpdateUUIDBytes();
        }

        return true;
    }

    bool Yggdrasil_Authentifier::AuthenticateToken()
    {
        Json::Value request_data;
        request_data["username"] = email;
        request_data["password"] = password;
        request_data["requestUser"] = false;
        Json::Value agent;
        agent["name"] = "Minecraft";
        agent["version"] = 1;
        request_data["agent"] = agent;

        auto post_response =
            POSTRequest(yggdrasil_host, "/api/yggdrasil/authserver/authenticate", "application/json; charset=utf-8",
                        "*/*", "",
                        request_data.Dump());
        if (post_response.status_code != 200)
        {
            LOG_ERROR("Authentication failed. host:" << yggdrasil_host << " json:" << request_data.Dump());
            return false;
        }
        UpdateCached(email, post_response.response);

        return true;
    }

    bool Yggdrasil_Authentifier::RefreshToken()
    {
        Json::Value request_data;
        request_data["accessToken"] = mc_access_token;
        request_data["requestUser"] = false;

        auto post_response =
            POSTRequest(yggdrasil_host, "/api/yggdrasil/authserver/refresh", "application/json", "*/*", "",
                        request_data.Dump());
        if (post_response.status_code != 200)
        {
            LOG_ERROR(
                "RefreshToken failed. status_code:" << post_response.status_code << " json:" << post_response.response.
                Dump());
            return false;
        }
        UpdateCached(email, post_response.response);

        return true;
    }

    bool Yggdrasil_Authentifier::ValidateToken()
    {
        Json::Value request_data;
        request_data["accessToken"] = mc_access_token;

        auto post_response =
            POSTRequest(yggdrasil_host, "/api/yggdrasil/authserver/validate", "application/json", "*/*", "",
                        request_data.Dump());
        if (post_response.status_code != 204)
        {
            return false;
        }

        return true;
    }

    const bool Botcraft::Yggdrasil_Authentifier::JoinServer(const std::string &server_id,
                                                            const std::vector<unsigned char> &shared_secret,
                                                            const std::vector<unsigned char> &public_key) const
    {
        return Authentifier::JoinServer(server_id, shared_secret, public_key);
    }

    std::string extractSubstring(const std::string &str, char startChar, char endChar)
    {
        size_t startPos = str.find(startChar);
        if (startPos == std::string::npos)
        {
            return "";
        }

        size_t endPos = str.rfind(endChar);
        if (endPos == std::string::npos || endPos <= startPos)
        {
            return "";
        }

        return str.substr(startPos, endPos - startPos + 1);
    }

    const WebRequestResponse Yggdrasil_Authentifier::WebRequest(const std::string &host,
                                                                const std::string &raw_request) const
    {
        asio::io_context io_context;

        // Get a list of endpoints corresponding to the server name.
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, yggdrasil_port);

        asio::ssl::context ctx(asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();
        ctx.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::verify_none);

        asio::ssl::stream<asio::ip::tcp::socket> socket(io_context, ctx);
        socket.set_verify_mode(asio::ssl::verify_none);
        socket.set_verify_callback([](bool, asio::ssl::verify_context &) { return true; });
        SSL_set_tlsext_host_name(socket.native_handle(), host.c_str());
        asio::connect(socket.lowest_layer(), endpoints);
        socket.handshake(socket.client);
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
        web_response.status_message.erase(
            std::remove(web_response.status_message.begin(), web_response.status_message.end(), '\r'),
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
        std::string header;
        long long int data_length = -1;
        while (std::getline(response_stream, header) && header != "\r")
        {
            if (header.find("Content-Length: ") == 0)
            {
                data_length = std::stoll(header.substr(16));
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
        std::string raw_response = output_stringstream.str();
        raw_response = extractSubstring(raw_response, '{', '}');

        if (error != asio::error::eof)
        {
            LOG_ERROR("Error trying to read web request response, Error:\n " << error);
            web_response.response = {};
        }
        else
        {
            web_response.response = Json::Parse(raw_response);
        }

        return web_response;
    }

    void Yggdrasil_Authentifier::UpdateCached(const std::string &login, const ProtocolCraft::Json::Value &response)
    {
        const Json::Value &selected = response["selectedProfile"];

        auto time =
            std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
        UpdateCachedMCToken(login, response["accessToken"].get_string(), 259200 + time);
        UpdateCachedMCProfile(login, selected["name"].get_string(), selected["id"].get_string());

        mc_access_token = response["accessToken"].get_string();
        player_display_name = selected["name"].get_string();
        mc_player_uuid = selected["id"].get_string();
    }
} // namespace Botcraft
