#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundChatPacket : public BaseMessage<ClientboundChatPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Chat";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (Chat,    char),
            (Message, Type)
        );
#else
        DECLARE_FIELDS(
            (Chat,    char, UUID),
            (Message, Type, Sender)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Message);
        GETTER_SETTER(Type);
#if PROTOCOL_VERSION > 717 /* > 1.15.2 */
        GETTER_SETTER(Sender);
#endif
    };
} //ProtocolCraft
#endif
