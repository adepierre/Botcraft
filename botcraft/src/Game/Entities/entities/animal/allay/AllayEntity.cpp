#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/animal/allay/AllayEntity.hpp"

namespace Botcraft
{
    AllayEntity::AllayEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION > 759 /* > 1.19 */
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataDancing(true);
        SetDataCanDuplicate(true);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 20.0) });
        attributes.insert({ EntityAttribute::Type::FlyingSpeed, EntityAttribute(EntityAttribute::Type::FlyingSpeed, 0.1) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.1) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 48.0) });
#endif
    }

    AllayEntity::~AllayEntity()
    {

    }


    std::string AllayEntity::GetName() const
    {
        return "allay";
    }

    EntityType AllayEntity::GetType() const
    {
        return EntityType::Allay;
    }


    std::string AllayEntity::GetClassName()
    {
        return "allay";
    }

    EntityType AllayEntity::GetClassType()
    {
        return EntityType::Allay;
    }


#if PROTOCOL_VERSION > 759 /* > 1.19 */
    ProtocolCraft::Json::Value AllayEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = PathfinderMobEntity::Serialize();

        output["metadata"]["data_dancing"] = GetDataDancing();
        output["metadata"]["data_can_duplicate"] = GetDataCanDuplicate();

        output["attributes"]["flying_speed"] = GetAttributeFlyingSpeedValue();
        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    bool AllayEntity::GetDataDancing() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_dancing"));
    }

    bool AllayEntity::GetDataCanDuplicate() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_can_duplicate"));
    }


    void AllayEntity::SetDataDancing(const bool data_dancing)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_dancing"), data_dancing);
    }

    void AllayEntity::SetDataCanDuplicate(const bool data_can_duplicate)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_can_duplicate"), data_can_duplicate);
    }
#endif

    double AllayEntity::GetAttributeFlyingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FlyingSpeed).GetValue();
    }

    double AllayEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }

    double AllayEntity::GetWidthImpl() const
    {
        return 0.35;
    }

    double AllayEntity::GetHeightImpl() const
    {
        return 0.6;
    }

}
#endif
