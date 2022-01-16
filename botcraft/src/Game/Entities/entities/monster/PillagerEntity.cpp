#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/monster/PillagerEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PillagerEntity::metadata_count> PillagerEntity::metadata_names{ {
        "is_charging_crossbow",
    } };

    PillagerEntity::PillagerEntity()
    {
        // Initialize all metadata with default values
        SetIsChargingCrossbow(false);
    }

    PillagerEntity::~PillagerEntity()
    {

    }


    std::string PillagerEntity::GetName() const
    {
        return "Pillager";
    }

    EntityType PillagerEntity::GetType() const
    {
        return EntityType::Pillager;
    }

    double PillagerEntity::GetWidth() const
    {
        return 0.6;
    }

    double PillagerEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string PillagerEntity::GetClassName()
    {
        return "Pillager";
    }

    EntityType PillagerEntity::GetClassType()
    {
        return EntityType::Pillager;
    }


    nlohmann::json PillagerEntity::Serialize() const
    {
        nlohmann::json output = AbstractIllagerEntity::Serialize();

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
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool PillagerEntity::GetIsChargingCrossbow() const
    {
        return std::any_cast<bool>(metadata.at("is_charging_crossbow"));
    }


    void PillagerEntity::SetIsChargingCrossbow(const bool is_charging_crossbow)
    {
        metadata["is_charging_crossbow"] = is_charging_crossbow;
    }

}
#endif
