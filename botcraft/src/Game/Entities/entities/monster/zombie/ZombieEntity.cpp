#include "botcraft/Game/Entities/entities/monster/zombie/ZombieEntity.hpp"

namespace Botcraft
{
    ZombieEntity::ZombieEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataBabyId(false);
        SetDataSpecialTypeId(0);
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        SetDataAreHandsUp(false);
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        SetDataDrownedConversionId(false);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 35.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.23) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
        attributes.insert({ EntityAttribute::Type::Armor, EntityAttribute(EntityAttribute::Type::Armor, 2.0) });
        attributes.insert({ EntityAttribute::Type::ZombieSpawnReinforcementsChance, EntityAttribute(EntityAttribute::Type::ZombieSpawnReinforcementsChance, 0.0) });
    }

    ZombieEntity::~ZombieEntity()
    {

    }


    std::string ZombieEntity::GetName() const
    {
        return "zombie";
    }

    EntityType ZombieEntity::GetType() const
    {
        return EntityType::Zombie;
    }


    std::string ZombieEntity::GetClassName()
    {
        return "zombie";
    }

    EntityType ZombieEntity::GetClassType()
    {
        return EntityType::Zombie;
    }


    ProtocolCraft::Json::Value ZombieEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_baby_id"] = GetDataBabyId();
        output["metadata"]["data_special_type_id"] = GetDataSpecialTypeId();
#if PROTOCOL_VERSION < 405 /* < 1.14 */
        output["metadata"]["data_are_hands_up"] = GetDataAreHandsUp();
#endif
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        output["metadata"]["data_drowned_conversion_id"] = GetDataDrownedConversionId();
#endif

        output["attributes"]["spawn_reinforcements"] = GetAttributeSpawnReinforcementsChanceValue();

        return output;
    }


    bool ZombieEntity::GetDataBabyId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"));
    }

    int ZombieEntity::GetDataSpecialTypeId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_special_type_id"));
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    bool ZombieEntity::GetDataAreHandsUp() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_are_hands_up"));
    }
#endif

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    bool ZombieEntity::GetDataDrownedConversionId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_drowned_conversion_id"));
    }
#endif


    void ZombieEntity::SetDataBabyId(const bool data_baby_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"), data_baby_id);
    }

    void ZombieEntity::SetDataSpecialTypeId(const int data_special_type_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_special_type_id"), data_special_type_id);
    }

#if PROTOCOL_VERSION < 405 /* < 1.14 */
    void ZombieEntity::SetDataAreHandsUp(const bool data_are_hands_up)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_are_hands_up"), data_are_hands_up);
    }
#endif

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
    void ZombieEntity::SetDataDrownedConversionId(const bool data_drowned_conversion_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_drowned_conversion_id"), data_drowned_conversion_id);
    }
#endif


    double ZombieEntity::GetAttributeSpawnReinforcementsChanceValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::ZombieSpawnReinforcementsChance).GetValue();
    }


    double ZombieEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double ZombieEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
