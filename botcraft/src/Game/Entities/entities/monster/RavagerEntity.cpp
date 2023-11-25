#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/monster/RavagerEntity.hpp"

namespace Botcraft
{
    RavagerEntity::RavagerEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 100.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.3) });
        attributes.insert({ EntityAttribute::Type::KnockbackResistance, EntityAttribute(EntityAttribute::Type::KnockbackResistance, 0.75) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 12.0) });
        attributes.insert({ EntityAttribute::Type::AttackKnockback, EntityAttribute(EntityAttribute::Type::AttackKnockback, 1.5) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 32.0) });
    }

    RavagerEntity::~RavagerEntity()
    {

    }


    std::string RavagerEntity::GetName() const
    {
        return "ravager";
    }

    EntityType RavagerEntity::GetType() const
    {
        return EntityType::Ravager;
    }


    std::string RavagerEntity::GetClassName()
    {
        return "ravager";
    }

    EntityType RavagerEntity::GetClassType()
    {
        return EntityType::Ravager;
    }


    double RavagerEntity::GetWidthImpl() const
    {
        return 1.95;
    }

    double RavagerEntity::GetHeightImpl() const
    {
        return 2.2;
    }

}
#endif
