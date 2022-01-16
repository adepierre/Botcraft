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
        return "MinecartChest";
    }

    EntityType MinecartChestEntity::GetType() const
    {
        return EntityType::MinecartChest;
    }

    double MinecartChestEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartChestEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string MinecartChestEntity::GetClassName()
    {
        return "MinecartChest";
    }

    EntityType MinecartChestEntity::GetClassType()
    {
        return EntityType::MinecartChest;
    }

}
