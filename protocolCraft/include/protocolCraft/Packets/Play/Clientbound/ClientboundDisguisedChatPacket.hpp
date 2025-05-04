#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"

namespace ProtocolCraft
{
    class ClientboundDisguisedChatPacket : public BasePacket<ClientboundDisguisedChatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Disguised Chat";

        SERIALIZED_FIELD(Message, Chat);
        SERIALIZED_FIELD(ChatType, ChatTypeBoundNetwork);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
