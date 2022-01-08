#include "botcraft/Game/Entities/entities/vehicle/MinecartHopperEntity.hpp"

namespace Botcraft
{
    MinecartHopperEntity::MinecartHopperEntity()
    {

    }

    MinecartHopperEntity::~MinecartHopperEntity()
    {

    }


    std::string MinecartHopperEntity::GetName() const
    {
        return "MinecartHopper";
    }

    EntityType MinecartHopperEntity::GetType() const
    {
        return EntityType::MinecartHopper;
    }

    AABB MinecartHopperEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double MinecartHopperEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartHopperEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string MinecartHopperEntity::GetClassName()
    {
        return "MinecartHopper";
    }

    EntityType MinecartHopperEntity::GetClassType()
    {
        return EntityType::MinecartHopper;
    }

}
