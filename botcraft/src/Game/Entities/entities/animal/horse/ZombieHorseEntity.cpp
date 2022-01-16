#include "botcraft/Game/Entities/entities/animal/horse/ZombieHorseEntity.hpp"

namespace Botcraft
{
    ZombieHorseEntity::ZombieHorseEntity()
    {

    }

    ZombieHorseEntity::~ZombieHorseEntity()
    {

    }


    std::string ZombieHorseEntity::GetName() const
    {
        return "ZombieHorse";
    }

    EntityType ZombieHorseEntity::GetType() const
    {
        return EntityType::ZombieHorse;
    }

    double ZombieHorseEntity::GetWidth() const
    {
        return 1.3964844;
    }

    double ZombieHorseEntity::GetHeight() const
    {
        return 1.6;
    }


    std::string ZombieHorseEntity::GetClassName()
    {
        return "ZombieHorse";
    }

    EntityType ZombieHorseEntity::GetClassType()
    {
        return EntityType::ZombieHorse;
    }

}
