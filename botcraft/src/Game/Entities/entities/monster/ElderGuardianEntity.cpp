#include "botcraft/Game/Entities/entities/monster/ElderGuardianEntity.hpp"

namespace Botcraft
{
    ElderGuardianEntity::ElderGuardianEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 8.0) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 80.0) });
    }

    ElderGuardianEntity::~ElderGuardianEntity()
    {

    }


    std::string ElderGuardianEntity::GetName() const
    {
        return "elder_guardian";
    }

    EntityType ElderGuardianEntity::GetType() const
    {
        return EntityType::ElderGuardian;
    }


    std::string ElderGuardianEntity::GetClassName()
    {
        return "elder_guardian";
    }

    EntityType ElderGuardianEntity::GetClassType()
    {
        return EntityType::ElderGuardian;
    }


    double ElderGuardianEntity::GetWidthImpl() const
    {
        return 1.9975;
    }

    double ElderGuardianEntity::GetHeightImpl() const
    {
        return 1.9975;
    }

}
