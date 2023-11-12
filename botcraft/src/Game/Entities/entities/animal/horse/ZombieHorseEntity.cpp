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
        return "zombie_horse";
    }

    EntityType ZombieHorseEntity::GetType() const
    {
        return EntityType::ZombieHorse;
    }


    std::string ZombieHorseEntity::GetClassName()
    {
        return "zombie_horse";
    }

    EntityType ZombieHorseEntity::GetClassType()
    {
        return EntityType::ZombieHorse;
    }


    double ZombieHorseEntity::GetWidthImpl() const
    {
        return 1.3964844;
    }

    double ZombieHorseEntity::GetHeightImpl() const
    {
        return 1.6;
    }

}
