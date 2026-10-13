#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/ZoglinEntity.hpp"

namespace Botcraft
{
    ZoglinEntity::ZoglinEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataBabyId(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 40.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 0.6) });
        attributes.insert({ EntityAttribute::Type::AttackKnockback, EntityAttribute(EntityAttribute::Type::AttackKnockback, 1.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 6.0) });
    }

    ZoglinEntity::~ZoglinEntity()
    {

    }


    std::string ZoglinEntity::GetName() const
    {
        return "zoglin";
    }

    EntityType ZoglinEntity::GetType() const
    {
        return EntityType::Zoglin;
    }


    std::string ZoglinEntity::GetClassName()
    {
        return "zoglin";
    }

    EntityType ZoglinEntity::GetClassType()
    {
        return EntityType::Zoglin;
    }


    ProtocolCraft::Json::Value ZoglinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["metadata"]["data_baby_id"] = GetDataBabyId();

        return output;
    }


    bool ZoglinEntity::GetDataBabyId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"));
    }


    void ZoglinEntity::SetDataBabyId(const bool data_baby_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_baby_id"), data_baby_id);
    }


    double ZoglinEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double ZoglinEntity::GetHeightImpl() const
    {
        return 1.4;
    }

}
#endif
