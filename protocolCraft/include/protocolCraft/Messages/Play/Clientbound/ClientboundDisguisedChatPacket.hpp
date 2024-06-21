#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"
#include "protocolCraft/Types/Chat/ChatTypeBoundNetwork.hpp"

namespace ProtocolCraft
{
    class ClientboundDisguisedChatPacket : public BaseMessage<ClientboundDisguisedChatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Disguised Chat";

        DECLARE_FIELDS(
            (Chat, ChatTypeBoundNetwork),
            (Message, ChatType)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Message);
        GETTER_SETTER(ChatType);
    };
} //ProtocolCraft
#endif
