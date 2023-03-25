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
        return "egg";
    }

    EntityType ThrownEggEntity::GetType() const
    {
        return EntityType::ThrownEgg;
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
        return "egg";
    }

    EntityType ThrownEggEntity::GetClassType()
    {
        return EntityType::ThrownEgg;
    }

}
