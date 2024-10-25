#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundSystemChatPacket : public BaseMessage<ClientboundSystemChatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "System Chat";

        SERIALIZED_FIELD(Content, Chat);
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        SERIALIZED_FIELD(TypeId, VarInt);
#else
        SERIALIZED_FIELD(Overlay, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
