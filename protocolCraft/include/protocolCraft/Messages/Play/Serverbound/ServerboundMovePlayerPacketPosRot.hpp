#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketPosRot : public BaseMessage<ServerboundMovePlayerPacketPosRot>
    {
    public:
        static constexpr std::string_view packet_name = "Move Player PosRot";

        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
