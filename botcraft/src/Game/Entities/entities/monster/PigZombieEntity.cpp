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

    AABB PigZombieEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
