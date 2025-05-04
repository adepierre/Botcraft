#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPacket : public BasePacket<ClientboundChatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat";

        SERIALIZED_FIELD(Message, Chat);
        SERIALIZED_FIELD(Type, char);
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
        SERIALIZED_FIELD(Sender, UUID);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
