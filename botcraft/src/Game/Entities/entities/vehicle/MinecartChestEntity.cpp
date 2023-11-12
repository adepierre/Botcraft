#include "botcraft/Game/Entities/entities/vehicle/MinecartChestEntity.hpp"

namespace Botcraft
{
    MinecartChestEntity::MinecartChestEntity()
    {

    }

    MinecartChestEntity::~MinecartChestEntity()
    {

    }


    std::string MinecartChestEntity::GetName() const
    {
        return "chest_minecart";
    }

    EntityType MinecartChestEntity::GetType() const
    {
        return EntityType::MinecartChest;
    }


    std::string MinecartChestEntity::GetClassName()
    {
        return "chest_minecart";
    }

    EntityType MinecartChestEntity::GetClassType()
    {
        return EntityType::MinecartChest;
    }


    double MinecartChestEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartChestEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
