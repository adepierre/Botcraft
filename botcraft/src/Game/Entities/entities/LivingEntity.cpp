#include "botcraft/Game/Entities/entities/LivingEntity.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <mutex>

namespace Botcraft
{
    const std::array<std::string, LivingEntity::metadata_count> LivingEntity::metadata_names{ {
        "data_living_entity_flags",
        "data_health_id",
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        "data_effect_color_id",
#else
        "data_effect_particles",
#endif
        "data_effect_ambience_id",
        "data_arrow_count_id",
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        "data_stinger_count_id",
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        "sleeping_pos_id",
#endif
    } };

    LivingEntity::LivingEntity()
    {
        // Initialize all metadata with default values
        SetDataLivingEntityFlags(0);
        SetDataHealthId(1.0f);
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        SetDataEffectColorId(0);
#else
        SetDataEffectParticles({});
#endif
        SetDataEffectAmbienceId(false);
        SetDataArrowCountId(0);
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        SetDataStingerCountId(0);
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        SetSleepingPosId(std::optional<Position>());
#endif

        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 20.0) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 0.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.7) });
        attributes.insert({ EntityAttribute::Type::Armor, EntityAttribute(EntityAttribute::Type::Armor, 0.0) });
        attributes.insert({ EntityAttribute::Type::ArmorToughness, EntityAttribute(EntityAttribute::Type::ArmorToughness, 0.0) });
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        attributes.insert({ EntityAttribute::Type::MaxAbsorption, EntityAttribute(EntityAttribute::Type::MaxAbsorption, 0.0) });
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        attributes.insert({ EntityAttribute::Type::StepHeight, EntityAttribute(EntityAttribute::Type::StepHeight, 0.6) });
        attributes.insert({ EntityAttribute::Type::Scale, EntityAttribute(EntityAttribute::Type::Scale, 1.0) });
        attributes.insert({ EntityAttribute::Type::Gravity, EntityAttribute(EntityAttribute::Type::Gravity, 0.08) });
        attributes.insert({ EntityAttribute::Type::SafeFallDistance, EntityAttribute(EntityAttribute::Type::SafeFallDistance, 3.0) });
        attributes.insert({ EntityAttribute::Type::FallDamageMultiplier, EntityAttribute(EntityAttribute::Type::FallDamageMultiplier, 1.0) });
        attributes.insert({ EntityAttribute::Type::JumpStrength, EntityAttribute(EntityAttribute::Type::JumpStrength, 0.42) });
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        attributes.insert({ EntityAttribute::Type::OxygenBonus, EntityAttribute(EntityAttribute::Type::OxygenBonus, 0.0) });
        attributes.insert({ EntityAttribute::Type::BurningTime, EntityAttribute(EntityAttribute::Type::BurningTime, 1.0) });
        attributes.insert({ EntityAttribute::Type::ExplosionKnockbackResistance, EntityAttribute(EntityAttribute::Type::ExplosionKnockbackResistance, 0.0) });
        attributes.insert({ EntityAttribute::Type::WaterMovementEfficiency, EntityAttribute(EntityAttribute::Type::WaterMovementEfficiency, 0.0) });
        attributes.insert({ EntityAttribute::Type::MovementEfficiency, EntityAttribute(EntityAttribute::Type::MovementEfficiency, 0.0) });
        attributes.insert({ EntityAttribute::Type::AttackKnockback, EntityAttribute(EntityAttribute::Type::AttackKnockback, 0.0) });
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        attributes.insert({ EntityAttribute::Type::CameraDistance, EntityAttribute(EntityAttribute::Type::CameraDistance, 4.0) });
        attributes.insert({ EntityAttribute::Type::WaypointTransmitRange, EntityAttribute(EntityAttribute::Type::WaypointTransmitRange, 0.0) });
#endif
    }

    LivingEntity::~LivingEntity()
    {

    }

    bool LivingEntity::IsLivingEntity() const
    {
        return true;
    }


    ProtocolCraft::Json::Value LivingEntity::Serialize() const
    {
        ProtocolCraft::Json::Value output = Entity::Serialize();

        output["metadata"]["data_living_entity_flags"] = GetDataLivingEntityFlags();
        output["metadata"]["data_health_id"] = GetDataHealthId();
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        output["metadata"]["data_effect_color_id"] = GetDataEffectColorId();
#else
        output["metadata"]["data_effect_particles"] = GetDataEffectParticles();
#endif
        output["metadata"]["data_effect_ambience_id"] = GetDataEffectAmbienceId();
        output["metadata"]["data_arrow_count_id"] = GetDataArrowCountId();
#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
        output["metadata"]["data_stinger_count_id"] = GetDataStingerCountId();
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        output["metadata"]["sleeping_pos_id"] = GetSleepingPosId() ? GetSleepingPosId().value().Serialize() : ProtocolCraft::Json::Value();
#endif

        output["attributes"] = ProtocolCraft::Json::Value();

        output["attributes"]["max_health"] = GetAttributeMaxHealthValue();
        output["attributes"]["knockback_resistance"] = GetAttributeKnockbackResistanceValue();
        output["attributes"]["movement_speed"] = GetAttributeMovementSpeedValue();
        output["attributes"]["armor"] = GetAttributeArmorValue();
        output["attributes"]["armor_toughness"] = GetAttributeArmorToughnessValue();
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        output["attributes"]["max_absorption"] = GetAttributeMaxAbsorptionValue();
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        output["attributes"]["step_height"] = GetAttributeStepHeightValue();
        output["attributes"]["scale"] = GetAttributeScaleValue();
        output["attributes"]["gravity"] = GetAttributeGravityValue();
        output["attributes"]["safe_fall_distance"] = GetAttributeSafeFallDistanceValue();
        output["attributes"]["fall_damage_multiplier"] = GetAttributeFallDamageMultiplierValue();
        output["attributes"]["jump_strength"] = GetAttributeJumpStrengthValue();
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        output["attributes"]["oxygen_bonus"] = GetAttributeOxygenBonusValue();
        output["attributes"]["burning_time"] = GetAttributeBurningTimeValue();
        output["attributes"]["explosion_knockback_resistance"] = GetAttributeExplosionKnockbackResistanceValue();
        output["attributes"]["water_movement_efficiency"] = GetAttributeWaterMovementEfficiencyValue();
        output["attributes"]["movement_efficiency"] = GetAttributeMovementEfficiencyValue();
        output["attributes"]["attack_knockback"] = GetAttributeAttackKnockbackValue();
#endif
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
        output["attributes"]["camera_distance"] = GetAttributeCameraDistanceValue();
        output["attributes"]["waypoint_transmit_range"] = GetAttributeWaypointTransmitRangeValue();
#endif

        return output;
    }


    void LivingEntity::SetMetadataValue(const int index, const std::any& value)
    {
        if (index < hierarchy_metadata_count)
        {
            Entity::SetMetadataValue(index, value);
        }
        else if (index - hierarchy_metadata_count < metadata_count)
        {
            std::scoped_lock<std::shared_mutex> lock(entity_mutex);
            metadata[metadata_names[index - hierarchy_metadata_count]] = value;
        }
    }

    char LivingEntity::GetDataLivingEntityFlags() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetDataLivingEntityFlagsImpl();
    }

    float LivingEntity::GetDataHealthId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<float>(metadata.at("data_health_id"));
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    int LivingEntity::GetDataEffectColorId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_effect_color_id"));
    }
#else
    std::vector<ProtocolCraft::Particle> LivingEntity::GetDataEffectParticles() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<std::vector<ProtocolCraft::Particle>>(metadata.at("data_effect_particle"));
    }
#endif

    bool LivingEntity::GetDataEffectAmbienceId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<bool>(metadata.at("data_effect_ambience_id"));
    }

    int LivingEntity::GetDataArrowCountId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_arrow_count_id"));
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    int LivingEntity::GetDataStingerCountId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return std::any_cast<int>(metadata.at("data_stinger_count_id"));
    }
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    std::optional<Position> LivingEntity::GetSleepingPosId() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetSleepingPosIdImpl();
    }
#endif


    void LivingEntity::SetDataLivingEntityFlags(const char data_living_entity_flags)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_living_entity_flags"] = data_living_entity_flags;
    }

    void LivingEntity::SetDataHealthId(const float data_health_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_health_id"] = data_health_id;
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    void LivingEntity::SetDataEffectColorId(const int data_effect_color_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_effect_color_id"] = data_effect_color_id;
    }
#else
    void LivingEntity::SetDataEffectParticles(const std::vector<ProtocolCraft::Particle>& data_effect_particles)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_effect_particles"] = data_effect_particles;
    }
#endif

    void LivingEntity::SetDataEffectAmbienceId(const bool data_effect_ambience_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_effect_ambience_id"] = data_effect_ambience_id;
    }

    void LivingEntity::SetDataArrowCountId(const int data_arrow_count_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_arrow_count_id"] = data_arrow_count_id;
    }

#if PROTOCOL_VERSION > 498 /* > 1.14.4 */
    void LivingEntity::SetDataStingerCountId(const int data_stinger_count_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["data_stinger_count_id"] = data_stinger_count_id;
    }
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void LivingEntity::SetSleepingPosId(const std::optional<Position>& sleeping_pos_id)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        metadata["sleeping_pos_id"] = sleeping_pos_id;
    }
#endif

    std::optional<EntityAttribute> LivingEntity::GetAttribute(const EntityAttribute::Type type) const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);

        auto it = attributes.find(type);
        if (it == attributes.end())
        {
            return std::optional<EntityAttribute>();
        }
        return it->second;
    }

    void LivingEntity::SetAttributeBaseValue(const EntityAttribute::Type type, const double value)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);

        auto it = attributes.find(type);
        if (it == attributes.end())
        {
            LOG_WARNING("Trying to set attribute base value for " << type << " for a " << GetName() << " but it doesn't have this attribute");
            return;
        }
        it->second.SetBaseValue(value);
    }

    void LivingEntity::RemoveAttributeModifier(const EntityAttribute::Type type, const EntityAttribute::ModifierKey& key)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        RemoveAttributeModifierImpl(type, key);
    }

    void LivingEntity::SetAttributeModifier(const EntityAttribute::Type type, const EntityAttribute::ModifierKey& key, const EntityAttribute::Modifier& modifier)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);
        SetAttributeModifierImpl(type, key, modifier);
    }

    void LivingEntity::ClearModifiers(const EntityAttribute::Type type)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);

        auto it = attributes.find(type);
        if (it == attributes.end())
        {
            return;
        }
        it->second.ClearModifiers();
    }

    void LivingEntity::AddAttribute(const EntityAttribute& attribute)
    {
        std::scoped_lock<std::shared_mutex> lock(entity_mutex);

        auto it = attributes.find(attribute.GetType());
        if (it == attributes.end())
        {
            LOG_WARNING("Trying to add an attribute " << attribute.GetType() << " to a " << GetName() << " but it was not present");
        }
        else
        {
            attributes.erase(it);
        }
        attributes.insert({ attribute.GetType(), attribute });
    }

    double LivingEntity::GetAttributeMaxHealthValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::MaxHealth).GetValue();
    }

    double LivingEntity::GetAttributeKnockbackResistanceValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::KnockbackResistance).GetValue();
    }

    double LivingEntity::GetAttributeMovementSpeedValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributeMovementSpeedValueImpl();
    }

    double LivingEntity::GetAttributeArmorValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::Armor).GetValue();
    }

    double LivingEntity::GetAttributeArmorToughnessValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::ArmorToughness).GetValue();
    }

#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
    double LivingEntity::GetAttributeMaxAbsorptionValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::MaxAbsorption).GetValue();
    }
#endif

    double LivingEntity::GetAttributeMovementSpeedValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::MovementSpeed).GetValue();
    }

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    double LivingEntity::GetAttributeStepHeightValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributeStepHeightValueImpl();
    }

    double LivingEntity::GetAttributeScaleValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::Scale).GetValue();
    }

    double LivingEntity::GetAttributeGravityValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributeGravityValueImpl();
    }

    double LivingEntity::GetAttributeSafeFallDistanceValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::SafeFallDistance).GetValue();
    }

    double LivingEntity::GetAttributeFallDamageMultiplierValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::FallDamageMultiplier).GetValue();
    }

    double LivingEntity::GetAttributeJumpStrengthValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributeJumpStrengthValueImpl();
    }
#endif

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
    double LivingEntity::GetAttributeOxygenBonusValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::OxygenBonus).GetValue();
    }

    double LivingEntity::GetAttributeBurningTimeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::BurningTime).GetValue();
    }

    double LivingEntity::GetAttributeExplosionKnockbackResistanceValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::ExplosionKnockbackResistance).GetValue();
    }

    double LivingEntity::GetAttributeWaterMovementEfficiencyValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributeWaterMovementEfficiencyValueImpl();
    }

    double LivingEntity::GetAttributeMovementEfficiencyValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return GetAttributeMovementEfficiencyValueImpl();
    }

    double LivingEntity::GetAttributeAttackKnockbackValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::AttackKnockback).GetValue();
    }
#endif

#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
    double LivingEntity::GetAttributeCameraDistanceValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::CameraDistance).GetValue();
    }

    double LivingEntity::GetAttributeWaypointTransmitRangeValue() const
    {
        std::shared_lock<std::shared_mutex> lock(entity_mutex);
        return attributes.at(EntityAttribute::Type::WaypointTransmitRange).GetValue();
    }
#endif

    void LivingEntity::RemoveAttributeModifierImpl(const EntityAttribute::Type type, const EntityAttribute::ModifierKey& key)
    {
        auto it = attributes.find(type);
        if (it == attributes.end())
        {
            return;
        }
        it->second.RemoveModifier(key);
    }

    void LivingEntity::SetAttributeModifierImpl(const EntityAttribute::Type type, const EntityAttribute::ModifierKey& key, const EntityAttribute::Modifier& modifier)
    {
        auto it = attributes.find(type);
        if (it == attributes.end())
        {
            LOG_WARNING("Trying to set attribute modifier for " << type << " for a " << GetName() << " but it doesn't have this attribute");
            return;
        }
        it->second.SetModifier(key, modifier);
    }

    char LivingEntity::GetDataLivingEntityFlagsImpl() const
    {
        return std::any_cast<char>(metadata.at("data_living_entity_flags"));
    }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    std::optional<Position> LivingEntity::GetSleepingPosIdImpl() const
    {
        return std::any_cast<std::optional<Position>>(metadata.at("sleeping_pos_id"));
    }
#endif

#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
    double LivingEntity::GetAttributeStepHeightValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::StepHeight).GetValue();
    }

    double LivingEntity::GetAttributeGravityValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::Gravity).GetValue();
    }

    double LivingEntity::GetAttributeJumpStrengthValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::JumpStrength).GetValue();
    }
#endif

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
    double LivingEntity::GetAttributeWaterMovementEfficiencyValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::WaterMovementEfficiency).GetValue();
    }

    double LivingEntity::GetAttributeMovementEfficiencyValueImpl() const
    {
        return attributes.at(EntityAttribute::Type::MovementEfficiency).GetValue();
    }
#endif

}
