#include "botcraft/Game/Entities/entities/projectile/EvokerFangsEntity.hpp"

namespace Botcraft
{
    EvokerFangsEntity::EvokerFangsEntity()
    {

    }

    EvokerFangsEntity::~EvokerFangsEntity()
    {

    }


    std::string EvokerFangsEntity::GetName() const
    {
        return "EvokerFangs";
    }

    EntityType EvokerFangsEntity::GetType() const
    {
        return EntityType::EvokerFangs;
    }

    AABB EvokerFangsEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double EvokerFangsEntity::GetWidth() const
    {
        return 0.5;
    }

    double EvokerFangsEntity::GetHeight() const
    {
        return 0.8;
    }


    std::string EvokerFangsEntity::GetClassName()
    {
        return "EvokerFangs";
    }

    EntityType EvokerFangsEntity::GetClassType()
    {
        return EntityType::EvokerFangs;
    }

}
