#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/Waypoints/TrackedWaypoint.hpp"

#include "protocolCraft/Types/Waypoints/AzimuthWaypoint.hpp"
#include "protocolCraft/Types/Waypoints/ChunkWaypoint.hpp"
#include "protocolCraft/Types/Waypoints/EmptyWaypoint.hpp"
#include "protocolCraft/Types/Waypoints/Vec3iWaypoint.hpp"

#include "protocolCraft/Types/Waypoints/WaypointIcon.hpp"

namespace ProtocolCraft
{
    DEFINE_NETWORK_TYPE(AzimuthWaypoint);
    DEFINE_NETWORK_TYPE(ChunkWaypoint);
    DEFINE_NETWORK_TYPE(EmptyWaypoint);
    DEFINE_NETWORK_TYPE(Vec3iWaypoint);

    DEFINE_NETWORK_TYPE(WaypointIcon);

    std::shared_ptr<TrackedWaypointData> TrackedWaypoint::CreateTrackedWaypointData(const TrackedWaypointDataType type)
    {
        switch (type)
        {
        case TrackedWaypointDataType::Empty:
            return std::make_shared<EmptyWaypoint>();
        case TrackedWaypointDataType::Vec3i:
            return std::make_shared<Vec3iWaypoint>();
        case TrackedWaypointDataType::Chunk:
            return std::make_shared<ChunkWaypoint>();
        case TrackedWaypointDataType::Azimuth:
            return std::make_shared<AzimuthWaypoint>();
        default: // Should not happen
            throw std::runtime_error("Unable to create TrackedWaypointData with id: " + std::to_string(static_cast<int>(type)) + ".");
            return nullptr;
        }
    }

    DEFINE_NETWORK_TYPE(TrackedWaypoint);
}
#endif
