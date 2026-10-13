#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/piglin/PiglinEntity.hpp"

namespace Botcraft
{
    PiglinEntity::PiglinEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataBabyId(false);
#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
        SetDataImmuneToZombification(false);
#endif
        SetDataIsChargingCrossbow(false);
        SetDataIsDancing(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 16.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.35) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 5.0) });
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


    bool PiglinEntity::GetDataBabyId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"));
    }

#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
    bool PiglinEntity::GetDataImmuneToZombification() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_immune_to_zombification"));
    }
#endif

    bool PiglinEntity::GetDataIsChargingCrossbow() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_charging_crossbow"));
    }

    bool PiglinEntity::GetDataIsDancing() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_dancing"));
    }


    void PiglinEntity::SetDataBabyId(const bool data_baby_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"), data_baby_id);
    }

#if PROTOCOL_VERSION < 737 /* < 1.16.2 */
    void PiglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_immune_to_zombification"), data_immune_to_zombification);
    }
#endif
    void PiglinEntity::SetDataIsChargingCrossbow(const bool data_is_charging_crossbow)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_charging_crossbow"), data_is_charging_crossbow);
    }

    void PiglinEntity::SetDataIsDancing(const bool data_is_dancing)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_is_dancing"), data_is_dancing);
    }

    double PiglinEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double PiglinEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
