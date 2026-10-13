#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "botcraft/Game/Entities/entities/vehicle/boat/AbstractBoatEntity.hpp"

namespace Botcraft
{
    AbstractBoatEntity::AbstractBoatEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
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


    bool AbstractBoatEntity::GetDataIdPaddleLeft() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_left"));
    }

    bool AbstractBoatEntity::GetDataIdPaddleRight() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_right"));
    }

    int AbstractBoatEntity::GetDataIdBubbleTime() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_bubble_time"));
    }


    void AbstractBoatEntity::SetDataIdPaddleLeft(const bool data_id_paddle_left)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_left"), data_id_paddle_left);
    }

    void AbstractBoatEntity::SetDataIdPaddleRight(const bool data_id_paddle_right)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_paddle_right"), data_id_paddle_right);
    }

    void AbstractBoatEntity::SetDataIdBubbleTime(const int data_id_bubble_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_id_bubble_time"), data_id_bubble_time);
    }
}
#endif
