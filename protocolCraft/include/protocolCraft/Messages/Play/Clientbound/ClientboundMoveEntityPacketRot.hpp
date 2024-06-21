#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketRot : public BaseMessage<ClientboundMoveEntityPacketRot>
    {
    public:

        static constexpr std::string_view packet_name = "Move Entity Rot";

        DECLARE_FIELDS(
            (VarInt,   unsigned char, unsigned char, bool),
            (EntityId, XRot,          YRot,          OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(XRot);
        GETTER_SETTER(YRot);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
