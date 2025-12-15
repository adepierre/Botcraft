#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#include "botcraft/Game/Entities/entities/animal/nautilus/AbstractNautilusEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, AbstractNautilusEntity::metadata_count> AbstractNautilusEntity::metadata_names{ {
        "data_dash",
    } };

    AbstractNautilusEntity::AbstractNautilusEntity()
    {
        // Initialize all metadata with default values
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


    void AbstractNautilusEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            TamableAnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool AbstractNautilusEntity::GetDataDash() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_dash"));
    }


    void AbstractNautilusEntity::SetDataDash(const bool data_dash)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_dash"] = data_dash;
    }


    double AbstractNautilusEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }

}
#endif
