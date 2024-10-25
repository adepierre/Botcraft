#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockUpdatePacket : public BaseMessage<ClientboundBlockUpdatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Update";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Blockstate, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
