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
        return "minecart";
    }

    EntityType MinecartEntity::GetType() const
    {
        return EntityType::Minecart;
    }


    std::string MinecartEntity::GetClassName()
    {
        return "minecart";
    }

    EntityType MinecartEntity::GetClassType()
    {
        return EntityType::Minecart;
    }


    double MinecartEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
