#include "botcraft/Game/Entities/entities/vehicle/minecart/MinecartHopperEntity.hpp"

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
        return "hopper_minecart";
    }

    EntityType MinecartHopperEntity::GetType() const
    {
        return EntityType::MinecartHopper;
    }


    std::string MinecartHopperEntity::GetClassName()
    {
        return "hopper_minecart";
    }

    EntityType MinecartHopperEntity::GetClassType()
    {
        return EntityType::MinecartHopper;
    }


    double MinecartHopperEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartHopperEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
