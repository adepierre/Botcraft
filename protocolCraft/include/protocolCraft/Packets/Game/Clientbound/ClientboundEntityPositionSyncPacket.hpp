#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/PositionMoveRotation.hpp"

namespace ProtocolCraft
{
    class ClientboundEntityPositionSyncPacket : public BasePacket<ClientboundEntityPositionSyncPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Entity Position Sync";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Values, PositionMoveRotation);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
