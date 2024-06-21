#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDisconnectPacket : public BaseMessage<ClientboundDisconnectPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Disconnect";

        DECLARE_FIELDS(
            (Chat),
            (Reason)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Reason);
    };
} //ProtocolCraft
