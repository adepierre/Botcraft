#include "botcraft/Game/Entities/entities/projectile/SpectralArrowEntity.hpp"

namespace Botcraft
{
    SpectralArrowEntity::SpectralArrowEntity()
    {

    }

    SpectralArrowEntity::~SpectralArrowEntity()
    {

    }


    std::string SpectralArrowEntity::GetName() const
    {
        return "SpectralArrow";
    }

    EntityType SpectralArrowEntity::GetType() const
    {
        return EntityType::SpectralArrow;
    }

    AABB SpectralArrowEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SpectralArrowEntity::GetWidth() const
    {
        return 0.5;
    }

    double SpectralArrowEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string SpectralArrowEntity::GetClassName()
    {
        return "SpectralArrow";
    }

    EntityType SpectralArrowEntity::GetClassType()
    {
        return EntityType::SpectralArrow;
    }

}
