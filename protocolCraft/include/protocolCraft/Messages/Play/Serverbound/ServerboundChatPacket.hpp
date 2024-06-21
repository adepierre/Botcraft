#pragma once

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include <string>

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
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x02;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */ || PROTOCOL_VERSION == 755 /* 1.17 */ ||  \
      PROTOCOL_VERSION == 756 /* 1.17.1 */ || PROTOCOL_VERSION == 757 /* 1.18/.1 */ ||  \
      PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */ ||  \
      PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x06;
#else
#error "Protocol version not implemented"
#endif

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
