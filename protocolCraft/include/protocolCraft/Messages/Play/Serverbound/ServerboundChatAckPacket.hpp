#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace ProtocolCraft
{
    class ServerboundChatAckPacket : public BaseMessage<ServerboundChatAckPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat Ack";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(LastSeenMessages, LastSeenMessagesUpdate);
#else
        SERIALIZED_FIELD(Offset, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
