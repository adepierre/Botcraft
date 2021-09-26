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
    const std::string Authentifier::msa_credentials_path = "botcraft_msa_credentials.json";
    const std::string Authentifier::botcraft_app_id = "a0ad834d-e78a-4881-87f6-390aa0f4b283";


    Authentifier::Authentifier()
    {

    }

    Authentifier::~Authentifier()
    {

    }

    const bool Authentifier::AuthMojang(const std::string& login, const std::string& password)
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        std::cout << "Sending credentials to Mojang authentication server..." << std::endl;

        const nlohmann::json data = {
            { 
                "agent", {
                    { "name", "Minecraft" },
                    { "version", 1 }
                }
            },
            { "username", login },
            { "password", password }
        };

        const WebRequestResponse post_response = POSTRequest("authserver.mojang.com", "/authenticate", "application/json; charset=utf-8", "*/*", data.dump());

        if (post_response.status_code != 200)
        {
            std::cerr << "Error during authentication, returned status code " << post_response.status_code << " (" << post_response.status_message << ")" << std::endl;
            return false;
        }

        const nlohmann::json& response = post_response.response;
        
        if (response.contains("error"))
        {
            std::cerr << "Error trying to authenticate: " << response["errorMessage"].get<std::string>() << std::endl;
            return false;
        }

        if (!response.contains("accessToken"))
        {
            std::cerr << "Error trying to authenticate, no accessToken returned" << std::endl;
            return false;
        }

        if (!response.contains("selectedProfile"))
        {
            std::cerr << "Error trying to authenticate, no selectedProfile item found" << std::endl;
            return false;
        }

        const nlohmann::json& profile = response.at("selectedProfile");

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

        mc_access_token = response["accessToken"].get<std::string>();
        player_display_name = profile["name"].get<std::string>();
        mc_player_uuid = profile["id"].get<std::string>();
        
        std::cout << "Authentication completed!" << std::endl;

        return true;
#endif
    }

    const bool Authentifier::AuthMicrosoft()
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        // This auth flow is directly inspired from https://github.com/maxsupermanhd/go-mc-ms-auth
        std::cout << "Trying to get Microsoft access token..." << std::endl;
        const std::string msa_token = GetMSAToken();
        if (msa_token.empty())
        {
            std::cerr << "Unable to get a microsoft auth token" << std::endl;
            return false;
        }
        std::cout << "Microsoft access token obtained!" << std::endl;


        std::cout << "Trying to get XBL token..." << std::endl;
        const std::string xbl_token = GetXBLToken(msa_token);
        if (xbl_token.empty())
        {
            std::cerr << "Unable to get a XBL token" << std::endl;
            return false;
        }
        std::cout << "XBL token obtained!" << std::endl;


        std::cout << "Trying to get XSTS token..." << std::endl;
        const auto [xsts_token, xsts_userhash] = GetXSTSToken(xbl_token);
        if (xsts_token.empty())
        {
            std::cerr << "Unable to get a XSTS token" << std::endl;
            return false;
        }
        std::cout << "XSTS token obtained!" << std::endl;


        std::cout << "Trying to get MC token..." << std::endl;
        mc_access_token = GetMCToken(xsts_token, xsts_userhash);
        if (mc_access_token.empty())
        {
            std::cerr << "Unable to get a MC token" << std::endl;
            return false;
        }
        std::cout << "MC token obtained! Almost there..." << std::endl;


        // We assume you're using an account owning minecraft so
        // we don't check (and also a bit because it's complicated)
        // If you don't, Botcraft won't work on online mode.
        // But you can buy yourself a copy of the game: 
        // https://www.minecraft.net/get-minecraft
        std::cout << "Assuming the account owns Minecraft..." << std::endl;


        std::cout << "Trying to get MC profile..." << std::endl;
        std::tie(mc_player_uuid, player_display_name) = GetMCProfile(mc_access_token);
        if (mc_player_uuid.empty())
        {
            std::cerr << "Unable to get a MC profile" << std::endl;
            return false;
        }
        std::cout << "MC profile obtained!" << std::endl;

        std::cout << "Authentication completed!" << std::endl;

        return true;
#endif
    }

    const bool Authentifier::JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& public_key) const
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        if (mc_player_uuid.empty())
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
        const nlohmann::json data = {
            { "accessToken", mc_access_token },
            { "selectedProfile", mc_player_uuid },
            { "serverId", server_hash}
        };

        const WebRequestResponse post_response = POSTRequest("sessionserver.mojang.com", "/session/minecraft/join", "application/json; charset=utf-8", "*/*", data.dump());

        if (post_response.status_code != 204)
        {
            std::cerr << "Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during server join" << std::endl;
            return false;
        }

        return true;
#endif
    }

    const std::string& Authentifier::GetPlayerDisplayName() const
    {
        return player_display_name;
    }

#ifdef USE_ENCRYPTION
    const std::string Authentifier::GetMSAToken() const
    {
        // Check if we have some cached credentials
        std::ifstream msa_file(msa_credentials_path);

        // If we don't, start the auth process to get credentials
        if (!msa_file.good())
        {
            return MSAAuthDeviceFlow();
        }

        // If we have a cache file check if the token needs to be refreshed
        nlohmann::json cached;
        msa_file >> cached;
        msa_file.close();

        // If this token is expired, we need to refresh it
        if (cached.contains("expires_date") && cached["expires_date"].get<long long int>() < std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count())
        {
            std::cout << "Refreshing Microsoft token..." << std::endl;
            std::string refresh_data;
            refresh_data += "client_id=" + botcraft_app_id;
            refresh_data += "&refresh_token=" + cached["refresh_token"].get<std::string>();
            refresh_data += "&grant_type=refresh_token";
            refresh_data += "&redirect_uri=https://login.microsoftonline.com/common/oauth2/nativeclient";

            const WebRequestResponse post_response = POSTRequest("login.live.com", "/oauth20_token.srf",
                "application/x-www-form-urlencoded", "*/*", refresh_data);

            // If refresh fails, remove the cache
            // file and restart the whole auth flow
            if (post_response.status_code != 200)
            {
                std::cerr << "Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during microsoft token refresh" << std::endl;
                std::remove(msa_credentials_path.c_str());
                std::cout << "Failed to refresh token, starting Microsoft authentication process..." << std::endl;
                return MSAAuthDeviceFlow();
            }
            const nlohmann::json& response = post_response.response;

            if (!response.contains("expires_in"))
            {
                std::cerr << "Error trying to refresh microsoft token, no expires_in in response" << std::endl;
                return "";
            }
            if (!response.contains("refresh_token"))
            {
                std::cerr << "Error trying to refresh microsoft token, no refresh_token in response" << std::endl;
                return "";
            }
            if (!response.contains("access_token"))
            {
                std::cerr << "Error trying to refresh microsoft token, no access_token in response" << std::endl;
                return "";
            }

            cached["expires_date"] = response["expires_in"].get<long long int>() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            cached["refresh_token"] = response["refresh_token"];
            cached["access_token"] = response["access_token"];

            // Store the new credentials in the cache file
            std::ofstream cached_file(msa_credentials_path);
            cached_file << std::setw(4) << cached;

            std::cout << "Cached Microsoft token refreshed" << std::endl;

            return response["access_token"].get<std::string>();
        }

        if (!cached.contains("access_token"))
        {
            std::cerr << "Error trying to get cached microsoft token, no access_token in " << msa_credentials_path << std::endl;
            return "";
        }

        std::cout << "Microsoft token obtained from " << msa_credentials_path << std::endl;

        return cached["access_token"].get<std::string>();
    }

    const std::string Authentifier::MSAAuthDeviceFlow() const
    {
        std::string auth_data = "";
        auth_data += "client_id=" + botcraft_app_id;
        auth_data += "&scope=XboxLive.signin%20offline_access";

        const WebRequestResponse post_response = POSTRequest("login.microsoftonline.com", "/consumers/oauth2/v2.0/devicecode",
            "application/x-www-form-urlencoded", "*/*", auth_data);

        if (post_response.status_code != 200)
        {
            std::cerr << "Response returned with status code " << post_response.status_code << " ("
                << post_response.status_message << ") during microsoft authentification" << std::endl;
            return "";
        }

        const nlohmann::json& auth_response = post_response.response;

        if (!auth_response.contains("interval"))
        {
            std::cerr << "Error trying to get microsoft token, no interval in authentication response" << std::endl;
            return "";
        }

        if (!auth_response.contains("message"))
        {
            std::cerr << "Error trying to get microsoft token, no message in authentication response" << std::endl;
            return "";
        }

        if (!auth_response.contains("device_code"))
        {
            std::cerr << "Error trying to get microsoft token, no device_code in authentication response" << std::endl;
            return "";
        }

        // Display the instructions the user has to follow to authenticate
        std::cout << auth_response["message"].get<std::string>() << std::endl;

        const long long int pool_interval = auth_response["interval"];
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(pool_interval + 1));

            std::string check_auth_status_data;
            check_auth_status_data += "client_id=" + botcraft_app_id;
            check_auth_status_data += "&scope=XboxLive.signin%20offline_access";
            check_auth_status_data += "&grant_type=urn:ietf:params:oauth:grant-type:device_code";
            check_auth_status_data += "&device_code=" + auth_response["device_code"].get<std::string>();

            const WebRequestResponse post_response = POSTRequest("login.microsoftonline.com", "/consumers/oauth2/v2.0/token",
                "application/x-www-form-urlencoded", "*/*", check_auth_status_data);

            const nlohmann::json& status_response = post_response.response;

            if (post_response.status_code == 400)
            {
                if (!status_response.contains("error"))
                {
                    std::cerr << "Unknown error happened during microsoft device authentication process" << std::endl;
                    return "";
                }

                const std::string error = status_response["error"];

                if (error == "authorization_pending")
                {
                    continue;
                }
                else if (error == "authorization_declined")
                {
                    std::cerr << "User declined authorization during microsoft device authentication check" << std::endl;
                    return "";
                }
                else if (error == "expired_token")
                {
                    std::cerr << "User took too long to perform device authentication, aborting" << std::endl;
                    return "";
                }
                else if (error == "invalid_grant")
                {
                    if (!status_response.contains("error_description"))
                    {
                        std::cerr << "While waiting for microsoft device authentication, token got invalidated (no further information)" << std::endl;
                    }
                    else
                    {
                        std::cerr << "While waiting for microsoft device authentication, token got invalidated: " << status_response["error_description"] << std::endl;
                    }

                    return "";
                }
            }
            else if (post_response.status_code == 200)
            {
                if (!status_response.contains("expires_in"))
                {
                    std::cerr << "Error trying to get microsoft token, no expires_in in device authentication status response" << std::endl;
                    return "";
                }

                if (!status_response.contains("refresh_token"))
                {
                    std::cerr << "Error trying to get microsoft token, no refresh_token in device authentication status response" << std::endl;
                    return "";
                }

                if (!status_response.contains("access_token"))
                {
                    std::cerr << "Error trying to get microsoft token, no access_token in device authentication status response" << std::endl;
                    return "";
                }

                nlohmann::json credentials;
                credentials["expires_date"] = status_response["expires_in"].get<long long int>() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                credentials["refresh_token"] = status_response["refresh_token"];
                credentials["access_token"] = status_response["access_token"];

                std::ofstream cached_file(msa_credentials_path);
                cached_file << std::setw(4) << credentials;

                std::cout << "Newly obtained Microsoft token stored in " << msa_credentials_path << std::endl;

                return status_response["access_token"].get<std::string>();
            }
            else
            {
                std::cerr << "Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during microsoft device authentification check" << std::endl;
                return "";
            }
        }
    }

    const std::string Authentifier::GetXBLToken(const std::string& msa_token) const
    {
        nlohmann::json request_data = {
            { "Properties", {
                    {"AuthMethod", "RPS"},
                    {"SiteName", "user.auth.xboxlive.com"},
                    {"RpsTicket", "d=" + msa_token}
                }
            },
            { "RelyingParty", "http://auth.xboxlive.com"},
            { "TokenType", "JWT"}
        };

        const WebRequestResponse post_response = POSTRequest("user.auth.xboxlive.com", "/user/authenticate",
            "application/json", "application/json", request_data.dump());

        if (post_response.status_code != 200)
        {
            std::cerr << "Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during XBL authentication" << std::endl;
            return "";
        }

        const nlohmann::json& response = post_response.response;

        if (!response.contains("Token"))
        {
            std::cerr << "Error trying to get XBL token, no Token in authentication response" << std::endl;
            return "";
        }

        return response["Token"].get<std::string>();
    }

    const std::pair<std::string, std::string> Authentifier::GetXSTSToken(const std::string& xbl_token) const
    {
        nlohmann::json request_data = {
            { "Properties", {
                    {"SandboxId", "RETAIL"},
                    {"UserTokens", { xbl_token } }
                }
            },
            { "RelyingParty", "rp://api.minecraftservices.com/"},
            { "TokenType", "JWT"}
        };

        const WebRequestResponse post_response = POSTRequest("xsts.auth.xboxlive.com", "/xsts/authorize",
            "application/json", "application/json", request_data.dump());

        if (post_response.status_code != 200)
        {
            std::cerr << "Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during XSTS authentication" << std::endl;
            return { "", "" };
        }

        const nlohmann::json& response = post_response.response;

        if (!response.contains("Token"))
        {
            std::cerr << "Error trying to get XSTS token, no Token in authentication response" << std::endl;
            return { "", "" };
        }

        if (!response.contains("DisplayClaims") || !response["DisplayClaims"].contains("xui")
            || !response["DisplayClaims"]["xui"].is_array() || response["DisplayClaims"]["xui"].size() < 1
            || !response["DisplayClaims"]["xui"][0].contains("uhs"))
        {
            std::cerr << "Error trying to get XSTS token, no DisplayClaims/xui/0/uhs in authentication response" << std::endl;
            return { "", "" };
        }

        return { response["Token"], response["DisplayClaims"]["xui"][0]["uhs"] };
    }

    const std::string Authentifier::GetMCToken(const std::string& xsts_token, const std::string& user_hash) const
    {
        nlohmann::json request_data = {
            { "identityToken", "XBL3.0 x=" + user_hash + ";" + xsts_token }
        };

        const WebRequestResponse post_response = POSTRequest("api.minecraftservices.com", "/authentication/login_with_xbox",
            "application/json", "application/json", request_data.dump());

        if (post_response.status_code != 200)
        {
            std::cerr << "Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during MC authentication" << std::endl;
            return "";
        }

        const nlohmann::json& response = post_response.response;

        if (!response.contains("access_token"))
        {
            std::cerr << "Error trying to get MC token, no access_token in authentication response" << std::endl;
            return "";
        }

        return response["access_token"].get<std::string>();
    }

    const std::pair<std::string, std::string> Authentifier::GetMCProfile(const std::string& mc_token) const
    {
        const WebRequestResponse get_response = GETRequest("api.minecraftservices.com", "/minecraft/profile",
            "Bearer " + mc_token);

        if (get_response.status_code != 200)
        {
            std::cerr << "Response returned with status code " << get_response.status_code << " (" << get_response.status_message << ") during MC profile retrieval" << std::endl;
            return { "", "" };
        }

        const nlohmann::json& response = get_response.response;

        if (response.contains("errorMessage"))
        {
            std::cerr << "Error trying to get MC profile: " << response["errorMessage"] << std::endl;
            return { "", "" };
        }

        if (!response.contains("id"))
        {
            std::cerr << "Error trying to get MC profile, no id in response" << std::endl;
            return { "", "" };
        }

        if (!response.contains("name"))
        {
            std::cerr << "Error trying to get MC profile, no name in response" << std::endl;
            return { "", "" };
        }

        return { response["id"].get<std::string>(), response["name"].get<std::string>() };
    }

    const WebRequestResponse Authentifier::WebRequest(const std::string& host, const std::string& raw_request) const
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
            std::cerr << "Invalid response during web request" << std::endl;
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
        const std::string raw_response = output_stringstream.str();

        if (error != asio::error::eof && raw_response.size() != data_length)
        {
            std::cerr << "Error trying to read web request response, Error:\n " << error << std::endl;
            web_response.response = {};
        }
        else
        {
            web_response.response = nlohmann::json::parse(raw_response);
        }

        return web_response;
    }

    const WebRequestResponse Authentifier::POSTRequest(const std::string& host, const std::string& endpoint,
        const std::string& content_type, const std::string& accept, const std::string& data) const
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
        raw_request += "Content-Length: " + std::to_string(data.length()) + "\r\n";
        raw_request += "Connection: close\r\n\r\n";
        raw_request += data;

        return WebRequest(host, raw_request);
    }

    const WebRequestResponse Authentifier::GETRequest(const std::string& host, const std::string& endpoint, const std::string& authorization) const
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
#endif
}