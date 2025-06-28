#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/Waypoints/TrackedWaypoint.hpp"

namespace ProtocolCraft
{
    class ClientboundTrackedWaypointPacket : public BasePacket<ClientboundTrackedWaypointPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Tracked Waypoint";

        SERIALIZED_FIELD(Operation, VarInt);
        SERIALIZED_FIELD(Waypoint, TrackedWaypoint);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
