#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/monster/illager/PillagerEntity.hpp"

namespace Botcraft
{
    PillagerEntity::PillagerEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetIsChargingCrossbow(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.35) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 24.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 5.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 32.0) });
    }

    PillagerEntity::~PillagerEntity()
    {

    }


    std::string PillagerEntity::GetName() const
    {
        return "pillager";
    }

    EntityType PillagerEntity::GetType() const
    {
        return EntityType::Pillager;
    }


    std::string PillagerEntity::GetClassName()
    {
        return "pillager";
    }

    EntityType PillagerEntity::GetClassType()
    {
        return EntityType::Pillager;
    }


    ProtocolCraft::Json::Value PillagerEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractIllagerEntity::Serialize();

        output["metadata"]["is_charging_crossbow"] = GetIsChargingCrossbow();

        return output;
    }


    bool PillagerEntity::GetIsChargingCrossbow() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("is_charging_crossbow"));
    }


    void PillagerEntity::SetIsChargingCrossbow(const bool is_charging_crossbow)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("is_charging_crossbow"), is_charging_crossbow);
    }


    double PillagerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double PillagerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
