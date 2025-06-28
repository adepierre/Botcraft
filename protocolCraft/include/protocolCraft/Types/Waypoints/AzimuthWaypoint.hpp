#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/Types/Waypoints/TrackedWaypointData.hpp"

namespace ProtocolCraft
{
    class AzimuthWaypoint : public TrackedWaypointData
    {
        SERIALIZED_FIELD(Angle, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
