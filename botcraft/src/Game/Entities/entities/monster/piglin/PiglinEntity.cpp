#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinEntity.hpp"

namespace Botcraft
{
    const std::array<std::string, PiglinEntity::metadata_count> PiglinEntity::metadata_names{ {
        "data_baby_id",
#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
        "data_immune_to_zombification",
#endif
        "data_is_charging_crossbow",
        "data_is_dancing",
    } };

    PiglinEntity::PiglinEntity()
    {
        // Initialize all metadata with default values
        SetDataBabyId(false);
#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
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
        return "piglin";
    }

    EntityType PiglinEntity::GetType() const
    {
        return EntityType::Piglin;
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
        return "piglin";
    }

    EntityType PiglinEntity::GetClassType()
    {
        return EntityType::Piglin;
    }


    ProtocolCraft::Json::Value PiglinEntity::Serialize() const
    {
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
        ProtocolCraft::Json::Value output = AbstractPiglinEntity::Serialize();
#else
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();
#endif

        output["metadata"]["data_baby_id"] = GetDataBabyId();
#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
        output["metadata"]["data_immune_to_zombification"] = GetDataImmuneToZombification();
#endif
        output["metadata"]["data_is_charging_crossbow"] = GetDataIsChargingCrossbow();
        output["metadata"]["data_is_dancing"] = GetDataIsDancing();

        return output;
    }


    void PiglinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
#if PROTOCOL_VERSION > 736 /* > 1.16.1 */
            AbstractPiglinEntity::SetMetadataValue(index, value);
#else
            MonsterEntity::SetMetadataValue(index, value);
#endif
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool PiglinEntity::GetDataBabyId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_baby_id"));
    }

#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
    bool PiglinEntity::GetDataImmuneToZombification() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_immune_to_zombification"));
    }
#endif

    bool PiglinEntity::GetDataIsChargingCrossbow() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_is_charging_crossbow"));
    }

    bool PiglinEntity::GetDataIsDancing() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_is_dancing"));
    }


    void PiglinEntity::SetDataBabyId(const bool data_baby_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_baby_id"] = data_baby_id;
    }

#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
    void PiglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_immune_to_zombification"] = data_immune_to_zombification;
    }
#endif
    void PiglinEntity::SetDataIsChargingCrossbow(const bool data_is_charging_crossbow)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_is_charging_crossbow"] = data_is_charging_crossbow;
    }

    void PiglinEntity::SetDataIsDancing(const bool data_is_dancing)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_is_dancing"] = data_is_dancing;
    }

}
#endif
