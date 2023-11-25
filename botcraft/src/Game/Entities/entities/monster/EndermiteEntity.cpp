#include "botcraft/Game/Entities/entities/monster/EndermiteEntity.hpp"

namespace Botcraft
{
    EndermiteEntity::EndermiteEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 8.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.25) });
        attributes.insert({ EntityAttribute::Type::AttackDamage, EntityAttribute(EntityAttribute::Type::AttackDamage, 2.0) });
    }

    EndermiteEntity::~EndermiteEntity()
    {

    }


    std::string EndermiteEntity::GetName() const
    {
        return "endermite";
    }

    EntityType EndermiteEntity::GetType() const
    {
        return EntityType::Endermite;
    }


    std::string EndermiteEntity::GetClassName()
    {
        return "endermite";
    }

    EntityType EndermiteEntity::GetClassType()
    {
        return EntityType::Endermite;
    }


    double EndermiteEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double EndermiteEntity::GetHeightImpl() const
    {
        return 0.3;
    }

}
