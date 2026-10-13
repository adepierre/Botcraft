#include "botcraft/Game/Entities/entities/animal/wolf/WolfEntity.hpp"

namespace Botcraft
{
    WolfEntity::WolfEntity()
    {
        // Initialize all metadata with default values
        metadata.resize(metadata_count + hierarchy_metadata_count);
#if PROTOCOL_VERSION < 499 /* < 1.15 */
        SetDataHealthId(1.0f);
#endif
        SetDataInterestedId(false);
        SetDataCollarColor(14);
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        SetDataRemainingAngerTime(0);
#else
        SetDataAngerEndTime(0);
#endif
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        SetDataVariantId(0);
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SetDataSoundVariantId(0);
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
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
        output["metadata"]["data_remaining_anger_time"] = GetDataRemainingAngerTime();
#else
        output["metadata"]["data_anger_end_time"] = GetDataAngerEndTime();
#endif
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        output["metadata"]["data_variant_id"] = GetDataVariantId();
#endif
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        output["metadata"]["data_sound_variant_id"] = GetDataSoundVariantId();
#endif

        output["attributes"]["attack_damage"] = GetAttributeAttackDamageValue();

        return output;
    }


#if PROTOCOL_VERSION < 499 /* < 1.15 */
    float WolfEntity::GetDataHealthId() const
    {
        return GetMetadata<float>(BOTCRAFT_ENTITY_METADATA_INDEX("data_health_id"));
    }
#endif

    bool WolfEntity::GetDataInterestedId() const
    {
        return GetMetadata<bool>(BOTCRAFT_ENTITY_METADATA_INDEX("data_interested_id"));
    }

    int WolfEntity::GetDataCollarColor() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_collar_color"));
    }

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
    int WolfEntity::GetDataRemainingAngerTime() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_remaining_anger_time"));
    }
#else
    long long int WolfEntity::GetDataAngerEndTime() const
    {
        return GetMetadata<long long int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_anger_end_time"));
    }
#endif
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    int WolfEntity::GetDataVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"));
    }
#endif

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    int WolfEntity::GetDataSoundVariantId() const
    {
        return GetMetadata<int>(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"));
    }
#endif


#if PROTOCOL_VERSION < 499 /* < 1.15 */
    void WolfEntity::SetDataHealthId(const float data_health_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_health_id"), data_health_id);
    }
#endif

    void WolfEntity::SetDataInterestedId(const bool data_interested_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_interested_id"), data_interested_id);
    }

    void WolfEntity::SetDataCollarColor(const int data_collar_color)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_collar_color"), data_collar_color);
    }

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#if PROTOCOL_VERSION < 774 /* < 1.21.11 */
    void WolfEntity::SetDataRemainingAngerTime(const int data_remaining_anger_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_remaining_anger_time"), data_remaining_anger_time);
    }
#else
    void WolfEntity::SetDataAngerEndTime(const long long int data_anger_end_time)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_anger_end_time"), data_anger_end_time);
    }
#endif
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    void WolfEntity::SetDataVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_variant_id"), data_variant_id);
    }
#endif

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
    void WolfEntity::SetDataSoundVariantId(const int data_variant_id)
    {
        SetMetadata(BOTCRAFT_ENTITY_METADATA_INDEX("data_sound_variant_id"), data_variant_id);
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
