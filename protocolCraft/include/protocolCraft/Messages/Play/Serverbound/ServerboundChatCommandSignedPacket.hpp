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
        static constexpr std::string_view packet_name = "Chat Command Signed";

        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(Timestamp, long long int);
        SERIALIZED_FIELD(Salt, long long int);
        SERIALIZED_FIELD(ArgumentSignatures, std::map<std::string, std::vector<unsigned char>>);
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
