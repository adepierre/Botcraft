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

    TrackedWaypoint& TrackedWaypoint::SetType(const TrackedWaypointType type)
    {
        if (type <= TrackedWaypointType::None || type >= TrackedWaypointType::NUM_WAYPOINT_TYPES)
        {
            throw std::runtime_error("Unable to create particle with id: " + std::to_string(static_cast<int>(type)) + ".");
        }
        Type = type;
        switch (Type)
        {
        case TrackedWaypointType::Empty:
            Data = std::make_shared<EmptyWaypoint>();
            break;
        case TrackedWaypointType::Vec3i:
            Data = std::make_shared<Vec3iWaypoint>();
            break;
        case TrackedWaypointType::Chunk:
            Data = std::make_shared<ChunkWaypoint>();
            break;
        case TrackedWaypointType::Azimuth:
            Data = std::make_shared<AzimuthWaypoint>();
            break;
        default: // Should not happen
            throw std::runtime_error("Unable to create TrackedWaypointData with id: " + std::to_string(static_cast<int>(Type)) + ".");
            Data = nullptr;
            break;
        }
        return *this;
    }

    void TrackedWaypoint::ReadImpl(ReadIterator& iter, size_t& length)
    {
        Type = ReadData<TrackedWaypointType, VarInt>(iter, length);
        SetType(Type);
        if (Data != nullptr)
        {
            Data->Read(iter, length);
        }
    }

    void TrackedWaypoint::WriteImpl(WriteContainer& container) const
    {
        WriteData<TrackedWaypointType, VarInt>(Type, container);
        if (Data != nullptr)
        {
            Data->Write(container);
        }
    }

    Json::Value TrackedWaypoint::SerializeImpl() const
    {
        Json::Value output;

        output[std::string(field_name<Type_index>)] = Type;
        output[std::string(field_name<Data_index>)] = Data == nullptr ? Json::Object() : Data->Serialize();

        return output;
    }
}
#endif
