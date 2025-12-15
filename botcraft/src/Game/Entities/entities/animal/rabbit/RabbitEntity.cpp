#include "botcraft/Game/Entities/entities/animal/rabbit/RabbitEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, RabbitEntity::metadata_count> RabbitEntity::metadata_names{ {
        "data_type_id",
    } };

    RabbitEntity::RabbitEntity()
    {
        // Initialize all metadata with default values
        SetDataTypeId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 3.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 3.0) });
#endif
    }

    RabbitEntity::~RabbitEntity()
    {

    }


    std::string RabbitEntity::GetName() const
    {
        return "rabbit";
    }

    EntityType RabbitEntity::GetType() const
    {
        return EntityType::Rabbit;
    }


    std::string RabbitEntity::GetClassName()
    {
        return "rabbit";
    }

    EntityType RabbitEntity::GetClassType()
    {
        return EntityType::Rabbit;
    }


    ProtocolCraft::Json::Value RabbitEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = AnimalEntity::Serialize();

        output["metadata"]["data_type_id"] = GetDataTypeId();

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        output["attribute"]["attack_damage"] = GetAttributeAttackDamageValue();
#endif

        return output;
    }


    void RabbitEntity::SetMetadataValue(const int index, const std::any& value)
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

    int RabbitEntity::GetDataTypeId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_type_id"));
    }


    void RabbitEntity::SetDataTypeId(const int data_type_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_type_id"] = data_type_id;
    }

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
    double RabbitEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }
#endif


    double RabbitEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double RabbitEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
