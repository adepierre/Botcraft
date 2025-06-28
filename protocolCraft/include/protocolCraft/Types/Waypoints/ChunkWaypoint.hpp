#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/Types/Waypoints/TrackedWaypointData.hpp"

namespace ProtocolCraft
{
    class ChunkWaypoint : public TrackedWaypointData
    {
        SERIALIZED_FIELD(X, VarInt);
        SERIALIZED_FIELD(Z, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
