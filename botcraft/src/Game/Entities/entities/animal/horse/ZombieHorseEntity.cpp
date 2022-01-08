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

    AABB ZombieHorseEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
