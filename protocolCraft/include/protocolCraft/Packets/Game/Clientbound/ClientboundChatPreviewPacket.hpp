#if PROTOCOL_VERSION > 758 /* > 1.18.2 */ && PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPreviewPacket : public BasePacket<ClientboundChatPreviewPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat Preview";

        SERIALIZED_FIELD(QueryId, int);
        SERIALIZED_FIELD(Preview, std::optional<Chat>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
