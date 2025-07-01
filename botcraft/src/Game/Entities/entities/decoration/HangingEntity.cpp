#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"

#include "botcraft/Game/Enums.hpp"

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#include <mutex>
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
    const std::array<std::string, HangingEntity::metadata_count> HangingEntity::metadata_names{ {
        "data_direction",
    } };
#endif

    HangingEntity::HangingEntity()
    {
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        // Initialize all metadata with default values
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

    void HangingEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            BlockAttachedEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }


    int HangingEntity::GetDataDirection() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_direction"));
    }


    void HangingEntity::SetDataDirection(const int data_direction)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_direction"] = data_direction;
    }
#endif

}
