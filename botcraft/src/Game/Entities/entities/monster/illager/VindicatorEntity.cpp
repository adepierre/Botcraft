#include "botcraft/Game/Entities/entities/monster/illager/VindicatorEntity.hpp"

namespace Botcraft
{
    VindicatorEntity::VindicatorEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.35) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 12.0) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 24.0) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 5.0) });
    }

    VindicatorEntity::~VindicatorEntity()
    {

    }


    std::string VindicatorEntity::GetName() const
    {
        return "vindicator";
    }

    EntityType VindicatorEntity::GetType() const
    {
        return EntityType::Vindicator;
    }


    std::string VindicatorEntity::GetClassName()
    {
        return "vindicator";
    }

    EntityType VindicatorEntity::GetClassType()
    {
        return EntityType::Vindicator;
    }


    double VindicatorEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double VindicatorEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
