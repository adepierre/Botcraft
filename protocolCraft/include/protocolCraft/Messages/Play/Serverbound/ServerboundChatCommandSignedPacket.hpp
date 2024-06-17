#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include <string>
#include <map>
#include <vector>

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace ProtocolCraft
{
    class ServerboundChatCommandSignedPacket : public BaseMessage<ServerboundChatCommandSignedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Command Signed";

        DECLARE_FIELDS(
            (std::string, long long int, long long int, std::map<std::string, std::vector<unsigned char>>, LastSeenMessagesUpdate),
            (Command,     Timestamp,     Salt,          ArgumentSignatures,                                LastSeenMessages)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Command);
        GETTER_SETTER(Timestamp);
        GETTER_SETTER(Salt);
        GETTER_SETTER(ArgumentSignatures);
        GETTER_SETTER(LastSeenMessages);
    };
} //ProtocolCraft
#endif
