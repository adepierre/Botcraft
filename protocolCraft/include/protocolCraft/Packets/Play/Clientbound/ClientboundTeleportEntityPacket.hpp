#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/PositionMoveRotation.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundTeleportEntityPacket : public BasePacket<ClientboundTeleportEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Teleport Entity";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(XRot, unsigned char);
#else
        SERIALIZED_FIELD(Change, PositionMoveRotation);
        SERIALIZED_FIELD(Relatives, int);
#endif
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
