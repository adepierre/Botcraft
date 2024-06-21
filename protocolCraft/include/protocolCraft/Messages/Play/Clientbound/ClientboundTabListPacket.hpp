#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundTabListPacket : public BaseMessage<ClientboundTabListPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Tab List";

        DECLARE_FIELDS(
            (Chat,   Chat),
            (Header, Footer)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Header);
        GETTER_SETTER(Footer);
    };
} //ProtocolCraft
