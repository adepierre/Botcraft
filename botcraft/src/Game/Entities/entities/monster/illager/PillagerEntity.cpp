#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/monster/illager/PillagerEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PillagerEntity::metadata_count> PillagerEntity::metadata_names{ {
        "is_charging_crossbow",
    } };

    PillagerEntity::PillagerEntity()
    {
        // Initialize all metadata with default values
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


    void PillagerEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractIllagerEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool PillagerEntity::GetIsChargingCrossbow() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("is_charging_crossbow"));
    }


    void PillagerEntity::SetIsChargingCrossbow(const bool is_charging_crossbow)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["is_charging_crossbow"] = is_charging_crossbow;
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
