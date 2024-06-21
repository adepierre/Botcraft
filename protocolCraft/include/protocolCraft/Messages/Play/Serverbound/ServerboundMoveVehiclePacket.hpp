#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMoveVehiclePacket : public BaseMessage<ServerboundMoveVehiclePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Move Vehicle";

        DECLARE_FIELDS(
            (double, double, double, float, float),
            (X,      Y,      Z,      YRot,  XRot)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
    };
} //ProtocolCraft
