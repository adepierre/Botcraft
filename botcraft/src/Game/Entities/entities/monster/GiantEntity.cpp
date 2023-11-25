#include "botcraft/Game/Entities/entities/monster/GiantEntity.hpp"

namespace Botcraft
{
    GiantEntity::GiantEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 100.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.5) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 50.0) });
    }

    GiantEntity::~GiantEntity()
    {

    }


    std::string GiantEntity::GetName() const
    {
        return "giant";
    }

    EntityType GiantEntity::GetType() const
    {
        return EntityType::Giant;
    }


    std::string GiantEntity::GetClassName()
    {
        return "giant";
    }

    EntityType GiantEntity::GetClassType()
    {
        return EntityType::Giant;
    }


    double GiantEntity::GetWidthImpl() const
    {
        return 3.6;
    }

    double GiantEntity::GetHeightImpl() const
    {
        return 12.0;
    }

}
