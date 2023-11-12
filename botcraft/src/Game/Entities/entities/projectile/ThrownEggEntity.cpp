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


    std::string ThrownEggEntity::GetClassName()
    {
        return "egg";
    }

    EntityType ThrownEggEntity::GetClassType()
    {
        return EntityType::ThrownEgg;
    }


    double ThrownEggEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownEggEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
