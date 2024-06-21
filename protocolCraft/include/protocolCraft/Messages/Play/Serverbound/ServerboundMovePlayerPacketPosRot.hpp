#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPosRot : public BaseMessage<ServerboundMovePlayerPacketPosRot>
    {
    public:

        static constexpr std::string_view packet_name = "Move Player PosRot";

        DECLARE_FIELDS(
            (double, double, double, float, float, bool),
            (X,      Y,      Z,      YRot,  XRot,  OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
