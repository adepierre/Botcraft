#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 759 /* > 1.19 */
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"
#endif

namespace ProtocolCraft
{
    class ServerboundChatCommandPacket : public BaseMessage<ServerboundChatCommandPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x03;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */ ||  \
      PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x04;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Command";

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS_TYPES(std::string, long long int, std::map<std::string, std::vector<unsigned char>>, bool);
        DECLARE_FIELDS_NAMES(Command,     Timestamp,     ArgumentSignatures,                                SignedPreview);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS_TYPES(std::string, long long int, long long int, std::map<std::string, std::vector<unsigned char>>, bool,          LastSeenMessagesUpdate);
        DECLARE_FIELDS_NAMES(Command,     Timestamp,     Salt,          ArgumentSignatures,                                SignedPreview, LastSeenMessages);
#elif PROTOCOL_VERSION < 766 /* < 1.20.5 */
        DECLARE_FIELDS_TYPES(std::string, long long int, long long int, std::map<std::string, std::vector<unsigned char>>, LastSeenMessagesUpdate);
        DECLARE_FIELDS_NAMES(Command,     Timestamp,     Salt,          ArgumentSignatures,                                LastSeenMessages);
#else
        DECLARE_FIELDS_TYPES(std::string);
        DECLARE_FIELDS_NAMES(Command);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Command);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Timestamp);
        GETTER_SETTER(ArgumentSignatures);
#endif
#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(SignedPreview);
#endif
#if PROTOCOL_VERSION > 759 /* > 1.19 */ && PROTOCOL_VERSION < 766 /* < 1.20.5 */
        GETTER_SETTER(Salt);
        GETTER_SETTER(LastSeenMessages);
#endif
    };
} //ProtocolCraft
#endif
