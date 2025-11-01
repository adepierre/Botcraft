#pragma once
#include <array>
#include <optional>
#include <string>

#include "protocolCraft/Utilities/Json.hpp"

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include <random>
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/LastSeenMessagesEntry.hpp"
#endif

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
struct rsa_st;
typedef struct rsa_st RSA;
#endif

namespace Botcraft
{
    struct WebRequestResponse
    {
        ProtocolCraft::Json::Value response;
        unsigned int status_code = 0;
        std::string status_message;
    };

    class Authentifier
    {
    public:
        Authentifier();
        ~Authentifier();

        /// @brief Authentication using a Microsoft account, storing the credentials in the cache file
        /// @param cache_key used as key to identify the credentials in cache file
        /// @return True if successfully authenticated, false otherwise
        bool AuthMicrosoft(const std::string& cache_key);

        /// @brief Authentication using a minecraft token
        /// @param mc_token Minecraft token, must be valid
        /// @return True if successfully authenticated, false otherwise
        bool AuthMCToken(const std::string& mc_token);

        // Join a server after encryption request
        bool JoinServer(const std::string& server_id, const std::vector<unsigned char>& shared_secret, const std::vector<unsigned char>& server_public_key) const;

        const std::string& GetPlayerDisplayName() const;
        const std::array<unsigned char, 16>& GetPlayerUUID() const;

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        RSA* GetPrivateKey() const;
        const std::string& GetPublicKey() const;
        const std::string& GetKeySignature() const;
        const long long int GetKeyTimestamp() const;

#if PROTOCOL_VERSION == 759 /* 1.19 */
        /// @brief Compute the signature of a message
        /// @param message Message to send
        /// @param salt Output salt used to generate the signature
        /// @param timestamp Output timestamp in ms used to generate the signature
        /// @return The message signature
        std::vector<unsigned char> GetMessageSignature(const std::string& message, long long int& salt, long long int& timestamp);
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        /// @brief Compute the signature of a message
        /// @param message Message to send
        /// @param previous_signature Signature of the previous message sent
        /// @param last_seen Vector of previously received messages from players
        /// @param salt Output salt used to generate the signature
        /// @param timestamp Output timestamp in ms used to generate the signature
        /// @return The message signature
        std::vector<unsigned char> GetMessageSignature(const std::string& message,
            const std::vector<unsigned char>& previous_signature, const std::vector<ProtocolCraft::LastSeenMessagesEntry>& last_seen,
            long long int& salt, long long int& timestamp);
#else
        /// @brief Compute the signature of a message
        /// @param message Message to send
        /// @param message_sent_index Index of the message in this message chain
        /// @param chat_session_uuid UUID of the chat session, as sent in ServerboundChatSessionUpdatePacket
        /// @param last_seen Vector of signatures of previously received messages
        /// @param salt Output salt used to generate the signature
        /// @param timestamp Output timestamp in ms used to generate the signature
        /// @return The message signature
        std::vector<unsigned char> GetMessageSignature(const std::string& message,
            const int message_sent_index, const ProtocolCraft::UUID& chat_session_uuid,
            const std::vector<std::vector<unsigned char>>& last_seen,
            long long int& salt, long long int& timestamp);
#endif
#endif

    private:
        /// @brief Compute the UUID bytes from the string one
        void UpdateUUIDBytes();

#ifdef USE_ENCRYPTION
        /// @brief Get the content of the whole cache file
        /// @return The content in JSON
        ProtocolCraft::Json::Value GetAllCachedAccounts() const;

        /// @brief Get the cached credentials for a key
        /// @return Cached credentials for the given account, or default if not found in cached
        ProtocolCraft::Json::Value GetCachedAccountOrDefault(const std::optional<std::string>& cache_key) const;

        /// @brief Save a profiles list to cache file
        /// @param profiles A json object with logins as keys and cache credentials as values
        void WriteCacheFile(const ProtocolCraft::Json::Value& profiles) const;

        /// @brief Check if there is a saved credentials file and
        /// if the token is still valid. Refresh it if not.
        /// If file doesn't exist, launch auth device flow
        /// @param cache_key If present, the value will be stored in the cache file under the given key
        /// @return The microsoft access token, empty if failed.
        std::string GetMSAToken(const std::optional<std::string>& cache_key) const;

        /// @brief Try to authenticate with microsoft account using device flow.
        /// @param cache_key If present, the values will be stored in the cache file under the given key
        /// @return The microsoft access token, empty if failed.
        std::string MSAAuthDeviceFlow(const std::optional<std::string>& cache_key) const;

        /// @brief Try to get XBox Live token from Microsoft token.
        /// @param msa_token Microsoft access token
        /// @return XBL token, empty if failed.
        std::string GetXBLToken(const std::string& msa_token) const;

        /// @brief Try to get XSTS token from XBL token.
        /// @param xbl_token XBL token
        /// @return Pair of {XSTS token, userhash}, empty if failed.
        std::pair<std::string, std::string> GetXSTSToken(const std::string& xbl_token) const;

        /// @brief Try to get MC token from XSTS token and user hash
        /// @param xsts_token XSTS Token
        /// @param user_hash User hash
        /// @param cache_key If present, the value will be stored in the cache file under the given key
        /// @return True if minecraft token was correctly updated, false otherwise
        bool GetMCToken(const std::string& xsts_token, const std::string& user_hash, const std::optional<std::string>& cache_key);

        /// @brief Try to get Minecraft profile from Minecraft token
        /// @param cache_key If present, the values will be stored in the cache file under the given key
        /// @return True if the profile was correctly updated, false otherwise
        bool GetMCProfile(const std::optional<std::string>& cache_key);

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        /// @brief Try to get player certificates using Minecraft token
        /// @return True if the certificates were correctly fetched, false otherwise
        bool GetPlayerCertificates();
#endif

        /// @brief Send a web request with ssl stuff
        /// @param host The host address
        /// @param raw_request The full request (header + content) as it should be sent
        /// @return A WebRequestResponse returned by the server
        const WebRequestResponse WebRequest(const std::string& host, const std::string& raw_request) const;

        /// @brief Send a POST request with ssl stuff
        /// @param host The host address (after https:// and before the first /)
        /// @param endpoint The endpoint (after the first /)
        /// @param content_type Data type
        /// @param accept Accept header value
        /// @param data Actual data to send
        /// @param authorization Optional authorization header, only if not empty
        /// @return A WebRequestResponse returned by the server
        const WebRequestResponse POSTRequest(const std::string& host, const std::string& endpoint,
            const std::string& content_type, const std::string& accept,
            const std::string& authorization, const std::string& data) const;

        /// @brief Send a GET request with ssl stuff
        /// @param host The host address (after https:// and before the first /)
        /// @param endpoint The endpoint (after the first /)
        /// @param authorization Optional authorization header, only set if not empty
        /// @return A WebRequestResponse returned by the server
        const WebRequestResponse GETRequest(const std::string& host, const std::string& endpoint,
            const std::string& authorization = "") const;
#endif

    private:

        /// @brief Path to cache the credentials
        static const std::string cached_credentials_path;

        /// @brief Botcraft app ID for microsoft auth
        static const std::string botcraft_app_id;

        /// @brief Default cached credentials JSON
        static const ProtocolCraft::Json::Value defaultCachedCredentials;

        std::string player_display_name;
        std::string mc_access_token;
        std::string mc_player_uuid;
        std::array<unsigned char, 16> mc_player_uuid_bytes;

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        RSA* private_key = nullptr;
        std::string public_key;
        std::string key_signature;
        long long int key_timestamp;

        std::mt19937 rnd;
#endif

    };
}
