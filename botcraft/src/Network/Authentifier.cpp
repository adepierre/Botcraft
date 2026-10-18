#include <asio/connect.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/read.hpp>
#include <asio/read_until.hpp>
#include <asio/streambuf.hpp>

#ifdef USE_ENCRYPTION
#include <asio/ssl.hpp>
#include <openssl/sha.h>
#endif

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "botcraft/Network/Authentifier.hpp"
#include "botcraft/Network/Https.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/MiscUtilities.hpp"
#include "botcraft/Utilities/StringUtilities.hpp"

#include "protocolCraft/Utilities/Json.hpp"


using namespace ProtocolCraft;

namespace Botcraft
{
#ifdef USE_ENCRYPTION
    namespace
    {
        static const std::string botcraft_app_id = "a0ad834d-e78a-4881-87f6-390aa0f4b283";
        static const std::string cached_credentials_path = "botcraft_cached_credentials.json";
        static const Json::Value default_cached_credentials = {
            { "msa", {
                { "access_token", nullptr },
                { "expires_date", nullptr },
                { "refresh_token", nullptr }
            }},
            { "name", nullptr },
            { "id", nullptr },
            { "mc_token", nullptr },
            { "expires_date", nullptr }
        };

        /// @brief Get the cached credentials of one account, throw if the cache file is not valid JSON
        /// @param key Key of the account in the cache file
        /// @return Cached credentials, or the default ones if the account is not in the file
        Json::Value LoadCachedAccount(const std::string& key);

        /// @brief Save the credentials of one account, keeping the other accounts of the file
        void SaveCachedAccount(const std::string& key, const Json::Value& account);

        /// @brief Get a Minecraft token using the Microsoft auth flow (MSA -> XBL -> XSTS -> MC)
        /// @param cached Cached credentials of the account. "msa", "mc_token" and "expires_date" are erased, then set again on success
        /// @return The Minecraft access token, throw if failed
        std::string GetMCTokenFromMicrosoft(Json::Value& cached);

        /// @brief Get the Minecraft profile of a Minecraft token
        /// @param mc_token Minecraft access token
        /// @return Pair of {uuid, name}, throw if failed
        std::pair<std::string, std::string> GetMCProfile(const std::string& mc_token);

        /// @brief Convert ISO8601 time to timestamp
        /// @param s Date/time
        /// @return Number of ms since epoch
        long long int TimestampMilliFromISO8601(const std::string& s);
    }
#endif


    Authentifier::Authentifier()
    {
        mc_player_uuid_bytes.fill(0);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        key_timestamp = 0;
        rnd = std::mt19937(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()));
#endif
    }

    Authentifier::~Authentifier()
    {
#ifdef USE_ENCRYPTION
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        if (private_key != nullptr)
        {
            RSA_free(private_key);
            private_key = nullptr;
        }
#endif
#endif
    }

    bool Authentifier::AuthMicrosoft(const std::string& cache_key)
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        try
        {
            Json::Value cached = LoadCachedAccount(cache_key);
            // Cached value will be updated upon leaving the scope. If any step fails, value will have missing fields to make sure next run doesn't use garbage values
            Utilities::OnEndScope save_cache([&]() { SaveCachedAccount(cache_key, cached); });

            const long long int now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            const bool cached_ok =
                cached.contains("mc_token") && cached["mc_token"].is_string() &&
                cached.contains("expires_date") && cached["expires_date"].is_number() &&
                cached.contains("name") && cached["name"].is_string() &&
                cached.contains("id") && cached["id"].is_string();

            if (cached_ok && cached["expires_date"].get<long long int>() >= now)
            {
                LOG_INFO("Cached Minecraft token for Microsoft account still valid.");
                mc_access_token = cached["mc_token"].get_string();
                player_display_name = cached["name"].get_string();
                mc_player_uuid = cached["id"].get_string();
            }
            else
            {
                if (cached_ok)
                {
                    LOG_INFO("Cached Minecraft token for Microsoft account expired, starting auth flow...");
                }
                else
                {
                    LOG_WARNING("Missing or malformed cached credentials for Microsoft account, starting auth flow...");
                }

                mc_access_token = GetMCTokenFromMicrosoft(cached);

                // We assume you're using an account owning minecraft so we don't check (and also a bit because it's complicated)
                // If you don't, Botcraft won't work on online mode.
                // But you can buy yourself a copy of the game: https://www.minecraft.net/get-minecraft
                LOG_INFO("Assuming the account owns Minecraft...");

                LOG_INFO("Trying to get MC profile...");
                cached.get_object().erase("id");
                cached.get_object().erase("name");
                std::tie(mc_player_uuid, player_display_name) = GetMCProfile(mc_access_token);
                cached["id"] = mc_player_uuid;
                cached["name"] = player_display_name;
                LOG_INFO("MC profile obtained!");
            }
            UpdateUUIDBytes();

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            GetPlayerCertificates();
#endif
            LOG_INFO("Authentication completed!");
            return true;
        }
        catch (const std::exception& e)
        {
            LOG_ERROR(e.what());
            return false;
        }
#endif
    }

    bool Authentifier::AuthMCToken(const std::string& mc_token)
    {
#ifndef USE_ENCRYPTION
        return false;
#else
        try
        {
            mc_access_token = mc_token;

            LOG_INFO("Trying to get MC profile...");
            std::tie(mc_player_uuid, player_display_name) = GetMCProfile(mc_access_token);
            UpdateUUIDBytes();
            LOG_INFO("MC profile obtained!");

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            GetPlayerCertificates();
#endif
            LOG_INFO("Authentication completed!");
            return true;
        }
        catch (const std::exception& e)
        {
            LOG_ERROR(e.what());
            return false;
        }
#endif
    }

    bool Authentifier::JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& server_public_key) const
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
        SHA1_Update(&sha_context, server_public_key.data(), server_public_key.size());

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
            int position = static_cast<int>(digest.size()) - 1;
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
            ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(digest[i] & 0xFF);
        }

        std::string server_hash = ss.str();
        // Remove leading 0
        const size_t start = server_hash.find_first_not_of('0');
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
        const Json::Value data = {
            { "accessToken", mc_access_token },
            { "selectedProfile", mc_player_uuid },
            { "serverId", server_hash}
        };

        const WebRequestResponse post_response = POSTRequest("sessionserver.mojang.com", "/session/minecraft/join",
            "application/json; charset=utf-8", "*/*", "", data.Dump());

        if (post_response.status_code != 204)
        {
            LOG_ERROR("Response returned with status code " << post_response.status_code
                << " (" << post_response.status_message << ") during server join:\n"
                << post_response.response.Dump(4));
            return false;
        }

        return true;
#endif
    }

    const std::string& Authentifier::GetPlayerDisplayName() const
    {
        return player_display_name;
    }

    const std::array<unsigned char, 16>& Authentifier::GetPlayerUUID() const
    {
        return mc_player_uuid_bytes;
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    RSA* Authentifier::GetPrivateKey() const
    {
        return private_key;
    }

    const std::string& Authentifier::GetPublicKey() const
    {
        return public_key;
    }

    const std::string& Authentifier::GetKeySignature() const
    {
        return key_signature;
    }

    long long int Authentifier::GetKeyTimestamp() const
    {
        return key_timestamp;
    }

#if PROTOCOL_VERSION == 759 /* 1.19 */
    std::vector<unsigned char> Authentifier::GetMessageSignature(const std::string& message, long long int& salt, long long int& timestamp)
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
    std::vector<unsigned char> Authentifier::GetMessageSignature(const std::string& message,
        const std::vector<unsigned char>& previous_signature, const std::vector<LastSeenMessagesEntry>& last_seen,
        long long int& salt, long long int& timestamp)
#else
    std::vector<unsigned char> Authentifier::GetMessageSignature(const std::string& message,
        const int message_sent_index, const UUID& chat_session_uuid,
        const std::vector<std::vector<unsigned char>>& last_seen,
        long long int& salt, long long int& timestamp)
#endif
    {
#ifndef USE_ENCRYPTION
        LOG_ERROR("Trying to compute message signature while botcraft was compiled without USE_ENCRYPTION.");
        return {};
#else
        if (mc_player_uuid.empty() || private_key == nullptr)
        {
            LOG_ERROR("Trying to compute message signature before authentication");
            return {};
        }

        // Generate random salt and timestamp
        salt = std::uniform_int_distribution<long long int>(std::numeric_limits<long long int>::min(), std::numeric_limits<long long int>::max())(rnd);
        timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::array<unsigned char, 8> salt_bytes;
        std::array<unsigned char, 8> timestamp_bytes;

        for (int i = 0; i < 8; ++i)
        {
            salt_bytes[i] = static_cast<unsigned char>((salt >> (8 * (7 - i))) & 0xFF);
            // Signature is computed with seconds not milliseconds
            timestamp_bytes[i] = static_cast<unsigned char>(((timestamp / 1000) >> (8 * (7 - i))) & 0xFF);
        }

        std::array<unsigned char, SHA256_DIGEST_LENGTH> signature_hash;
#if PROTOCOL_VERSION == 759 /* 1.19 */
        // Signature is computed with a dumb json instead of the actual string
        const std::string jsoned_message = "{\"text\":\"" + message + "\"}";

        // Compute hash
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, salt_bytes.data(), salt_bytes.size());
        SHA256_Update(&sha256, mc_player_uuid_bytes.data(), mc_player_uuid_bytes.size());
        SHA256_Update(&sha256, timestamp_bytes.data(), timestamp_bytes.size());
        SHA256_Update(&sha256, jsoned_message.data(), jsoned_message.size());
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        const unsigned char const_byte_70 = 70;

        // Body hash
        std::array<unsigned char, SHA256_DIGEST_LENGTH> body_hash;
        SHA256_CTX body_sha256;
        SHA256_Init(&body_sha256);
        SHA256_Update(&body_sha256, salt_bytes.data(), salt_bytes.size());
        SHA256_Update(&body_sha256, timestamp_bytes.data(), timestamp_bytes.size());
        SHA256_Update(&body_sha256, message.data(), message.size());
        SHA256_Update(&body_sha256, &const_byte_70, 1);
        // All previously seen messages
        for (int i = 0; i < last_seen.size(); ++i)
        {
            SHA256_Update(&body_sha256, &const_byte_70, 1);
            SHA256_Update(&body_sha256, last_seen[i].GetProfileId().data(), last_seen[i].GetProfileId().size());
            SHA256_Update(&body_sha256, last_seen[i].GetLastSignature().data(), last_seen[i].GetLastSignature().size());
        }
        SHA256_Final(body_hash.data(), &body_sha256);


        // Signature hash
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        if (!previous_signature.empty())
        {
            SHA256_Update(&sha256, previous_signature.data(), previous_signature.size());
        }
        SHA256_Update(&sha256, mc_player_uuid_bytes.data(), mc_player_uuid_bytes.size());
        SHA256_Update(&sha256, body_hash.data(), body_hash.size());
#else
        std::array<unsigned char, 4> bytes_1_big_endian;
        std::array<unsigned char, 4> message_sent_index_bytes;
        std::array<unsigned char, 4> message_size_bytes;
        std::array<unsigned char, 4> last_seen_size_bytes;

        for (int i = 0; i < 4; ++i)
        {
            bytes_1_big_endian[i] = static_cast<unsigned char>((1 >> (8 * (3 - i))) & 0xFF);
            message_sent_index_bytes[i] = static_cast<unsigned char>((message_sent_index >> (8 * (3 - i))) & 0xFF);
            message_size_bytes[i] = static_cast<unsigned char>((static_cast<int>(message.size()) >> (8 * (3 - i))) & 0xFF);
            last_seen_size_bytes[i] = static_cast<unsigned char>((static_cast<int>(last_seen.size()) >> (8 * (3 - i))) & 0xFF);
        }

        // Compute hash
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Init(&sha256);
        // Big endian (int)1
        SHA256_Update(&sha256, bytes_1_big_endian.data(), bytes_1_big_endian.size());
        // signed message link
        SHA256_Update(&sha256, mc_player_uuid_bytes.data(), mc_player_uuid_bytes.size());
        SHA256_Update(&sha256, chat_session_uuid.data(), chat_session_uuid.size());
        SHA256_Update(&sha256, message_sent_index_bytes.data(), message_sent_index_bytes.size());
        // signed message body
        SHA256_Update(&sha256, salt_bytes.data(), salt_bytes.size());
        SHA256_Update(&sha256, timestamp_bytes.data(), timestamp_bytes.size());
        SHA256_Update(&sha256, message_size_bytes.data(), message_size_bytes.size());
        SHA256_Update(&sha256, message.data(), message.size());
        SHA256_Update(&sha256, last_seen_size_bytes.data(), last_seen_size_bytes.size());
        for (size_t i = 0; i < last_seen.size(); ++i)
        {
            SHA256_Update(&sha256, last_seen[i].data(), last_seen[i].size());
        }
#endif
        SHA256_Final(signature_hash.data(), &sha256);

        // Compute signature
        const int private_key_size = RSA_size(private_key);
        std::vector<unsigned char> signature(private_key_size);
        unsigned int signature_size;
        RSA_sign(NID_sha256, signature_hash.data(), static_cast<unsigned int>(signature_hash.size()), signature.data(), &signature_size, private_key);
        signature.resize(signature_size);

        return signature;
#endif
    }
#endif

    void Authentifier::UpdateUUIDBytes()
    {
        for (int i = 0; i < 32; i += 2)
        {
            const std::string byte_str = mc_player_uuid.substr(i, 2);
            mc_player_uuid_bytes[i / 2] = static_cast<unsigned char>(std::strtol(byte_str.c_str(), nullptr, 16));
        }
    }

#ifdef USE_ENCRYPTION
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    void Authentifier::GetPlayerCertificates()
    {
        // Certificates are not cached cause they're sometimes made invalid before the expire date (not sure why or when)
        // So instead we get new ones for each connection (vanilla like behaviour)
        LOG_INFO("Getting player certificates...");

#if PROTOCOL_VERSION == 759 /* 1.19 */
        const std::string signature_field = "publicKeySignature";
#else
        const std::string signature_field = "publicKeySignatureV2";
#endif
        const Json::Value response = CheckJsonResponse(
            POSTRequest("api.minecraftservices.com", "/player/certificates", "application/json", "application/json", "Bearer " + mc_access_token, ""),
            "player certificates acquisition",
            { "keyPair", signature_field, "expiresAt" }
        );

        const Json::Value& key_pair = response["keyPair"];
        if (!key_pair.contains("privateKey") || !key_pair.contains("publicKey"))
        {
            throw std::runtime_error("Error trying to get player certificates, no keyPair/privateKey or keyPair/publicKey in response");
        }

        // Extract signature key from PEM string
        if (private_key != nullptr)
        {
            RSA_free(private_key);
        }
        BIO* keybio = BIO_new_mem_buf((void*)key_pair["privateKey"].get_string().c_str(), -1);
        private_key = PEM_read_bio_RSAPrivateKey(keybio, nullptr, nullptr, nullptr);
        BIO_free(keybio);

        public_key = key_pair["publicKey"].get_string();
        key_signature = response[signature_field].get_string();
        // Convert expires date in ISO8601 to ms since UNIX epoch
        key_timestamp = TimestampMilliFromISO8601(response["expiresAt"].get_string());

        LOG_INFO("Player certificates obtained!");
    }
#endif
#endif

#ifdef USE_ENCRYPTION
    namespace
    {
        Json::Value ReadCacheFile()
        {
            std::ifstream file(cached_credentials_path, std::ios::in);
            std::stringstream content;
            // If the file is missing, nothing is read and content stays empty
            content << file.rdbuf();
            return content.str().empty() ? Json::Object() : Json::Parse(content.str(), true);
        }

        Json::Value LoadCachedAccount(const std::string& key)
        {
            const Json::Value profiles = ReadCacheFile();
            // File is not valid
            if (!profiles.is_object())
            {
                throw std::runtime_error("Error trying to read " + cached_credentials_path + ", fix or delete it");
            }
            if (profiles.contains(key) && profiles[key].is_object())
            {
                return profiles[key];
            }
            return default_cached_credentials;
        }

        void SaveCachedAccount(const std::string& key, const Json::Value& account)
        {
            // Read again: another bot of this program may have saved its account since we loaded ours
            Json::Value profiles = ReadCacheFile();
            if (!profiles.is_object())
            {
                LOG_ERROR("Error trying to read " << cached_credentials_path << ", credentials not saved");
                return;
            }
            profiles[key] = account;
            std::ofstream file(cached_credentials_path);
            file << profiles.Dump(4) << std::endl;
        }

        Json::Value MSAAuthDeviceFlow()
        {
            const Json::Value auth_response = CheckJsonResponse(
                POSTRequest("login.microsoftonline.com", "/consumers/oauth2/v2.0/devicecode", "application/x-www-form-urlencoded", "*/*", "",
                    "client_id=" + botcraft_app_id + "&scope=XboxLive.signin%20offline_access"),
                "microsoft authentification", { "interval", "message", "device_code" }
            );

            // Display the instructions the user has to follow to authenticate in the console
            LOG_ALWAYS(auth_response["message"].get_string());

            const std::string check_auth_status_data =
                "client_id=" + botcraft_app_id +
                "&scope=XboxLive.signin%20offline_access" +
                "&grant_type=urn:ietf:params:oauth:grant-type:device_code" +
                "&device_code=" + auth_response["device_code"].get_string();

            long long int poll_interval = auth_response["interval"].get_number<long long int>();
            const long long int expires_in = auth_response.contains("expires_in") ? auth_response["expires_in"].get_number<long long int>() : 900;
            const std::chrono::steady_clock::time_point deadline = std::chrono::steady_clock::now() + std::chrono::seconds(expires_in);
            while (std::chrono::steady_clock::now() < deadline)
            {
                std::this_thread::sleep_for(std::chrono::seconds(poll_interval + 1));

                const WebRequestResponse status = POSTRequest("login.microsoftonline.com", "/consumers/oauth2/v2.0/token",
                    "application/x-www-form-urlencoded", "*/*", "", check_auth_status_data);

                if (status.status_code == 400 && status.response.contains("error"))
                {
                    const std::string error = status.response["error"].get_string();
                    if (error == "authorization_pending")
                    {
                        continue;
                    }
                    if (error == "slow_down")
                    {
                        poll_interval += 5;
                        continue;
                    }
                    // authorization_declined, expired_token, bad_verification_code, invalid_grant...
                    throw std::runtime_error("Error during microsoft device authentication: " + error +
                        (status.response.contains("error_description") ? " (" + status.response["error_description"].get_string() + ")" : ""));
                }

                const Json::Value response = CheckJsonResponse(status, "microsoft device authentification check", { "access_token", "refresh_token", "expires_in" });
                LOG_INFO("Newly obtained Microsoft token stored in cache");
                return response;
            }
            throw std::runtime_error("Microsoft device authentication timed out");
        }

        std::string GetMSAToken(Json::Value& cached)
        {
            const long long int now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            // Copy, as "msa" is erased below
            const Json::Value msa = cached["msa"];
            const bool cached_ok =
                msa.contains("refresh_token") && msa["refresh_token"].is_string() &&
                msa.contains("access_token") && msa["access_token"].is_string() &&
                msa.contains("expires_date") && msa["expires_date"].is_number();

            if (cached_ok && msa["expires_date"].get<long long int>() >= now)
            {
                LOG_INFO("Cached Microsoft token still valid");
                return msa["access_token"].get_string();
            }

            // Set again at the end, only if we get a new token
            cached.get_object().erase("msa");

            Json::Value response;
            if (!cached_ok)
            {
                LOG_ERROR("Error trying to get cached Microsoft credentials");
                LOG_INFO("Starting authentication process...");
                response = MSAAuthDeviceFlow();
            }
            else
            {
                LOG_INFO("Refreshing Microsoft token...");
                try
                {
                    response = CheckJsonResponse(POSTRequest("login.live.com", "/oauth20_token.srf",
                        "application/x-www-form-urlencoded", "*/*", "",
                        "client_id=" + botcraft_app_id +
                        "&refresh_token=" + msa["refresh_token"].get_string() +
                        "&grant_type=refresh_token" +
                        "&redirect_uri=https://login.microsoftonline.com/common/oauth2/nativeclient"),
                        "Microsoft token refresh", { "access_token", "refresh_token", "expires_in" });
                    LOG_INFO("Cached Microsoft token refreshed");
                }
                catch (const std::exception& e)
                {
                    // If refresh fails restart the whole auth flow
                    LOG_ERROR(e.what());
                    LOG_INFO("Failed to refresh token, starting Microsoft authentication process...");
                    response = MSAAuthDeviceFlow();
                }
            }

            cached["msa"] = {
                { "access_token", response["access_token"].get_string() },
                { "refresh_token", response["refresh_token"].get_string() },
                { "expires_date", response["expires_in"].get<long long int>() + now }
            };
            return response["access_token"].get_string();
        }

        std::string GetXBLToken(const std::string& msa_token)
        {
            const Json::Value request_data = {
                { "Properties", {
                        {"AuthMethod", "RPS"},
                        {"SiteName", "user.auth.xboxlive.com"},
                        {"RpsTicket", "d=" + msa_token}
                    }
                },
                { "RelyingParty", "http://auth.xboxlive.com"},
                { "TokenType", "JWT"}
            };

            return CheckJsonResponse(
                POSTRequest("user.auth.xboxlive.com", "/user/authenticate", "application/json", "application/json", "", request_data.Dump()),
                "XBL authentication",
                { "Token" }
            )["Token"].get_string();
        }

        std::pair<std::string, std::string> GetXSTSToken(const std::string& xbl_token)
        {
            const Json::Value request_data = {
                { "Properties", {
                    {"SandboxId", "RETAIL"},
                    {"UserTokens", { xbl_token } }
                }},
                { "RelyingParty", "rp://api.minecraftservices.com/"},
                { "TokenType", "JWT"}
            };

            const Json::Value response = CheckJsonResponse(
                POSTRequest("xsts.auth.xboxlive.com", "/xsts/authorize", "application/json", "application/json", "", request_data.Dump()),
                "XSTS authentication",
                { "Token", "DisplayClaims" }
            );

            const Json::Value& display_claims = response["DisplayClaims"];
            if (
                !display_claims.contains("xui") ||
                !display_claims["xui"].is_array() ||
                display_claims["xui"].size() < 1 ||
                !display_claims["xui"][0].contains("uhs")
            )
            {
                throw std::runtime_error("Error trying to get XSTS token, no DisplayClaims/xui/0/uhs in authentication response");
            }

            return { response["Token"].get_string(), display_claims["xui"][0]["uhs"].get_string() };
        }

        std::string GetMCTokenFromMicrosoft(Json::Value& cached)
        {
            LOG_INFO("Trying to get Microsoft access token...");
            const std::string msa_token = GetMSAToken(cached);

            LOG_INFO("Trying to get XBL token...");
            const std::string xbl_token = GetXBLToken(msa_token);
            LOG_INFO("XBL token obtained!");

            LOG_INFO("Trying to get XSTS token...");
            const auto [xsts_token, user_hash] = GetXSTSToken(xbl_token);
            LOG_INFO("XSTS token obtained!");

            LOG_INFO("Trying to get MC token...");
            const long long int now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            // Set again below, only if we get a new token with an expiry date
            cached.get_object().erase("mc_token");
            cached.get_object().erase("expires_date");

            const Json::Value request_data = {
                { "identityToken", "XBL3.0 x=" + user_hash + ";" + xsts_token }
            };
            const Json::Value response = CheckJsonResponse(
                POSTRequest("api.minecraftservices.com", "/authentication/login_with_xbox", "application/json", "application/json", "", request_data.Dump()),
                "MC authentication",
                { "access_token" }
            );

            if (response.contains("expires_in"))
            {
                cached["mc_token"] = response["access_token"].get_string();
                cached["expires_date"] = response["expires_in"].get<long long int>() + now;
            }
            else
            {
                // If no expires_in assuming it is one-time, don't need to cache it
                LOG_WARNING("No expires_in in authentication response of MC");
            }
            LOG_INFO("MC token obtained! Almost there...");

            return response["access_token"].get_string();
        }

        std::pair<std::string, std::string> GetMCProfile(const std::string& mc_token)
        {
            const Json::Value response = CheckJsonResponse(
                GETRequest("api.minecraftservices.com", "/minecraft/profile", "Bearer " + mc_token),
                "MC profile retrieval",
                { "id", "name" }
            );

            return { response["id"].get_string(), response["name"].get_string() };
        }

        int IsLeap(const int year)
        {
            if (year % 400 == 0) { return 1; }
            if (year % 100 == 0) { return 0; }
            if (year % 4 == 0) { return 1; }
            return 0;
        }

        int DaysFrom0(const int year)
        {
            const long long y = year - 1;
            return 365 * y + y / 400 - y / 100 + y / 4;
        }

        int DaysFrom1970(int32_t year)
        {
            return DaysFrom0(year) - DaysFrom0(1970);
        }

        int DaysFrom1Jan(const int year, const int month, const int day)
        {
            static constexpr std::array<std::array<int, 12>, 2> days =
            { {
              { 0,31,59,90,120,151,181,212,243,273,304,334},
              { 0,31,60,91,121,152,182,213,244,274,305,335}
            } };

            return days[IsLeap(year)][month - 1] + day - 1;
        }

        long long int TimestampMilliFromISO8601(const std::string& s)
        {
            std::tm t{};
            std::stringstream iso8601(s);
            iso8601 >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");

            if (iso8601.fail() || t.tm_mon < 0 || t.tm_mon > 11)
            {
                LOG_ERROR("Error trying to parse ISO 8601 string: " << s);
                return 0;
            }

            std::string millis;
            if (iso8601.peek() == '.')
            {
                iso8601.get();
                while (millis.size() < 3 && std::isdigit(iso8601.peek()))
                {
                    millis += static_cast<char>(iso8601.get());
                }
            }
            millis.resize(3, '0');

            const int year = t.tm_year + 1900;
            const int month = t.tm_mon + 1;
            const int day = t.tm_mday;
            const int days_since_epoch = DaysFrom1970(year) + DaysFrom1Jan(year, month, day);

            const long long int sec = 3600LL * 24 * days_since_epoch + 3600 * t.tm_hour + 60 * t.tm_min + t.tm_sec;

            return sec * 1000 + std::stoll(millis);
        }
    }
#endif
}
