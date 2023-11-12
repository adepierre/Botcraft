#if PROTOCOL_VERSION < 579 /* < 1.16 */
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
        return "zombie_pigman";
    }

    EntityType PigZombieEntity::GetType() const
    {
        return EntityType::PigZombie;
    }


    std::string PigZombieEntity::GetClassName()
    {
        return "zombie_pigman";
    }

    EntityType PigZombieEntity::GetClassType()
    {
        return EntityType::PigZombie;
    }


    double PigZombieEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double PigZombieEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
