#include "botcraft/Game/Entities/entities/animal/horse/SkeletonHorseEntity.hpp"

namespace Botcraft
{
    SkeletonHorseEntity::SkeletonHorseEntity()
    {

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
