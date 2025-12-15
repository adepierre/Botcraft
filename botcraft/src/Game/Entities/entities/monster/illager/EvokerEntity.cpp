#include "botcraft/Game/Entities/entities/monster/illager/EvokerEntity.hpp"

namespace Botcraft
{
    EvokerEntity::EvokerEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.5) });
        attributes.insert({ EntityAttribute::Type::FollowRange, EntityAttribute(EntityAttribute::Type::FollowRange, 12.0) });
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 24.0) });
    }

    EvokerEntity::~EvokerEntity()
    {

    }


    std::string EvokerEntity::GetName() const
    {
        return "evoker";
    }

    EntityType EvokerEntity::GetType() const
    {
        return EntityType::Evoker;
    }


    std::string EvokerEntity::GetClassName()
    {
        return "evoker";
    }

    EntityType EvokerEntity::GetClassType()
    {
        return EntityType::Evoker;
    }


    double EvokerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double EvokerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
