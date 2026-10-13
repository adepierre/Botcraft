#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.hpp"

namespace Botcraft
{
    AbstractNautilusEntity::AbstractNautilusEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
        SetDataDash(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 15.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 1.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 0.3) });
    }

    AbstractNautilusEntity::~AbstractNautilusEntity()
    {

    }

    bool AbstractNautilusEntity::IsAbstractNautilus() const
    {
        return true;
    }


    ProtocolCraft::Json::Value AbstractNautilusEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = TamableAnimalEntity::Serialize();

        output["metadata"]["data_dash"] = GetDataDash();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    bool AbstractNautilusEntity::GetDataDash() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_dash"));
    }


    void AbstractNautilusEntity::SetDataDash(const bool data_dash)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_dash"), data_dash);
    }


    double AbstractNautilusEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }

}
#endif
