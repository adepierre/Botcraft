#include "botcraft/Game/Entities/entities/vehicle/minecart/MinecartSpawnerEntity.hpp"

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
        return "spawner_minecart";
    }

    EntityType MinecartSpawnerEntity::GetType() const
    {
        return EntityType::MinecartSpawner;
    }


    std::string MinecartSpawnerEntity::GetClassName()
    {
        return "spawner_minecart";
    }

    EntityType MinecartSpawnerEntity::GetClassType()
    {
        return EntityType::MinecartSpawner;
    }


    double MinecartSpawnerEntity::GetWidthImpl() const
    {
        return 0.98;
    }

    double MinecartSpawnerEntity::GetHeightImpl() const
    {
        return 0.7;
    }

}
