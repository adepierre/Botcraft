#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include "botcraft/Game/Entities/entities/monster/warden/WardenEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, WardenEntity::metadata_count> WardenEntity::metadata_names{ {
        "client_anger_level",
    } };

    WardenEntity::WardenEntity()
    {
        // Initialize all metadata with default values
        SetClientAngerLevel(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 500.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 1.0) });
        attributes.insert({ EntityAttribute::Type::AttackKnockback, EntityAttribute(EntityAttribute::Type::AttackKnockback, 1.5) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 30.0) });
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 24.0) });
#endif
    }

    WardenEntity::~WardenEntity()
    {

    }


    std::string WardenEntity::GetName() const
    {
        return "warden";
    }

    EntityType WardenEntity::GetType() const
    {
        return EntityType::Warden;
    }


    std::string WardenEntity::GetClassName()
    {
        return "warden";
    }

    EntityType WardenEntity::GetClassType()
    {
        return EntityType::Warden;
    }


    ProtocolCraft::Json::Value WardenEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = MonsterEntity::Serialize();

        output["client_anger_level"] = GetClientAngerLevel();

        return output;
    }


    void WardenEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            MonsterEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int WardenEntity::GetClientAngerLevel() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("client_anger_level"));
    }


    void WardenEntity::SetClientAngerLevel(const int client_anger_level)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["client_anger_level"] = client_anger_level;
    }


    double WardenEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double WardenEntity::GetHeightImpl() const
    {
        return 2.9;
    }

}
#endif
