#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockEventPacket : public BaseMessage<ClientboundBlockEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Event";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(B0, unsigned char);
        SERIALIZED_FIELD(B1, unsigned char);
        SERIALIZED_FIELD(Block, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
