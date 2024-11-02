#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/monster/hoglin/HoglinEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, HoglinEntity::metadata_count> HoglinEntity::metadata_names{ {
        "data_immune_to_zombification",
    } };

    HoglinEntity::HoglinEntity()
    {
        // Initialize all metadata with default values
        SetDataImmuneToZombification(false);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 40.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 0.6) });
        attributes.insert({ EntityAttribute::Type::AttackKnockback, EntityAttribute(EntityAttribute::Type::AttackKnockback, 1.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 6.0) });
    }

    HoglinEntity::~HoglinEntity()
    {

    }


    std::string HoglinEntity::GetName() const
    {
        return "hoglin";
    }

    EntityType HoglinEntity::GetType() const
    {
        return EntityType::Hoglin;
    }


    std::string HoglinEntity::GetClassName()
    {
        return "hoglin";
    }

    EntityType HoglinEntity::GetClassType()
    {
        return EntityType::Hoglin;
    }


    ProtocolCraft::Json::Value HoglinEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_immune_to_zombification"] = GetDataImmuneToZombification();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    void HoglinEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AnimalEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    bool HoglinEntity::GetDataImmuneToZombification() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_immune_to_zombification"));
    }


    void HoglinEntity::SetDataImmuneToZombification(const bool data_immune_to_zombification)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_immune_to_zombification"] = data_immune_to_zombification;
    }


    double HoglinEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double HoglinEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double HoglinEntity::GetHeightImpl() const
    {
        return 1.4;
    }

}
#endif
