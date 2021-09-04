#include <nlohmann/json.hpp>
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


        unsigned int status_code;
        std::string status_message;

        const std::string output_string = SendPostRequest(auth_server_URL, "/authenticate", data, status_code, status_message);

        if (status_code != 200)
        {
            std::cerr << "Error during authentication, returned status code " << status_code << "(" << status_message << ")\n";
            return false;
        }

        nlohmann::json json;
        try
        {
            json = nlohmann::json::parse(output_string);
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "Error trying to parse authentication response: " << e.what() << std::endl;
            return false;
        }

        if (json.contains("error"))
        {
            std::cerr << "Error trying to authenticate: " << json["errorMessage"].get<std::string>() << std::endl;
            return false;
        }

        if (!json.contains("accessToken"))
        {
            std::cerr << "Error trying to authenticate, no accessToken returned" << std::endl;
            return false;
        }
        access_token = json["accessToken"].get<std::string>();

        if (!json.contains("selectedProfile"))
        {
            std::cerr << "Error trying to authenticate, no selectedProfile item found" << std::endl;
            return false;
        }

        const nlohmann::json& profile = json.at("selectedProfile");

        if (!profile.contains("name"))
        {
            std::cerr << "Error trying to authenticate, no name in selected profile" << std::endl;
            return false;
        }

        if (!profile.contains("id"))
        {
            std::cerr << "Error trying to authenticate, no id in selected profile" << std::endl;
            return false;
        }

        player_display_name = profile["name"].get<std::string>();
        player_uuid = profile["id"].get<std::string>();

        return true;
#endif
    }

    bool Authentifier::AuthToken(const std::string& launcher_accounts_path)
    {

#ifndef USE_ENCRYPTION
        return false;
#else
        std::ifstream file;

        file.open(launcher_accounts_path);
        if (!file.is_open())
        {
            std::cerr << "Error reading launcher accounts file at " << launcher_accounts_path << std::endl;
            return false;
        }

        nlohmann::json json;
        try
        {
            file >> json;
        }
        catch (const nlohmann::json::exception& e)
        {
            std::cerr << "Error parsing launcher accounts file at " << launcher_accounts_path << "\n";
            std::cerr << e.what() << std::endl;
            return false;
        }
        file.close();

        if (!json.contains("accounts") || !json.contains("activeAccountLocalId"))
        {
            std::cerr << "No active account in launcher accounts file at " << launcher_accounts_path << std::endl;
            return false;
        }

        if (!json.contains("mojangClientToken"))
        {
            std::cerr << "No mojangClientToken in launcher accounts file at " << launcher_accounts_path << std::endl;
            return false;
        }

        const std::string client_token = json["mojangClientToken"].get<std::string>();

        nlohmann::json& account = json["accounts"][json["activeAccountLocalId"].get<std::string>()];

        if (!account.contains("accessToken"))
        {
            std::cerr << "Error trying to authenticate, no accessToken found" << std::endl;
            return false;
        }
        access_token = account["accessToken"].get<std::string>();

        if (!account.contains("minecraftProfile"))
        {
            std::cerr << "Error trying to authenticate, no minecraftProfile item found" << std::endl;
            return false;
        }

        nlohmann::json& profile = account["minecraftProfile"];

        if (!profile.contains("name"))
        {
            std::cerr << "Error trying to authenticate, no name in profile" << std::endl;
            return false;
        }

        if (!profile.contains("id"))
        {
            std::cerr << "Error trying to authenticate, no id in profile" << std::endl;
            return false;
        }

        player_display_name = profile["name"].get<std::string>();
        player_uuid = profile["id"].get<std::string>();

        // Trying to validate the token
        unsigned int validation_status_code;
        std::string validation_status_message;
        const std::string validation_response = SendPostRequest(auth_server_URL, "/validate",
            "{\"accessToken\":\"" + access_token + "\"}", validation_status_code, validation_status_message);

        if (validation_status_code != 204)
        {
            std::cout << "Token needs to be refreshed" << std::endl;

            // Refresh token

            unsigned int refresh_status_code;
            std::string refresh_status_message;
            const std::string refresh_response = SendPostRequest(auth_server_URL, "/refresh",
                "{\"accessToken\":\"" + access_token + "\",\"clientToken\":\"" + client_token + "\"}", refresh_status_code, refresh_status_message);

            if (refresh_status_code != 200)
            {
                std::cerr << "Error refreshing the token, status code: " << refresh_status_code << " (" << refresh_status_message << ")" << std::endl;
                return false;
            }

            nlohmann::json refresh_json;

            try
            {
                refresh_json = nlohmann::json::parse(refresh_response);
            }
            catch (const nlohmann::json::exception& e)
            {
                std::cerr << "Error trying to parse refresh response: " << e.what() << std::endl;
                return false;
            }

            if (!refresh_json.contains("accessToken"))
            {
                std::cerr << "Error trying to get refreshed token, no accessToken field found in response" << std::endl;
                return false;
            }
            access_token = refresh_json["accessToken"].get<std::string>();

            std::cout << "Token refreshed, saving new one into launcher file..." << std::endl;
            // We need to update the refresh token in the launcher file
            // for the next time
            account["accessToken"] = access_token;

            std::ofstream json_account_file;
            json_account_file.open(launcher_accounts_path);
            json_account_file << json.dump(4);
            json_account_file.close();
        }
        else
        {
            std::cout << "Token is valid, no need to refresh it." << std::endl;
        }

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

        unsigned int status_code;
        std::string status_message;

        SendPostRequest(session_server_URL, "/session/minecraft/join", data, status_code, status_message);

        if (status_code != 204)
        {
            std::cerr << "Response returned with status code " << status_code << "(" << status_message << ") during server join\n";
            return false;
        }

        return true;
#endif
    }

    const std::string& Authentifier::GetPlayerDisplayName() const
    {
        return player_display_name;
    }

    const std::string Authentifier::SendPostRequest(const std::string& host, const std::string& endpoint, const std::string& data, unsigned int& status_code, std::string& status_message)
    {
        asio::io_context io_context;

        // Get a list of endpoints corresponding to the server name.
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, "https");

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
        request_stream << "POST "<< endpoint << " HTTP/1.1 \r\n";
        request_stream << "Host: " << host << "\r\n";
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
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        response_stream >> status_code;
        std::getline(response_stream, status_message);


        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cerr << "Invalid response during POST\n";
            return "";
        }

        // Empty response
        if (status_code == 204)
        {
            return "";
        }

        // Read the response headers, which are terminated by a blank line.
        asio::read_until(socket, response, "\r\n\r\n");

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
        {

        }

        // Write whatever content we already have to output.
        std::stringstream output_string;
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
            std::cerr << "Error trying to read POST response (" << error << ")" << std::endl;
            return "";
        }

        return output_string.str();
    }
}