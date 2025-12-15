#include "botcraft/Game/Entities/entities/animal/golem/IronGolemEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, IronGolemEntity::metadata_count> IronGolemEntity::metadata_names{ {
        "data_flags_id",
    } };

    IronGolemEntity::IronGolemEntity()
    {
        // Initialize all metadata with default values
        SetDataFlagsId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 100.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 1.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 15.0) });
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 1.0) });
#endif
    }

    IronGolemEntity::~IronGolemEntity()
    {

    }


    std::string IronGolemEntity::GetName() const
    {
        return "iron_golem";
    }

    EntityType IronGolemEntity::GetType() const
    {
        return EntityType::IronGolem;
    }


    std::string IronGolemEntity::GetClassName()
    {
        return "iron_golem";
    }

    EntityType IronGolemEntity::GetClassType()
    {
        return EntityType::IronGolem;
    }


    ProtocolCraft::Json::Value IronGolemEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AbstractGolemEntity::Serialize();

        output["metadata"]["data_flags_id"] = GetDataFlagsId();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    void IronGolemEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            AbstractGolemEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char IronGolemEntity::GetDataFlagsId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<char>(metadata.at("data_flags_id"));
    }


    void IronGolemEntity::SetDataFlagsId(const char data_flags_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_flags_id"] = data_flags_id;
    }


    double IronGolemEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double IronGolemEntity::GetWidthImpl() const
    {
        return 1.4;
    }

    double IronGolemEntity::GetHeightImpl() const
    {
        return 2.7;
    }

}
