#include "botcraft/Game/Entities/entities/animal/horse/SkeletonHorseEntity.hpp"

namespace Botcraft
{
    SkeletonHorseEntity::SkeletonHorseEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 15.0) });
        attributes.insert({ EntityAttribute::Type::MovementSpeed, EntityAttribute(EntityAttribute::Type::MovementSpeed, 0.2) });
    }

    SkeletonHorseEntity::~SkeletonHorseEntity()
    {

    }


    std::string SkeletonHorseEntity::GetName() const
    {
        return "skeleton_horse";
    }

    EntityType SkeletonHorseEntity::GetType() const
    {
        return EntityType::SkeletonHorse;
    }


    std::string SkeletonHorseEntity::GetClassName()
    {
        return "skeleton_horse";
    }

    EntityType SkeletonHorseEntity::GetClassType()
    {
        return EntityType::SkeletonHorse;
    }


    double SkeletonHorseEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double SkeletonHorseEntity::GetHeightImpl() const
    {
        return 1.6;
    }

}
