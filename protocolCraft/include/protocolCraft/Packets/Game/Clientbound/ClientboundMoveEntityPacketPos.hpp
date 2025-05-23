#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketPos : public BasePacket<ClientboundMoveEntityPacketPos>
    {
    public:
        static constexpr std::string_view packet_name = "Move Entity Pos";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(XA, short);
        SERIALIZED_FIELD(YA, short);
        SERIALIZED_FIELD(ZA, short);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
