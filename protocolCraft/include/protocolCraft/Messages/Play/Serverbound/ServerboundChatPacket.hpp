#pragma once

#include <string>

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
#include "protocolCraft/Types/SaltSignature.hpp"
#else
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif
#endif
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPacket : public BaseMessage<ServerboundChatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chat";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (std::string),
            (Message)
        );
#elif PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS(
            (std::string, long long int, SaltSignature, bool),
            (Message,     Timestamp,     SaltSignature, SignedPreview)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (std::string, long long int, long long int, std::vector<unsigned char>, bool,          LastSeenMessagesUpdate),
            (Message,     Timestamp,     Salt,          Signature,                  SignedPreview, LastSeenMessages)
        );
#else
        DECLARE_FIELDS(
            (std::string, long long int, long long int, std::optional<std::array<unsigned char, 256>>, LastSeenMessagesUpdate),
            (Message,     Timestamp,     Salt,          Signature,                                     LastSeenMessages)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Message);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Timestamp);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 760 /* < 1.19.1 */
        GETTER_SETTER(SaltSignature);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(SignedPreview);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        GETTER_SETTER(Salt);
        GETTER_SETTER(Signature);
        GETTER_SETTER(LastSeenMessages);
#endif
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        // Convenient set from a std::vector
        auto& SetSignature(const std::vector<unsigned char>& signature)
        {
            std::array<unsigned char, 256> new_signature{};
            std::copy_n(signature.begin(), 256, new_signature.begin());
            return SetSignature(new_signature);
        }
#endif
    };
} //ProtocolCraft
