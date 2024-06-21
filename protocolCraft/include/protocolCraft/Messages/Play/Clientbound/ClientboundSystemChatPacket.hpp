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

#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        DECLARE_FIELDS(
            (Chat,    VarInt),
            (Content, TypeId)
        );
#else
        DECLARE_FIELDS(
            (Chat,    bool),
            (Content, Overlay)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Content);
#if PROTOCOL_VERSION < 760 /* < 1.19.1 */
        GETTER_SETTER(TypeId);
#else
        GETTER_SETTER(Overlay);
#endif
    };
} //ProtocolCraft
#endif
