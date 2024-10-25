#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketRot : public BaseMessage<ClientboundMoveEntityPacketRot>
    {
    public:
        static constexpr std::string_view packet_name = "Move Entity Rot";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(XRot, unsigned char);
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
