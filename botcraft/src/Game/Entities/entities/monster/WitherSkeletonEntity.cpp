#include "botcraft/Game/Entities/entities/monster/WitherSkeletonEntity.hpp"

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
        return "WitherSkeleton";
    }

    EntityType WitherSkeletonEntity::GetType() const
    {
        return EntityType::WitherSkeleton;
    }

    AABB WitherSkeletonEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double WitherSkeletonEntity::GetWidth() const
    {
        return 0.7;
    }

    double WitherSkeletonEntity::GetHeight() const
    {
        return 2.4;
    }


    std::string WitherSkeletonEntity::GetClassName()
    {
        return "WitherSkeleton";
    }

    EntityType WitherSkeletonEntity::GetClassType()
    {
        return EntityType::WitherSkeleton;
    }

}
