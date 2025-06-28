#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include <memory>

#include "protocolCraft/NetworkType.hpp"

#include "protocolCraft/Types/Either.hpp"
#include "protocolCraft/Types/Waypoints/WaypointIcon.hpp"

namespace ProtocolCraft
{
    enum class TrackedWaypointType
    {
        None = -1,
        Empty,
        Vec3i,
        Chunk,
        Azimuth,
        NUM_WAYPOINT_TYPES
    };

    class TrackedWaypointData;

    class TrackedWaypoint : public NetworkType
    {
        SERIALIZED_FIELD(Identifier, Either<UUID, std::string>);
        SERIALIZED_FIELD(Icon, WaypointIcon);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Type, Internal::DiffType<TrackedWaypointType, VarInt>);
        SERIALIZED_FIELD_WITHOUT_GETTER_SETTER(Data, std::shared_ptr<TrackedWaypointData>);

        GETTER(Type);
        GETTER(Data);

        TrackedWaypoint& SetType(const TrackedWaypointType type);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
