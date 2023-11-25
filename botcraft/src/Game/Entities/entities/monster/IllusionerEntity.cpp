#include "botcraft/Game/Entities/entities/monster/IllusionerEntity.hpp"

namespace Botcraft
{
    IllusionerEntity::IllusionerEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.5) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 18.0) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 32.0) });
    }

    IllusionerEntity::~IllusionerEntity()
    {

    }


    std::string IllusionerEntity::GetName() const
    {
        return "illusioner";
    }

    EntityType IllusionerEntity::GetType() const
    {
        return EntityType::Illusioner;
    }


    std::string IllusionerEntity::GetClassName()
    {
        return "illusioner";
    }

    EntityType IllusionerEntity::GetClassType()
    {
        return EntityType::Illusioner;
    }


    double IllusionerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double IllusionerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
