#include "botcraft/Game/Entities/entities/monster/MagmaCubeEntity.hpp"

namespace Botcraft
{
    MagmaCubeEntity::MagmaCubeEntity()
    {

    }

    MagmaCubeEntity::~MagmaCubeEntity()
    {

    }


    std::string MagmaCubeEntity::GetName() const
    {
        return "MagmaCube";
    }

    EntityType MagmaCubeEntity::GetType() const
    {
        return EntityType::MagmaCube;
    }

    AABB MagmaCubeEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double MagmaCubeEntity::GetWidth() const
    {
        return 2.04;
    }

    double MagmaCubeEntity::GetHeight() const
    {
        return 2.04;
    }


    std::string MagmaCubeEntity::GetClassName()
    {
        return "MagmaCube";
    }

    EntityType MagmaCubeEntity::GetClassType()
    {
        return EntityType::MagmaCube;
    }

}
