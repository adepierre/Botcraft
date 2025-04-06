#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "botcraft/Game/Entities/entities/animal/wolf/WolfEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, WolfEntity::metadata_count> WolfEntity::metadata_names{ {
        "data_interested_id",
        "data_collar_color",
        "data_remaining_anger_time",
        "data_variant_id",
        "data_sound_variant_id",
    } };

    WolfEntity::WolfEntity()
    {
        // Initialize all metadata with default values
        SetDataInterestedId(false);
        SetDataCollarColor(14);
        SetDataRemainingAngerTime(0);
        SetDataVariantId(0);
        SetDataSoundVariantId(0);

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 8.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 4.0) });
    }

    WolfEntity::~WolfEntity()
    {

    }


    std::string WolfEntity::GetName() const
    {
        return "wolf";
    }

    EntityType WolfEntity::GetType() const
    {
        return EntityType::Wolf;
    }


    std::string WolfEntity::GetClassName()
    {
        return "wolf";
    }

    EntityType WolfEntity::GetClassType()
    {
        return EntityType::Wolf;
    }


    ProtocolCraft::Json::Value WolfEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = TamableAnimalEntity::Serialize();

        output["metadata"]["data_interested_id"] = GetDataInterestedId();
        output["metadata"]["data_collar_color"] = GetDataCollarColor();
        output["metadata"]["data_remaining_anger_time"] = GetDataRemainingAngerTime();
        output["metadata"]["data_variant_id"] = GetDataVariantId();
        output["metadata"]["data_sound_variant_id"] = GetDataSoundVariantId();

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


    void WolfEntity::SetMetadataValue(const int index, const std::any& value)
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


    bool WolfEntity::GetDataInterestedId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_interested_id"));
    }

    int WolfEntity::GetDataCollarColor() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_collar_color"));
    }

    int WolfEntity::GetDataRemainingAngerTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_remaining_anger_time"));
    }

    int WolfEntity::GetDataVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }

    int WolfEntity::GetDataSoundVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_sound_variant_id"));
    }


    void WolfEntity::SetDataInterestedId(const bool data_interested_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_interested_id"] = data_interested_id;
    }

    void WolfEntity::SetDataCollarColor(const int data_collar_color)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_collar_color"] = data_collar_color;
    }

    void WolfEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_remaining_anger_time"] = data_remaining_anger_time;
    }

    void WolfEntity::SetDataVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_variant_id"] = data_variant_id;
    }

    void WolfEntity::SetDataSoundVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_sound_variant_id"] = data_variant_id;
    }


    double WolfEntity::GetAttributeAttackDamageValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackDamage).GetValue();
    }


    double WolfEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double WolfEntity::GetHeightImpl() const
    {
        return 0.85;
    }

}
#endif
