#include "botcraft/Game/Entities/entities/vehicle/MinecartSpawnerEntity.hpp"

namespace Botcraft
{
    MinecartSpawnerEntity::MinecartSpawnerEntity()
    {

    }

    MinecartSpawnerEntity::~MinecartSpawnerEntity()
    {

    }


    std::string MinecartSpawnerEntity::GetName() const
    {
        return "MinecartSpawner";
    }

    EntityType MinecartSpawnerEntity::GetType() const
    {
        return EntityType::MinecartSpawner;
    }

    double MinecartSpawnerEntity::GetWidth() const
    {
        return 0.98;
    }

    double MinecartSpawnerEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string MinecartSpawnerEntity::GetClassName()
    {
        return "MinecartSpawner";
    }

    EntityType MinecartSpawnerEntity::GetClassType()
    {
        return EntityType::MinecartSpawner;
    }

}
