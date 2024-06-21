#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketPos : public BaseMessage<ClientboundMoveEntityPacketPos>
    {
    public:

        static constexpr std::string_view packet_name = "Move Entity Pos";

        DECLARE_FIELDS(
            (VarInt,   short, short, short, bool),
            (EntityId, XA,    YA,    ZA,    OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(XA);
        GETTER_SETTER(YA);
        GETTER_SETTER(ZA);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
