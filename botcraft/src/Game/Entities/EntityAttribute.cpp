#include "botcraft/Game/Entities/EntityAttribute.hpp"
#include "botcraft/Utilities/EnumUtilities.hpp"

namespace Botcraft
{
    EntityAttribute::EntityAttribute(const Type type_, const double base_value_)
    {
        type = type_;
        base_value = base_value_;
        current_value = base_value;
        up_to_date = false;
    }

    void EntityAttribute::SetBaseValue(const double new_value)
    {
        if (new_value == base_value)
        {
            return;
        }
        base_value = new_value;
        up_to_date = false;
    }

    void EntityAttribute::ClearModifiers()
    {
        modifiers.clear();
        up_to_date = false;
    }

    void EntityAttribute::RemoveModifier(const ModifierKey& key)
    {
        // If no element is removed, value is still up to date
        up_to_date = modifiers.erase(key) > 0;
    }

    void EntityAttribute::SetModifier(const ModifierKey& key, const Modifier& modifier)
    {
        modifiers[key] = modifier;
        up_to_date = false;
    }

    EntityAttribute::Type EntityAttribute::GetType() const
    {
        return type;
    }

    double EntityAttribute::GetBaseValue() const
    {
        return base_value;
    }

    const std::map<EntityAttribute::ModifierKey, EntityAttribute::Modifier>& EntityAttribute::GetModifiers() const
    {
        return modifiers;
    }

    double EntityAttribute::GetValue() const
    {
        if (!up_to_date)
        {
            UpdateValue();
        }
        return current_value;
    }

    std::optional<EntityAttribute::Modifier> EntityAttribute::GetModifier(const ModifierKey& key)
    {
        auto it = modifiers.find(key);
        if (it == modifiers.end())
        {
            return std::optional<Modifier>();
        }
        return it->second;
    }

#if PROTOCOL_VERSION < 766 /* < 1.20.4 */
    std::string EntityAttribute::TypeToString(const Type type)
    {
        switch (type)
        {
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        case Type::MaxHealth:
            return "generic.maxHealth";
        case Type::FollowRange:
            return "generic.followRange";
        case Type::KnockbackResistance:
            return "generic.knockbackResistance";
        case Type::MovementSpeed:
            return "generic.movementSpeed";
        case Type::FlyingSpeed:
            return "generic.flyingSpeed";
        case Type::AttackDamage:
            return "generic.attackDamage";
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        case Type::AttackKnockback:
            return "generic.attackKnockback";
#endif
        case Type::AttackSpeed:
            return "generic.attackSpeed";
        case Type::Armor:
            return "generic.armor";
        case Type::ArmorToughness:
            return "generic.armorToughness";
        case Type::Luck:
            return "generic.luck";
        case Type::ZombieSpawnReinforcementsChance:
            return "zombie.spawnReinforcements";
        case Type::HorseJumpStrength:
            return "horse.jumpStrength";
#else
        case Type::MaxHealth:
            return "minecraft:generic.max_health";
        case Type::FollowRange:
            return "minecraft:generic.follow_range";
        case Type::KnockbackResistance:
            return "minecraft:generic.knockback_resistance";
        case Type::MovementSpeed:
            return "minecraft:generic.movement_speed";
        case Type::FlyingSpeed:
            return "minecraft:generic.flying_speed";
        case Type::AttackDamage:
            return "minecraft:generic.attack_damage";
        case Type::AttackKnockback:
            return "minecraft:generic.attack_knockback";
        case Type::AttackSpeed:
            return "minecraft:generic.attack_speed";
        case Type::Armor:
            return "minecraft:generic.armor";
        case Type::ArmorToughness:
            return "minecraft:generic.armor_toughness";
        case Type::Luck:
            return "minecraft:generic.luck";
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case Type::MaxAbsorption:
            return "minecraft:generic.max_absorption";
#endif
        case Type::ZombieSpawnReinforcementsChance:
            return "minecraft:zombie.spawn_reinforcements";
        case Type::HorseJumpStrength:
            return "minecraft:horse.jump_strength";
#endif
        default:
            return "";
        }
    }

    EntityAttribute::Type EntityAttribute::StringToType(const std::string& s)
    {

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        if (s == "generic.maxHealth")
        {
            return EntityAttribute::Type::MaxHealth;
        }
        if (s == "generic.followRange")
        {
            return EntityAttribute::Type::FollowRange;
        }
        if (s == "generic.knockbackResistance")
        {
            return EntityAttribute::Type::KnockbackResistance;
        }
        if (s == "generic.movementSpeed")
        {
            return EntityAttribute::Type::MovementSpeed;
        }
        if (s == "generic.flyingSpeed")
        {
            return EntityAttribute::Type::FlyingSpeed;
        }
        if (s == "generic.attackDamage")
        {
            return EntityAttribute::Type::AttackDamage;
        }
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        if (s == "generic.attackKnockback")
        {
            return EntityAttribute::Type::AttackKnockback;
        }
#endif
        if (s == "generic.attackSpeed")
        {
            return EntityAttribute::Type::AttackSpeed;
        }
        if (s == "generic.armor")
        {
            return EntityAttribute::Type::Armor;
        }
        if (s == "generic.armorToughness")
        {
            return EntityAttribute::Type::ArmorToughness;
        }
        if (s == "generic.luck")
        {
            return EntityAttribute::Type::Luck;
        }
        if (s == "zombie.spawnReinforcements")
        {
            return Type::ZombieSpawnReinforcementsChance;
        }
        if (s == "horse.jumpStrength")
        {
            return Type::HorseJumpStrength;
        }
#else
        if (s == "minecraft:generic.max_health")
        {
            return Type::MaxHealth;
        }
        if (s == "minecraft:generic.follow_range")
        {
            return Type::FollowRange;
        }
        if (s == "minecraft:generic.knockback_resistance")
        {
            return Type::KnockbackResistance;
        }
        if (s == "minecraft:generic.movement_speed")
        {
            return Type::MovementSpeed;
        }
        if (s == "minecraft:generic.flying_speed")
        {
            return Type::FlyingSpeed;
        }
        if (s == "minecraft:generic.attack_damage")
        {
            return Type::AttackDamage;
        }
        if (s == "minecraft:generic.attack_knockback")
        {
            return Type::AttackKnockback;
        }
        if (s == "minecraft:generic.attack_speed")
        {
            return Type::AttackSpeed;
        }
        if (s == "minecraft:generic.armor")
        {
            return Type::Armor;
        }
        if (s == "minecraft:generic.armor_toughness")
        {
            return Type::ArmorToughness;
        }
        if (s == "minecraft:generic.luck")
        {
            return Type::Luck;
        }
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        if (s == "minecraft:generic.max_absorption")
        {
            return Type::MaxAbsorption;
        }
#endif
        if (s == "minecraft:zombie.spawn_reinforcements")
        {
            return Type::ZombieSpawnReinforcementsChance;
        }
        if (s == "minecraft:horse.jump_strength")
        {
            return Type::HorseJumpStrength;
        }
#endif
        return Type::Unknown;
    }
#endif

    void EntityAttribute::UpdateValue() const
    {
        current_value = base_value;
        for (const auto& [uuid, m] : modifiers)
        {
            if (m.operation != Modifier::Operation::Add)
            {
                continue;
            }
            current_value += m.amount;
        }

        double current_mult = 1.0;
        for (const auto& [uuid, m] : modifiers)
        {
            if (m.operation != Modifier::Operation::MultiplyBase)
            {
                continue;
            }
            current_mult += m.amount;
        }
        current_value *= current_mult;

        for (const auto& [uuid, m] : modifiers)
        {
            if (m.operation != Modifier::Operation::MultiplyTotal)
            {
                continue;
            }
            current_value *= (1.0 + m.amount);
        }

        switch (type)
        {
        case Type::MaxHealth:
            current_value = std::clamp(current_value, 1.0, 1024.0);
            break;
        case Type::FollowRange:
            current_value = std::clamp(current_value, 0.0, 2048.0);
            break;
        case Type::KnockbackResistance:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
        case Type::MovementSpeed:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::FlyingSpeed:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::AttackDamage:
            current_value = std::clamp(current_value, 0.0, 2048.0);
            break;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        case Type::AttackKnockback:
            current_value = std::clamp(current_value, 0.0, 5.0);
            break;
#endif
        case Type::AttackSpeed:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::Armor:
            current_value = std::clamp(current_value, 0.0, 30.0);
            break;
        case Type::ArmorToughness:
            current_value = std::clamp(current_value, 0.0, 20.0);
            break;
        case Type::Luck:
            current_value = std::clamp(current_value, -1024.0, 1024.0);
            break;
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        case Type::MaxAbsorption:
            current_value = std::clamp(current_value, 0.0, 2048.0);
            break;
#endif
        case Type::ZombieSpawnReinforcementsChance:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        case Type::HorseJumpStrength:
            current_value = std::clamp(current_value, 0.0, 2.0);
            break;
#endif
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
        case Type::PlayerBlockBreakSpeed:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::PlayerBlockInteractionRange:
            current_value = std::clamp(current_value, 0.0, 64.0);
            break;
        case Type::PlayerEntityInteractionRange:
            current_value = std::clamp(current_value, 0.0, 64.0);
            break;
        case Type::FallDamageMultiplier:
            current_value = std::clamp(current_value, 0.0, 100.0);
            break;
        case Type::Gravity:
            current_value = std::clamp(current_value, -1.0, 1.0);
            break;
        case Type::JumpStrength:
            current_value = std::clamp(current_value, 0.0, 32.0);
            break;
        case Type::SafeFallDistance:
            current_value = std::clamp(current_value, -1024.0, 1024.0);
            break;
        case Type::Scale:
            current_value = std::clamp(current_value, 0.0625, 16.0);
            break;
        case Type::StepHeight:
            current_value = std::clamp(current_value, 0.0, 10.0);
            break;
#endif
#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        case Type::BurningTime:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::ExplosionKnockbackResistance:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
        case Type::PlayerMiningEfficiency:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::MovementEfficiency:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
        case Type::OxygenBonus:
            current_value = std::clamp(current_value, 0.0, 1024.0);
            break;
        case Type::PlayerSneakingSpeed:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
        case Type::PlayerSubmergedMiningSpeed:
            current_value = std::clamp(current_value, 0.0, 20.0);
            break;
        case Type::PlayerSweepingDamageRatio:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
        case Type::WaterMovementEfficiency:
            current_value = std::clamp(current_value, 0.0, 1.0);
            break;
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        case Type::TemptRange:
            current_value = std::clamp(current_value, 0.0, 2048.0);
            break;
#endif
        default:
            // No min or max value in case of Unknown attribute
            break;
        }

        up_to_date = true;
    }

    DEFINE_ENUM_STRINGIFYER_RANGE(EntityAttribute::Type, EntityAttribute::Type::Unknown, EntityAttribute::Type::NUM_ENTITY_ATTRIBUTES);
}
