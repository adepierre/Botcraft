#include "botcraft/Game/Entities/entities/monster/skeleton/WitherSkeletonEntity.hpp"

namespace Botcraft
{
    WitherSkeletonEntity::WitherSkeletonEntity()
    {

    }

    WitherSkeletonEntity::~WitherSkeletonEntity()
    {

    }


    std::string WitherSkeletonEntity::GetName() const
    {
        return "wither_skeleton";
    }

    EntityType WitherSkeletonEntity::GetType() const
    {
        return EntityType::WitherSkeleton;
    }


    std::string WitherSkeletonEntity::GetClassName()
    {
        return "wither_skeleton";
    }

    EntityType WitherSkeletonEntity::GetClassType()
    {
        return EntityType::WitherSkeleton;
    }


    double WitherSkeletonEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double WitherSkeletonEntity::GetHeightImpl() const
    {
        return 2.4;
    }

}
