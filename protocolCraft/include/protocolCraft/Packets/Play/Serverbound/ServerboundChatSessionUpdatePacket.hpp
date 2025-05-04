#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/RemoteChatSessionData.hpp"

namespace ProtocolCraft
{
    class ServerboundChatSessionUpdatePacket : public BasePacket<ServerboundChatSessionUpdatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Chat Session Update";

        SERIALIZED_FIELD(ChatSession, RemoteChatSessionData);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
