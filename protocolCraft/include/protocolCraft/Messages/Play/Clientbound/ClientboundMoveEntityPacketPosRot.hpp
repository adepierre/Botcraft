#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketPosRot : public BaseMessage<ClientboundMoveEntityPacketPosRot>
    {
    public:
        static constexpr std::string_view packet_name = "Move Entity PosRot";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(XA, short);
        SERIALIZED_FIELD(YA, short);
        SERIALIZED_FIELD(ZA, short);
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(XRot, unsigned char);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
