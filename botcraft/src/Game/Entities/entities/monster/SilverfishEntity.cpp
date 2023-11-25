#include "botcraft/Game/Entities/entities/monster/SilverfishEntity.hpp"

namespace Botcraft
{
    SilverfishEntity::SilverfishEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 8.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 1.0) });
    }

    SilverfishEntity::~SilverfishEntity()
    {

    }


    std::string SilverfishEntity::GetName() const
    {
        return "silverfish";
    }

    EntityType SilverfishEntity::GetType() const
    {
        return EntityType::Silverfish;
    }


    std::string SilverfishEntity::GetClassName()
    {
        return "silverfish";
    }

    EntityType SilverfishEntity::GetClassType()
    {
        return EntityType::Silverfish;
    }


    double SilverfishEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double SilverfishEntity::GetHeightImpl() const
    {
        return 0.3;
    }

}
