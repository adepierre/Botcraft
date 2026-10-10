#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Utilities/DynamicType.hpp"

#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Waypoints/WaypointIcon.hpp"

namespace ProtocolCraft
{
    enum class TrackedWaypointDataType
    {
        None = -1,
        Empty,
        Vec3i,
        Chunk,
        Azimuth,
        NUM_TRACKED_WAYPOINT_DATA_TYPES
    };

    class TrackedWaypointData;

    class TrackedWaypoint : public NetworkType
    {
    private:
        static std::shared_ptr<TrackedWaypointData> CreateTrackedWaypointData(const TrackedWaypointDataType type);

        SERIALIZED_FIELD(Identifier, Either<UUID, std::string>);
        SERIALIZED_FIELD(Icon, WaypointIcon);
        SERIALIZED_DYNAMIC_FIELD(TrackedWaypoint, Type, Data, TrackedWaypointData, TrackedWaypoint::CreateTrackedWaypointData, Internal::DiffType<TrackedWaypointDataType, VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
