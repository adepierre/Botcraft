#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "botcraft/Game/Entities/entities/vehicle/AbstractBoatEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractBoatEntity::metadata_count> AbstractBoatEntity::metadata_names{ {
        "data_id_paddle_left",
        "data_id_paddle_right",
        "data_id_bubble_time",
    } };

    AbstractBoatEntity::AbstractBoatEntity()
    {
        // Initialize all metadata with default values
        SetDataIdPaddleLeft(false);
        SetDataIdPaddleRight(false);
        SetDataIdBubbleTime(0);
    }

    AbstractBoatEntity::~AbstractBoatEntity()
    {

    }


    bool AbstractBoatEntity::IsAbstractBoat() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractBoatEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = VehicleEntity::Serialize();

        output["metadata"]["data_id_paddle_left"] = GetDataIdPaddleLeft();
        output["metadata"]["data_id_paddle_right"] = GetDataIdPaddleRight();
        output["metadata"]["data_id_bubble_time"] = GetDataIdBubbleTime();


        return output;
    }


    void AbstractBoatEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            VehicleEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AbstractBoatEntity::GetDataIdPaddleLeft() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_paddle_left"));
    }

    bool AbstractBoatEntity::GetDataIdPaddleRight() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_id_paddle_right"));
    }

    int AbstractBoatEntity::GetDataIdBubbleTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_id_bubble_time"));
    }


    void AbstractBoatEntity::SetDataIdPaddleLeft(const bool data_id_paddle_left)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_paddle_left"] = data_id_paddle_left;
    }

    void AbstractBoatEntity::SetDataIdPaddleRight(const bool data_id_paddle_right)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_paddle_right"] = data_id_paddle_right;
    }

    void AbstractBoatEntity::SetDataIdBubbleTime(const int data_id_bubble_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_id_bubble_time"] = data_id_bubble_time;
    }
}
#endif
