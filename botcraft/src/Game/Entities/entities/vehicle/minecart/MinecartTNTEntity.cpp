#include "botcraft/Game/Entities/entities/vehicle/minecart/MinecartTNTEntity.hpp"

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
        return "tnt_minecart";
    }

    EntityType MinecartTNTEntity::GetType() const
    {
        return EntityType::MinecartTNT;
    }


    std::string MinecartTNTEntity::GetClassName()
    {
        return "tnt_minecart";
    }

    EntityType MinecartTNTEntity::GetClassType()
    {
        return EntityType::MinecartTNT;
    }


    double MinecartTNTEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartTNTEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
