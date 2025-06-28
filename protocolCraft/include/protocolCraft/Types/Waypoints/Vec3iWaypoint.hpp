#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/Types/Waypoints/TrackedWaypointData.hpp"

namespace ProtocolCraft
{
    class Vec3iWaypoint : public TrackedWaypointData
    {
        SERIALIZED_FIELD(Vector, std::array<VarInt, 3>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
