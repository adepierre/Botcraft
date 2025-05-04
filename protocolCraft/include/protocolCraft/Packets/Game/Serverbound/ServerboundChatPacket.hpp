#pragma once

#include <string>

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
#include "protocolCraft/Types/SaltSignature.hpp"
#else
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif
#endif
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundChatPacket : public BasePacket<ServerboundChatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        SERIALIZED_FIELD(Message, std::string);
#elif PROTOCOL_VERSION < 760 /* < 1.19.1 */
        SERIALIZED_FIELD(Message, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(SaltSignature, ProtocolCraft::SaltSignature);
        SERIALIZED_FIELD(SignedPreview, bool);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Message, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(Signature, std::vector<unsigned char>);
        SERIALIZED_FIELD(SignedPreview, bool);
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);
#else
        SERIALIZED_FIELD(Message, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(Signature, std::optional<std::array<unsigned char, 256>>);
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    public:
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
