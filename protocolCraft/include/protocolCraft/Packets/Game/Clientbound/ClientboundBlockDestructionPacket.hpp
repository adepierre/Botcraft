#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockDestructionPacket : public BasePacket<ClientboundBlockDestructionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Break Animation";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Progress, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
