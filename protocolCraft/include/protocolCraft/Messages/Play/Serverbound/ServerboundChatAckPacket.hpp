#if PROTOCOL_VERSION > 759 /* > 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/LastSeenMessagesUpdate.hpp"

namespace ProtocolCraft
{
    class ServerboundChatAckPacket : public BaseMessage<ServerboundChatAckPacket>
    {
    public:
#if   PROTOCOL_VERSION == 760 /* 1.19.1/2 */ || PROTOCOL_VERSION == 761 /* 1.19.3 */ ||  \
      PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */ ||  \
      PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x03;
#else
#error "Protocol version not implemented"
#endif

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
