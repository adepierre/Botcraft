#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundDisconnectPacket : public BasePacket<ClientboundDisconnectPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Disconnect";

        SERIALIZED_FIELD(Reason, Chat);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
