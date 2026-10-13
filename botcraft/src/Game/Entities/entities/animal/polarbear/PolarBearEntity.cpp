#include "botcraft/Game/Entities/entities/animal/polarbear/PolarBearEntity.hpp"

namespace Botcraft
{
    PolarBearEntity::PolarBearEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataStandingId(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 30.0) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 20.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 6.0) });
    }

    PolarBearEntity::~PolarBearEntity()
    {

    }


    std::string PolarBearEntity::GetName() const
    {
        return "polar_bear";
    }

    EntityType PolarBearEntity::GetType() const
    {
        return EntityType::PolarBear;
    }


    std::string PolarBearEntity::GetClassName()
    {
        return "polar_bear";
    }

    EntityType PolarBearEntity::GetClassType()
    {
        return EntityType::PolarBear;
    }


    ProtocolCraft::Json::Value PolarBearEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_standing_id"] = GetDataStandingId();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    bool PolarBearEntity::GetDataStandingId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_standing_id"));
    }


    void PolarBearEntity::SetDataStandingId(const bool data_standing_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_standing_id"), data_standing_id);
    }


    double PolarBearEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double PolarBearEntity::GetWidthImpl() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        return 1.4;
#else
        return 1.3;
#endif
    }

    double PolarBearEntity::GetHeightImpl() const
    {
        return 1.4;
    }

}
