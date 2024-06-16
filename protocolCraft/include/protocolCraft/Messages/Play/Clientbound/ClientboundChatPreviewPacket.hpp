#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPreviewPacket : public BaseMessage<ClientboundChatPreviewPacket>
    {
    public:
#if   PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Chat Preview";

        DECLARE_FIELDS(
            (int,     std::optional<Chat>),
            (QueryId, Preview)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(QueryId);
        GETTER_SETTER(Preview);
    };
} //ProtocolCraft
#endif
