#include "botcraft/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.hpp"

namespace Botcraft
{
    AbstractSkeletonEntity::AbstractSkeletonEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
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


    bool AbstractSkeletonEntity::GetIsSwingingArms() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("is_swinging_arms"));
    }

    void AbstractSkeletonEntity::SetIsSwingingArms(const bool is_swinging_arms)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("is_swinging_arms"), is_swinging_arms);
    }
#endif

}
