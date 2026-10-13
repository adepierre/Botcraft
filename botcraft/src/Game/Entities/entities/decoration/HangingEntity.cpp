#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"

#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
    HangingEntity::HangingEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        SetDataDirection(static_cast<int>(Direction::South));
#endif

    }

    HangingEntity::~HangingEntity()
    {

    }

    bool HangingEntity::IsHangingEntity() const
    {
        return true;
    }


#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
    ProtocolCraft::Json::Value HangingEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = BlockAttachedEntity::Serialize();

        output["metadata"]["data_direction"] = GetDataDirection();

        return output;
    }

    int HangingEntity::GetDataDirection() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_direction"));
    }


    void HangingEntity::SetDataDirection(const int data_direction)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_direction"), data_direction);
    }
#endif

}
