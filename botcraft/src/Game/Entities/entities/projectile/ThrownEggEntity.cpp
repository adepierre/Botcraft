#include "botcraft/Game/Entities/entities/projectile/ThrownEggEntity.hpp"

namespace Botcraft
{
    ThrownEggEntity::ThrownEggEntity()
    {

    }

    ThrownEggEntity::~ThrownEggEntity()
    {

    }


    std::string ThrownEggEntity::GetName() const
    {
        return "ThrownEgg";
    }

    EntityType ThrownEggEntity::GetType() const
    {
        return EntityType::ThrownEgg;
    }

    AABB ThrownEggEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ThrownEggEntity::GetWidth() const
    {
        return 0.25;
    }

    double ThrownEggEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string ThrownEggEntity::GetClassName()
    {
        return "ThrownEgg";
    }

    EntityType ThrownEggEntity::GetClassType()
    {
        return EntityType::ThrownEgg;
    }

}
