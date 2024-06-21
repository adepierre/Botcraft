#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPreviewPacket : public BaseMessage<ClientboundChatPreviewPacket>
    {
    public:

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
