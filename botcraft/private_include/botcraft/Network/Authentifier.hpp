#pragma once
#include <array>
#include <optional>
#include <string>
#include <vector>

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
        long long int GetKeyTimestamp() const;

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
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        /// @brief Get player certificates using the Minecraft token, throw if failed
        void GetPlayerCertificates();
#endif
#endif

    private:
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
