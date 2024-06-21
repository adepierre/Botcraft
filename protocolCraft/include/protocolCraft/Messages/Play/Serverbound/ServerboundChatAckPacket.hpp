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
        DECLARE_FIELDS(
            (LastSeenMessagesUpdate),
            (LastSeenMessages)
        );
#else
        DECLARE_FIELDS(
            (VarInt),
            (Offset)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        GETTER_SETTER(LastSeenMessages);
#else
        GETTER_SETTER(Offset);
#endif
    };
} //ProtocolCraft
#endif
