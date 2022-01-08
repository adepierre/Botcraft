#include "botcraft/Game/Entities/entities/monster/StrayEntity.hpp"

namespace Botcraft
{
    StrayEntity::StrayEntity()
    {

    }

    StrayEntity::~StrayEntity()
    {

    }


    std::string StrayEntity::GetName() const
    {
        return "Stray";
    }

    EntityType StrayEntity::GetType() const
    {
        return EntityType::Stray;
    }

    AABB StrayEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double StrayEntity::GetWidth() const
    {
        return 0.6;
    }

    double StrayEntity::GetHeight() const
    {
        return 1.99;
    }


    std::string StrayEntity::GetClassName()
    {
        return "Stray";
    }

    EntityType StrayEntity::GetClassType()
    {
        return EntityType::Stray;
    }

}
