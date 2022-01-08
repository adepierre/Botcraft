#include "botcraft/Game/Entities/entities/vehicle/MinecartTNTEntity.hpp"

namespace Botcraft
{
    MinecartTNTEntity::MinecartTNTEntity()
    {

    }

    MinecartTNTEntity::~MinecartTNTEntity()
    {

    }


    std::string MinecartTNTEntity::GetName() const
    {
        return "MinecartTNT";
    }

    EntityType MinecartTNTEntity::GetType() const
    {
        return EntityType::MinecartTNT;
    }

    AABB MinecartTNTEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double MinecartTNTEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartTNTEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string MinecartTNTEntity::GetClassName()
    {
        return "MinecartTNT";
    }

    EntityType MinecartTNTEntity::GetClassType()
    {
        return EntityType::MinecartTNT;
    }

}
