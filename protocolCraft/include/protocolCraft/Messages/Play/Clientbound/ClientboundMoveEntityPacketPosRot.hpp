#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketPosRot : public BaseMessage<ClientboundMoveEntityPacketPosRot>
    {
    public:

        static constexpr std::string_view packet_name = "Move Entity PosRot";

        DECLARE_FIELDS(
            (VarInt,   short, short, short, unsigned char, unsigned char, bool),
            (EntityId, XA,    YA,    ZA,    YRot,          XRot,          OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(XA);
        GETTER_SETTER(YA);
        GETTER_SETTER(ZA);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
