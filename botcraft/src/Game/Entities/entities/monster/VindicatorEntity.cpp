#include "botcraft/Game/Entities/entities/monster/VindicatorEntity.hpp"

namespace Botcraft
{
    VindicatorEntity::VindicatorEntity()
    {

    }

    VindicatorEntity::~VindicatorEntity()
    {

    }


    std::string VindicatorEntity::GetName() const
    {
        return "Vindicator";
    }

    EntityType VindicatorEntity::GetType() const
    {
        return EntityType::Vindicator;
    }

    AABB VindicatorEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double VindicatorEntity::GetWidth() const
    {
        return 0.6;
    }

    double VindicatorEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string VindicatorEntity::GetClassName()
    {
        return "Vindicator";
    }

    EntityType VindicatorEntity::GetClassType()
    {
        return EntityType::Vindicator;
    }

}
