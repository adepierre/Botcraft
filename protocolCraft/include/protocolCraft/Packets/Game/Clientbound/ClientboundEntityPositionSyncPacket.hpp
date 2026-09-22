#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 777 /* < 26.3 */
#include "protocolCraft/Types/PositionMoveRotation.hpp"
#else
#include "protocolCraft/Types/PositionPath.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundEntityPositionSyncPacket : public BasePacket<ClientboundEntityPositionSyncPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Entity Position Sync";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(Values, PositionMoveRotation);
#else
        SERIALIZED_FIELD(Position, PositionPath);
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
#endif
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
