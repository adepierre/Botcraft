#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/PositionMoveRotation.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundPlayerPositionPacket : public BasePacket<ClientboundPlayerPositionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Position";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
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
#else
        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Change, PositionMoveRotation);
        SERIALIZED_FIELD(Relatives, int);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
