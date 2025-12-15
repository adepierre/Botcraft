#include "botcraft/Game/Entities/entities/animal/parrot/ParrotEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, ParrotEntity::metadata_count> ParrotEntity::metadata_names{ {
        "data_variant_id",
    } };

    ParrotEntity::ParrotEntity()
    {
        // Initialize all metadata with default values
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


    void ParrotEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            ShoulderRidingEntity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    int ParrotEntity::GetDataVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }


    void ParrotEntity::SetDataVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_variant_id"] = data_variant_id;
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
