#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PiglinEntity::metadata_count> PiglinEntity::metadata_names{ {
        "data_baby_id",
#if PROTOCOL_VERSION < 737
        "data_immune_to_zombification",
#endif
        "data_is_charging_crossbow",
        "data_is_dancing",
    } };

    PiglinEntity::PiglinEntity()
    {
        // Initialize all metadata with default values
        SetDataBabyId(false);
#if PROTOCOL_VERSION < 737
        SetDataImmuneToZombification(false);
#endif
        SetDataIsChargingCrossbow(false);
        SetDataIsDancing(false);
    }

    PiglinEntity::~PiglinEntity()
    {

    }


    std::string PiglinEntity::GetName() const
    {
        return "Piglin";
    }

    EntityType PiglinEntity::GetType() const
    {
        return EntityType::Piglin;
    }

    AABB PiglinEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double PiglinEntity::GetWidth() const
    {
        return 0.6;
    }

    double PiglinEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string PiglinEntity::GetClassName()
    {
        return "Piglin";
    }

    EntityType PiglinEntity::GetClassType()
    {
        return EntityType::Piglin;
    }


    nlohmann::json PiglinEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 736
        nlohmann::json output = AbstractPiglinEntity::Serialize();
#else
        nlohmann::json output = MonsterEntity::Serialize();
#endif

        output["data_baby_id"] = GetDataBabyId();
#if PROTOCOL_VERSION < 737
        output["data_immune_to_zombification"] = GetDataImmuneToZombification();
#endif
        output["data_is_charging_crossbow"] = GetDataIsChargingCrossbow();
        output["data_is_dancing"] = GetDataIsDancing();

        return output;
    }


    void PiglinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 736
            AbstractPiglinEntity::SetMetadataValue(index, value);
#else
            MonsterEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool PiglinEntity::GetDataBabyId() const
    {
        return std::any_cast<bool>(metadata.at("data_baby_id"));
    }

#if PROTOCOL_VERSION < 737
    bool PiglinEntity::GetDataImmuneToZombification() const
    {
        return std::any_cast<bool>(metadata.at("data_immune_to_zombification"));
    }
#endif

    bool PiglinEntity::GetDataIsChargingCrossbow() const
    {
        return std::any_cast<bool>(metadata.at("data_is_charging_crossbow"));
    }

    bool PiglinEntity::GetDataIsDancing() const
    {
        return std::any_cast<bool>(metadata.at("data_is_dancing"));
    }


    void PiglinEntity::SetDataBabyId(const bool data_baby_id)
    {
        metadata["data_baby_id"] = data_baby_id;
    }

#if PROTOCOL_VERSION < 737
    void PiglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        metadata["data_immune_to_zombification"] = data_immune_to_zombification;
    }
#endif
    void PiglinEntity::SetDataIsChargingCrossbow(const bool data_is_charging_crossbow)
    {
        metadata["data_is_charging_crossbow"] = data_is_charging_crossbow;
    }

    void PiglinEntity::SetDataIsDancing(const bool data_is_dancing)
    {
        metadata["data_is_dancing"] = data_is_dancing;
    }

}
#endif
