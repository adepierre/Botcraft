#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveVehiclePacket : public BaseMessage<ClientboundMoveVehiclePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Move Vehicle";

        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
