#include "botcraft/Game/Entities/entities/animal/parrot/ParrotEntity.hpp"

namespace Botcraft
{
    ParrotEntity::ParrotEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataVariantId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 6.0) });
        attributes.insert({ EntityAttribute::Type::FlyingSpeed, EntityAttribute(EntityAttribute::Type::FlyingSpeed, 0.4) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
#endif
    }

    ParrotEntity::~ParrotEntity()
    {

    }


    std::string ParrotEntity::GetName() const
    {
        return "parrot";
    }

    EntityType ParrotEntity::GetType() const
    {
        return EntityType::Parrot;
    }


    std::string ParrotEntity::GetClassName()
    {
        return "parrot";
    }

    EntityType ParrotEntity::GetClassType()
    {
        return EntityType::Parrot;
    }


    ProtocolCraft::Json::Value ParrotEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = ShoulderRidingEntity::Serialize();

        output["metadata"]["data_variant_id"] = GetDataVariantId();

        output["attributes"]["flying_speed"] = GetAttributeFlyingSpeedValue();
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();
#endif

        return output;
    }


    int ParrotEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }


    void ParrotEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }


    double ParrotEntity::GetAttributeFlyingSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FlyingSpeed).GetValue();
    }

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
    double ParrotEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }
#endif

    double ParrotEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ParrotEntity::GetHeightImpl() const
    {
        return 0.9;
    }

}
