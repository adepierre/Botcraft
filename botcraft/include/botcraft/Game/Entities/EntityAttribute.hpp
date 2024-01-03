#pragma once

#include <iosfwd>
#include <map>
#include <optional>
#include <string>

namespace Botcraft
{
    class EntityAttribute
    {
    public:
        enum class Type : char
        {
            Unknown = -1,
            MaxHealth,
            FollowRange,
            KnockbackResistance,
            MovementSpeed,
            FlyingSpeed,
            AttackDamage,
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            AttackKnockback,
#endif
            AttackSpeed,
            Armor,
            ArmorToughness,
            Luck,
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
            MaxAbsorption,
#endif
            ZombieSpawnReinforcementsChance,
            HorseJumpStrength,
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

        static std::string TypeToString(const Type type);
        static Type StringToType(const std::string& s);

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
