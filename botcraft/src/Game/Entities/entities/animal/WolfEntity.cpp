#include "botcraft/Game/Entities/entities/animal/WolfEntity.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, WolfEntity::metadata_count> WolfEntity::metadata_names{ {
#if PROTOCOL_VERSION < 499 /* < 1.15 */
        "data_health_id",
#endif
        "data_interested_id",
        "data_collar_color",
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        "data_remaining_anger_time",
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        "data_variant_id",
#endif
    } };

    WolfEntity::WolfEntity()
    {
        // Initialize all metadata with default values
#if PROTOCOL_VERSION < 499 /* < 1.15 */
        SetDataHealthId(1.0f);
#endif
        SetDataInterestedId(false);
        SetDataCollarColor(14);
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        SetDataRemainingAngerTime(0);
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SetDataVariantId(0);
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 8.0) });
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
#else
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 4.0) });
#endif
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

#if PROTOCOL_VERSION < 499 /* < 1.15 */
        output["metadata"]["data_health_id"] = GetDataHealthId();
#endif
        output["metadata"]["data_interested_id"] = GetDataInterestedId();
        output["metadata"]["data_collar_color"] = GetDataCollarColor();
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        output["metadata"]["data_remaining_anger_time"] = GetDataRemainingAngerTime();
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        output["metadata"]["data_variant_id"] = GetDataVariantId();
#endif

        output["attributes"]["generic.attack_damage"] = GetAttributeAttackDamageValue();

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

#if PROTOCOL_VERSION < 499 /* < 1.15 */
    float WolfEntity::GetDataHealthId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_health_id"));
    }
#endif

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

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    int WolfEntity::GetDataRemainingAngerTime() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_remaining_anger_time"));
    }
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    int WolfEntity::GetDataVariantId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_variant_id"));
    }
#endif


#if PROTOCOL_VERSION < 499 /* < 1.15 */
    void WolfEntity::SetDataHealthId(const float data_health_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_health_id"] = data_health_id;
    }
#endif

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

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    void WolfEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_remaining_anger_time"] = data_remaining_anger_time;
    }
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    void WolfEntity::SetDataVariantId(const int data_variant_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_variant_id"] = data_variant_id;
    }
#endif


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
