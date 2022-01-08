#include "botcraft/Game/Entities/entities/monster/EvokerEntity.hpp"

namespace Botcraft
{
    EvokerEntity::EvokerEntity()
    {

    }

    EvokerEntity::~EvokerEntity()
    {

    }


    std::string EvokerEntity::GetName() const
    {
        return "Evoker";
    }

    EntityType EvokerEntity::GetType() const
    {
        return EntityType::Evoker;
    }

    AABB EvokerEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double EvokerEntity::GetWidth() const
    {
        return 0.6;
    }

    double EvokerEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string EvokerEntity::GetClassName()
    {
        return "Evoker";
    }

    EntityType EvokerEntity::GetClassType()
    {
        return EntityType::Evoker;
    }

}
