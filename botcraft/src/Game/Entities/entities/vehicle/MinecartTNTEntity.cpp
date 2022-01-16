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
