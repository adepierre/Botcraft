#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"

namespace ProtocolCraft
{
    class ServerboundChatSessionUpdatePacket : public BaseMessage<ServerboundChatSessionUpdatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */ ||  \
      PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x07;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Session Update";

        DECLARE_FIELDS_TYPES(RemoteChatSessionData);
        DECLARE_FIELDS_NAMES(ChatSession);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ChatSession);
    };
} //ProtocolCraft
#endif
