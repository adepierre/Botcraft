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
        return "SkeletonHorse";
    }

    EntityType SkeletonHorseEntity::GetType() const
    {
        return EntityType::SkeletonHorse;
    }

    AABB SkeletonHorseEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SkeletonHorseEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double SkeletonHorseEntity::GetHeight() const
    {
        return 1.6;
    }


    std::string SkeletonHorseEntity::GetClassName()
    {
        return "SkeletonHorse";
    }

    EntityType SkeletonHorseEntity::GetClassType()
    {
        return EntityType::SkeletonHorse;
    }

}
