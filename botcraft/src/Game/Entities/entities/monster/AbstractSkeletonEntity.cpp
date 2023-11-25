#include "botcraft/Game/Entities/entities/monster/AbstractSkeletonEntity.hpp"

#include <mutex>

namespace Botcraft
{
#if PROTOCOL_VERSION < 405 /* < 1.14 */
    const std::array<std::string, AbstractSkeletonEntity::metadata_count> AbstractSkeletonEntity::metadata_names{ {
        "is_swinging_arms",
    } };
#endif

    AbstractSkeletonEntity::AbstractSkeletonEntity()
    {
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        // Initialize all metadata with default values
        SetIsSwingingArms(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
    }

    AbstractSkeletonEntity::~AbstractSkeletonEntity()
    {

    }

    bool AbstractSkeletonEntity::IsAbstractSkeleton() const
    {
        return true;
    }


#if PROTOCOL_VERSION < 405 /* < 1.14 */
    ProtocolCraft::Json::Value AbstractSkeletonEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["is_swinging_arms"] = GetIsSwingingArms();

        return output;
    }


    void AbstractSkeletonEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AbstractSkeletonEntity::GetIsSwingingArms() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("is_swinging_arms"));
    }


    void AbstractSkeletonEntity::SetIsSwingingArms(const bool is_swinging_arms)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["is_swinging_arms"] = is_swinging_arms;
    }
#endif

}
