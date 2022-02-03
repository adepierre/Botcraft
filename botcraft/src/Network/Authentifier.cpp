#include <asio.hpp>

#ifdef USE_ENCRYPTION
#include <asio/ssl.hpp>
#include <openssl/sha.h>
#endif

#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>

#include "botcraft/Network/Authentifier.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    const std::string Authentifier::cached_credentials_path = "botcraft_cached_credentials.json";
    const std::string Authentifier::botcraft_app_id = "a0ad834d-e78a-4881-87f6-390aa0f4b283";
    const nlohmann::json Authentifier::defaultCachedCredentials = {
        {"msa", {
            {"access_token", nullptr},
            {"expires_date", nullptr},
            {"refresh_token", nullptr}
        }},
        {"name", nullptr},
        {"id", nullptr},
        {"mc_token", nullptr},
        {"expires_date", nullptr}
    };

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
        const nlohmann::json cached = GetCachedCredentials(login);
        if (!cached.contains("mc_token") || !cached["mc_token"].is_string() ||
            !cached.contains("name") || !cached["name"].is_string() ||
            !cached.contains("id") || !cached["id"].is_string())
        {
            LOG_WARNING("Missing or malformed cached credentials for Mojang account with login <" << login << ">, sending credentials to get a new one...");
        }
        else if (!IsMCTokenValid(cached["mc_token"]))
        {
            LOG_INFO("Minecraft token for Mojang account with login <" << login << "> not valid. Refreshing it...");
            std::tie(mc_access_token, player_display_name, mc_player_uuid) = RefreshMCToken(cached["mc_token"]);

            UpdateCachedMC(login, player_display_name,
                mc_player_uuid, mc_access_token);

            if (!mc_access_token.empty())
            {
                LOG_INFO("Cached Minecraft token for Mojang login <" << login << "> refreshed.");
                return true;
            }

            LOG_WARNING("Refreshing cached Minecraft token for Mojang login <" << login << "> failed.");
        }
        else
        {
            mc_access_token = cached["mc_token"].get<std::string>();
            mc_player_uuid = cached["id"].get<std::string>();
            player_display_name = cached["name"].get<std::string>();
            LOG_INFO("Cached Minecraft token for login <" << login << "> still valid.");
            return true;
        }

        LOG_INFO("Sending credentials to Mojang authentication server...");

        const nlohmann::json data = {
            {
                "agent", {
                    { "name", "Minecraft" },
                    { "version", 1 }
                }
            },
            { "username", login },
            { "password", password },
            { "clientToken", "botcraft" } // clientToken should be a "randomly generated identifier". This is totally random.
        };

        const WebRequestResponse post_response = POSTRequest("authserver.mojang.com", "/authenticate", "application/json; charset=utf-8", "*/*", data.dump());

        if (post_response.status_code != 200)
        {
            LOG_ERROR("Error during authentication, returned status code " << post_response.status_code 
                << " (" << post_response.status_message << "):\n" 
                << post_response.response.dump(4));
            UpdateCachedMC(login, "", "", "");
            return false;
        }

        const nlohmann::json& response = post_response.response;

        std::tie(mc_access_token, player_display_name, mc_player_uuid) = ExtractMCFromResponse(post_response.response);
        UpdateCachedMC(login, player_display_name,
            mc_player_uuid, mc_access_token);

        if (mc_access_token.empty())
        {
            return false;
        }
        else
        {
            LOG_INFO("Authentication completed!");
            return true;
        }
#endif
    }

    const bool Authentifier::AuthMicrosoft(const std::string& login)
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        const nlohmann::json cached = GetCachedCredentials(login);
        if (!cached.contains("mc_token") || !cached["mc_token"].is_string() ||
            !cached.contains("expires_date") || !cached["expires_date"].is_number() ||
            !cached.contains("name") || !cached["name"].is_string() ||
            !cached.contains("id") || !cached["id"].is_string())
        {
            LOG_WARNING("Missing or malformed cached credentials for Microsoft account, starting auth flow...");
        }
        else if (IsTokenExpired(cached["expires_date"].get<long long int>()))
        {
            LOG_INFO("Cached Minecraft token for Microsoft account expired, starting auth flow...");
        }
        else
        {
            mc_access_token = cached["mc_token"].get<std::string>();
            mc_player_uuid = cached["id"].get<std::string>();
            player_display_name = cached["name"].get<std::string>();
            LOG_INFO("Cached Minecraft token for Microsoft account still valid.");
            return true;
        }

        // This auth flow is directly inspired from https://github.com/maxsupermanhd/go-mc-ms-auth
        LOG_INFO("Trying to get Microsoft access token...");
        const std::string msa_token = GetMSAToken(login);
        if (msa_token.empty())
        {
            LOG_ERROR("Unable to get a microsoft auth token");
            return false;
        }

        LOG_INFO("Trying to get XBL token...");
        const std::string xbl_token = GetXBLToken(msa_token);
        if (xbl_token.empty())
        {
            LOG_ERROR("Unable to get a XBL token");
            return false;
        }
        LOG_INFO("XBL token obtained!");

        LOG_INFO("Trying to get XSTS token...");
        const auto [xsts_token, xsts_userhash] = GetXSTSToken(xbl_token);
        if (xsts_token.empty())
        {
            LOG_ERROR("Unable to get a XSTS token");
            return false;
        }
        LOG_INFO("XSTS token obtained!");

        LOG_INFO("Trying to get MC token...");
        mc_access_token = GetMCToken(login, xsts_token, xsts_userhash);
        if (mc_access_token.empty())
        {
            LOG_ERROR("Unable to get a MC token");
            return false;
        }
        LOG_INFO("MC token obtained! Almost there...");


        // We assume you're using an account owning minecraft so
        // we don't check (and also a bit because it's complicated)
        // If you don't, Botcraft won't work on online mode.
        // But you can buy yourself a copy of the game: 
        // https://www.minecraft.net/get-minecraft
        LOG_INFO("Assuming the account owns Minecraft...");

        LOG_INFO("Trying to get MC profile...");
        std::tie(mc_player_uuid, player_display_name) = GetMCProfile(login, mc_access_token);
        if (mc_player_uuid.empty())
        {
            LOG_ERROR("Unable to get a MC profile");
            return false;
        }
        LOG_INFO("MC profile obtained!");

        LOG_INFO("Authentication completed!");

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
            LOG_ERROR("Trying to join a server before authentication");
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
            LOG_ERROR("Response returned with status code " << post_response.status_code 
                << " (" << post_response.status_message << ") during server join:\n" 
                << post_response.response.dump(4));
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
    nlohmann::json Authentifier::GetCachedProfiles() const
    {
        std::ifstream cache_file(cached_credentials_path);
        if (!cache_file.good())
        {
            return {};
        }
        nlohmann::json cached_content;
        cache_file >> cached_content;
        cache_file.close();

        return cached_content;
    }

    nlohmann::json Authentifier::GetCachedCredentials(const std::string& login) const
    {
        const nlohmann::json profiles = GetCachedProfiles();

        if (!profiles.empty() &&
            profiles.contains(login) &&
            profiles[login].is_object())
        {
            return profiles[login];
        }

        return defaultCachedCredentials;
    }

    const std::tuple<std::string, std::string, std::string> Authentifier::ExtractMCFromResponse(const nlohmann::json& response) const
    {
        if (response.contains("error"))
        {
            LOG_ERROR("Error trying to authenticate: " << response["errorMessage"].get<std::string>());
            return { "","","" };
        }

        if (!response.contains("accessToken"))
        {
            LOG_ERROR("Error trying to authenticate, no accessToken returned");
            return { "","","" };
        }

        if (!response.contains("selectedProfile"))
        {
            LOG_ERROR("Error trying to authenticate, no selectedProfile item found");
            return { "","","" };
        }

        const nlohmann::json& profile = response.at("selectedProfile");

        if (!profile.contains("name"))
        {
            LOG_ERROR("Error trying to authenticate, no name in selected profile");
            return { "","","" };
        }

        if (!profile.contains("id"))
        {
            LOG_ERROR("Error trying to authenticate, no id in selected profile");
            return { "","","" };
        }

        return { response["accessToken"].get<std::string>(), profile["name"].get<std::string>(), profile["id"].get<std::string>() };
    }

    const bool Authentifier::IsMCTokenValid(const std::string& token) const
    {
        const nlohmann::json data = {
               { "accessToken", token },
               { "clientToken", "botcraft" }
        };

        const WebRequestResponse post_response = POSTRequest("authserver.mojang.com", "/validate", "application/json; charset=utf-8", "*/*", data.dump());

        if (post_response.status_code != 204)
        {
            return false;
        }

        return true;
    }

    const std::tuple<std::string, std::string, std::string> Authentifier::RefreshMCToken(const std::string& token) const
    {
        const nlohmann::json data = {
               { "accessToken", token },
               { "clientToken", "botcraft" }
        };

        const WebRequestResponse post_response = POSTRequest("authserver.mojang.com", "/refresh", "application/json; charset=utf-8", "*/*", data.dump());

        if (post_response.status_code != 200)
        {
            LOG_ERROR("Error during refreshing, returned status code " << post_response.status_code << " (" << post_response.status_message << ")\n"
                << "Error message: " << post_response.response.dump(4));
            return { "", "", "" };
        }

        return ExtractMCFromResponse(post_response.response);
    }

    const bool Authentifier::IsTokenExpired(const long long int& t) const
    {
        return t < std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    void Authentifier::WriteCacheFile(const nlohmann::json& profiles) const
    {
        std::ofstream cached_ofile(cached_credentials_path);
        if (!cached_ofile.is_open())
        {
            return;
        }
        cached_ofile << profiles.dump(4) << std::endl;
        cached_ofile.close();
    }

    void Authentifier::UpdateCachedMSA(const std::string& login,
        const std::string& access_token, const std::string& refresh_token,
        const long long int& expiration) const
    {
        nlohmann::json profiles = GetCachedProfiles();

        if (!profiles.contains(login))
        {
            profiles[login] = defaultCachedCredentials;
        }

        if (access_token.empty())
        {
            profiles[login]["msa"]["access_token"] = nullptr;
        }
        else
        {
            profiles[login]["msa"]["access_token"] = access_token;
        }

        if (refresh_token.empty())
        {
            profiles[login]["msa"]["refresh_token"] = nullptr;
        }
        else
        {
            profiles[login]["msa"]["refresh_token"] = refresh_token;
        }

        if (expiration == -1)
        {
            profiles[login]["msa"]["expires_date"] = nullptr;
        }
        else
        {
            profiles[login]["msa"]["expires_date"] = expiration;
        }

        WriteCacheFile(profiles);
    }

    void Authentifier::UpdateCachedMCToken(const std::string& login,
        const std::string& mc_token, const long long int& expiration) const
    {
        nlohmann::json profiles = GetCachedProfiles();

        if (!profiles.contains(login))
        {
            profiles[login] = defaultCachedCredentials;
        }

        if (mc_token.empty())
        {
            profiles[login]["mc_token"] = nullptr;
        }
        else
        {
            profiles[login]["mc_token"] = mc_token;
        }

        if (expiration == -1)
        {
            profiles[login]["expires_date"] = nullptr;
        }
        else
        {
            profiles[login]["expires_date"] = expiration;
        }

        WriteCacheFile(profiles);
    }

    void Authentifier::UpdateCachedMCProfile(const std::string& login, const std::string& name, const std::string& id) const
    {
        nlohmann::json profiles = GetCachedProfiles();

        if (!profiles.contains(login))
        {
            profiles[login] = defaultCachedCredentials;
        }

        if (name.empty())
        {
            profiles[login]["name"] = nullptr;
        }
        else
        {
            profiles[login]["name"] = name;
        }

        if (id.empty())
        {
            profiles[login]["id"] = nullptr;
        }
        else
        {
            profiles[login]["id"] = id;
        }

        WriteCacheFile(profiles);
    }

    void Authentifier::UpdateCachedMC(const std::string& login,
        const std::string& name, const std::string& id,
        const std::string& token)
    {
        nlohmann::json profiles = GetCachedProfiles();

        if (!profiles.contains(login))
        {
            profiles[login] = defaultCachedCredentials;
        }

        if (name.empty())
        {
            profiles[login]["name"] = nullptr;
        }
        else
        {
            profiles[login]["name"] = name;
        }

        if (id.empty())
        {
            profiles[login]["id"] = nullptr;
        }
        else
        {
            profiles[login]["id"] = id;
        }

        if (token.empty())
        {
            profiles[login]["mc_token"] = nullptr;
        }
        else
        {
            profiles[login]["mc_token"] = token;
        }

        WriteCacheFile(profiles);
    }

    const std::string Authentifier::GetMSAToken(const std::string& login) const
    {
        // Retrieve cached microsoft credentials
        const nlohmann::json cached = GetCachedCredentials(login);

        // In case there is something wrong in the cached data
        if (!cached.contains("msa") || !cached["msa"].is_object() ||
            !cached["msa"].contains("refresh_token") || !cached["msa"]["refresh_token"].is_string() ||
            !cached["msa"].contains("access_token") || !cached["msa"]["access_token"].is_string() ||
            !cached["msa"].contains("expires_date") || !cached["msa"]["expires_date"].is_number())
        {
            LOG_ERROR("Error trying to get cached Microsoft credentials");
            UpdateCachedMSA(login, "", "", -1);
            LOG_INFO("Starting authentication process...");
            return MSAAuthDeviceFlow(login);
        }

        if (IsTokenExpired(cached["msa"]["expires_date"].get<long long int>()))
        {
            LOG_INFO("Refreshing Microsoft token...");
            std::string refresh_data;
            refresh_data += "client_id=" + botcraft_app_id;
            refresh_data += "&refresh_token=" + cached["msa"]["refresh_token"].get<std::string>();
            refresh_data += "&grant_type=refresh_token";
            refresh_data += "&redirect_uri=https://login.microsoftonline.com/common/oauth2/nativeclient";

            const WebRequestResponse post_response = POSTRequest("login.live.com", "/oauth20_token.srf",
                "application/x-www-form-urlencoded", "*/*", refresh_data);

            // If refresh fails, remove the cache
            // file and restart the whole auth flow
            if (post_response.status_code != 200)
            {
                LOG_ERROR("Response returned with status code " << post_response.status_code 
                    << " (" << post_response.status_message << ") during Microsoft token refresh:\n" 
                    << post_response.response.dump(4));
                UpdateCachedMSA(login, "", "", -1);
                LOG_WARNING("Failed to refresh token, starting Microsoft authentication process...");
                return MSAAuthDeviceFlow(login);
            }

            const nlohmann::json& response = post_response.response;

            if (!response.contains("expires_in"))
            {
                LOG_ERROR("Error trying to refresh Microsoft token, no expires_in in response");
                UpdateCachedMSA(login, "", "", -1);
                LOG_WARNING("Failed to refresh token, starting Microsoft authentication process...");
                return MSAAuthDeviceFlow(login);
            }

            if (!response.contains("refresh_token"))
            {
                LOG_ERROR("Error trying to refresh microsoft token, no refresh_token in response");
                UpdateCachedMSA(login, "", "", -1);
                LOG_WARNING("Failed to refresh token, starting Microsoft authentication process...");
                return MSAAuthDeviceFlow(login);
            }

            if (!response.contains("access_token"))
            {
                LOG_ERROR("Error trying to refresh microsoft token, no access_token in response");
                UpdateCachedMSA(login, "", "", -1);
                LOG_WARNING("Failed to refresh token, starting Microsoft authentication process...");
                return MSAAuthDeviceFlow(login);
            }

            UpdateCachedMSA(login, response["access_token"].get<std::string>(),
                response["refresh_token"].get<std::string>(),
                response["expires_in"].get<long long int>() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()
            );

            LOG_INFO("Cached Microsoft token refreshed");

            return response["access_token"].get<std::string>();
        }

        LOG_INFO("Microsoft token obtained from cache");

        return cached["msa"]["access_token"].get<std::string>();
    }

    const std::string Authentifier::MSAAuthDeviceFlow(const std::string& login) const
    {
        std::string auth_data = "";
        auth_data += "client_id=" + botcraft_app_id;
        auth_data += "&scope=XboxLive.signin%20offline_access";

        const WebRequestResponse post_response = POSTRequest("login.microsoftonline.com", "/consumers/oauth2/v2.0/devicecode",
            "application/x-www-form-urlencoded", "*/*", auth_data);

        if (post_response.status_code != 200)
        {
            LOG_ERROR("Response returned with status code " << post_response.status_code << " ("
                << post_response.status_message << ") during microsoft authentification:\n" 
                << post_response.response.dump(4));
            return "";
        }

        const nlohmann::json& auth_response = post_response.response;

        if (!auth_response.contains("interval"))
        {
            LOG_ERROR("Error trying to get microsoft token, no interval in authentication response");
            return "";
        }

        if (!auth_response.contains("message"))
        {
            LOG_ERROR("Error trying to get microsoft token, no message in authentication response");
            return "";
        }

        if (!auth_response.contains("device_code"))
        {
            LOG_ERROR("Error trying to get microsoft token, no device_code in authentication response");
            return "";
        }

        // Display the instructions the user has to follow to authenticate in the console
        std::cout << auth_response["message"].get<std::string>() << std::endl;
        LOG_INFO(auth_response["message"].get<std::string>());

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
                    LOG_ERROR("Unknown error happened during microsoft device authentication process");
                    return "";
                }

                const std::string error = status_response["error"];

                if (error == "authorization_pending")
                {
                    continue;
                }
                else if (error == "authorization_declined")
                {
                    LOG_ERROR("User declined authorization during microsoft device authentication check");
                    return "";
                }
                else if (error == "expired_token")
                {
                    LOG_ERROR("User took too long to perform device authentication, aborting");
                    return "";
                }
                else if (error == "invalid_grant")
                {
                    if (!status_response.contains("error_description"))
                    {
                        LOG_ERROR("While waiting for microsoft device authentication, token got invalidated (no further information)");
                    }
                    else
                    {
                        LOG_ERROR("While waiting for microsoft device authentication, token got invalidated: " << status_response["error_description"]);
                    }

                    return "";
                }
            }
            else if (post_response.status_code == 200)
            {
                if (!status_response.contains("expires_in"))
                {
                    LOG_ERROR("Error trying to get microsoft token, no expires_in in device authentication status response");
                    return "";
                }

                if (!status_response.contains("refresh_token"))
                {
                    LOG_ERROR("Error trying to get microsoft token, no refresh_token in device authentication status response");
                    return "";
                }

                if (!status_response.contains("access_token"))
                {
                    LOG_ERROR("Error trying to get microsoft token, no access_token in device authentication status response");
                    return "";
                }

                UpdateCachedMSA(login,
                    status_response["access_token"].get<std::string>(),
                    status_response["refresh_token"].get<std::string>(),
                    status_response["expires_in"].get<long long int>() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()
                );

                LOG_INFO("Newly obtained Microsoft token stored in cache");

                return status_response["access_token"].get<std::string>();
            }
            else
            {
                LOG_ERROR("Response returned with status code " << post_response.status_code << " (" << post_response.status_message << ") during microsoft device authentification check");
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
            LOG_ERROR("Response returned with status code " << post_response.status_code 
                << " (" << post_response.status_message << ") during XBL authentication:\n" 
                << post_response.response.dump(4));
            return "";
        }

        const nlohmann::json& response = post_response.response;

        if (!response.contains("Token"))
        {
            LOG_ERROR("Error trying to get XBL token, no Token in authentication response");
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
            LOG_ERROR("Response returned with status code " << post_response.status_code 
                << " (" << post_response.status_message << ") during XSTS authentication:\n" 
                << post_response.response.dump(4));
            return { "", "" };
        }

        const nlohmann::json& response = post_response.response;

        if (!response.contains("Token"))
        {
            LOG_ERROR("Error trying to get XSTS token, no Token in authentication response");
            return { "", "" };
        }

        if (!response.contains("DisplayClaims") || !response["DisplayClaims"].contains("xui")
            || !response["DisplayClaims"]["xui"].is_array() || response["DisplayClaims"]["xui"].size() < 1
            || !response["DisplayClaims"]["xui"][0].contains("uhs"))
        {
            LOG_ERROR("Error trying to get XSTS token, no DisplayClaims/xui/0/uhs in authentication response");
            return { "", "" };
        }

        return { response["Token"], response["DisplayClaims"]["xui"][0]["uhs"] };
    }

    const std::string Authentifier::GetMCToken(const std::string& login, const std::string& xsts_token, const std::string& user_hash) const
    {
        nlohmann::json request_data = {
            { "identityToken", "XBL3.0 x=" + user_hash + ";" + xsts_token }
        };

        const WebRequestResponse post_response = POSTRequest("api.minecraftservices.com", "/authentication/login_with_xbox",
            "application/json", "application/json", request_data.dump());

        if (post_response.status_code != 200)
        {
            LOG_ERROR("Response returned with status code " << post_response.status_code 
                << " (" << post_response.status_message << ") during MC authentication:\n" 
                << post_response.response.dump(4));
            return "";
        }

        const nlohmann::json& response = post_response.response;

        if (!response.contains("access_token"))
        {
            LOG_ERROR("Error trying to get MC token, no access_token in authentication response");
            return "";
        }

        if (!response.contains("expires_in"))
        {
            LOG_WARNING("No expires_in in authentication response of MC");
            // if no expires_in assuming it is one-time, don't need to cache it
            return response["access_token"].get<std::string>();
        }

        UpdateCachedMCToken(login,
            response["access_token"].get<std::string>(),
            response["expires_in"].get<long long int>() + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()
        );

        return response["access_token"].get<std::string>();
    }

    const std::pair<std::string, std::string> Authentifier::GetMCProfile(const std::string& login, const std::string& mc_token) const
    {
        const WebRequestResponse get_response = GETRequest("api.minecraftservices.com", "/minecraft/profile",
            "Bearer " + mc_token);

        if (get_response.status_code != 200)
        {
            LOG_ERROR("Response returned with status code " << get_response.status_code << " (" << get_response.status_message << ") during MC profile retrieval");
            return { "", "" };
        }

        const nlohmann::json& response = get_response.response;

        if (response.contains("errorMessage"))
        {
            LOG_ERROR("Error trying to get MC profile : " << response["errorMessage"]);
            return { "", "" };
        }

        if (!response.contains("id"))
        {
            LOG_ERROR("Error trying to get MC profile, no id in response");
            return { "", "" };
        }

        if (!response.contains("name"))
        {
            LOG_ERROR("Error trying to get MC profile, no name in response");
            return { "", "" };
        }

        UpdateCachedMCProfile(login,
            response["name"].get<std::string>(),
            response["id"].get<std::string>()
        );
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
        const std::string raw_response = output_stringstream.str();

        if (error != asio::error::eof && raw_response.size() != data_length)
        {
            LOG_ERROR("Error trying to read web request response, Error:\n " << error);
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
