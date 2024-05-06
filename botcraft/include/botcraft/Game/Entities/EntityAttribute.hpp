#pragma once

#include <iosfwd>
#include <map>
#include <optional>

namespace Botcraft
{
    class EntityAttribute
    {
    public:
        enum class Type : char
        {
            Unknown = -1,
            Armor,
            ArmorToughness,
            AttackDamage,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            AttackKnockback,
#endif
            AttackSpeed,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            PlayerBlockBreakSpeed,
            PlayerBlockInteractionRange,
            PlayerEntityInteractionRange,
            FallDamageMultiplier,
#endif
            FlyingSpeed,
            FollowRange,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            Gravity,
            JumpStrength,
#else
            HorseJumpStrength,
#endif
            KnockbackResistance,
            Luck,
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
            MaxAbsorption,
#endif
            MaxHealth,
            MovementSpeed,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            SafeFallDistance,
            Scale,
#endif
            ZombieSpawnReinforcementsChance,
#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
            StepHeight,
#endif
            NUM_ENTITY_ATTRIBUTES
        };

        struct Modifier
        {
            enum class Operation : char
            {
                Add = 0,
                MultiplyBase = 1,
                MultiplyTotal = 2
            };

            double amount = 0.0;
            Operation operation = Operation::Add;
        };

        EntityAttribute(const Type type_, const double base_value_);
        EntityAttribute() = delete;

        void SetBaseValue(const double new_value);
        void ClearModifiers();
        void RemoveModifier(const std::array<unsigned char, 16>& uuid);
        void SetModifier(const std::array<unsigned char, 16>& uuid, const Modifier& modifier);

        Type GetType() const;
        double GetBaseValue() const;
        const std::map<std::array<unsigned char, 16>, Modifier>& GetModifiers() const;
        double GetValue() const;
        std::optional<Modifier> GetModifier(const std::array<unsigned char, 16>& uuid);

#if PROTOCOL_VERSION < 766 /* < 1.20.4 */
        static std::string TypeToString(const Type type);
        static Type StringToType(const std::string& s);
#endif

    private:
        void UpdateValue() const;

    private:
        Type type;
        double base_value;
        mutable double current_value;
        mutable bool up_to_date;
        std::map<std::array<unsigned char, 16>, Modifier> modifiers;
    };
    std::ostream& operator<<(std::ostream& os, const EntityAttribute::Type v);
}
