#include "botcraft/Game/Entities/entities/vehicle/MinecartEntity.hpp"

namespace Botcraft
{
    MinecartEntity::MinecartEntity()
    {

    }

    MinecartEntity::~MinecartEntity()
    {

    }


    std::string MinecartEntity::GetName() const
    {
        return "Minecart";
    }

    EntityType MinecartEntity::GetType() const
    {
        return EntityType::Minecart;
    }

    double MinecartEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string MinecartEntity::GetClassName()
    {
        return "Minecart";
    }

    EntityType MinecartEntity::GetClassType()
    {
        return EntityType::Minecart;
    }

}
