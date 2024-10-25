#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerPositionPacket : public BaseMessage<ClientboundPlayerPositionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Position";

        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
        SERIALIZED_FIELD(RelativeArguments, char);
        SERIALIZED_FIELD(Id_, VarInt);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        SERIALIZED_FIELD(DismountVehicle, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
