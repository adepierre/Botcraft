#if PROTOCOL_VERSION < 579
#include "botcraft/Game/Entities/entities/monster/PigZombieEntity.hpp"

namespace Botcraft
{
    PigZombieEntity::PigZombieEntity()
    {

    }

    PigZombieEntity::~PigZombieEntity()
    {

    }


    std::string PigZombieEntity::GetName() const
    {
        return "PigZombieEntity";
    }

    EntityType PigZombieEntity::GetType() const
    {
        return EntityType::PigZombie;
    }

    double PigZombieEntity::GetWidth() const
    {
        return 0.6;
    }

    double PigZombieEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string PigZombieEntity::GetClassName()
    {
        return "PigZombieEntity";
    }

    EntityType PigZombieEntity::GetClassType()
    {
        return EntityType::PigZombie;
    }

}
#endif
