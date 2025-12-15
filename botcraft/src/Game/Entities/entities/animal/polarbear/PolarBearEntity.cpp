#include "botcraft/Game/Entities/entities/animal/polarbear/PolarBearEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, PolarBearEntity::metadata_count> PolarBearEntity::metadata_names{ {
        "data_standing_id",
    } };

    PolarBearEntity::PolarBearEntity()
    {
        // Initialize all metadata with default values
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


    void PolarBearEntity::SetMetadataValue(const int index, const std::any& value)
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

    bool PolarBearEntity::GetDataStandingId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_standing_id"));
    }


    void PolarBearEntity::SetDataStandingId(const bool data_standing_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_standing_id"] = data_standing_id;
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
