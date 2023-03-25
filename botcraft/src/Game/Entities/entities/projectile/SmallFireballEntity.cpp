#include "botcraft/Game/Entities/entities/projectile/SmallFireballEntity.hpp"

namespace Botcraft
{
    SmallFireballEntity::SmallFireballEntity()
    {

    }

    SmallFireballEntity::~SmallFireballEntity()
    {

    }


    std::string SmallFireballEntity::GetName() const
    {
        return "small_fireball";
    }

    EntityType SmallFireballEntity::GetType() const
    {
        return EntityType::SmallFireball;
    }

    double SmallFireballEntity::GetWidth() const
    {
        return 0.3125;
    }

    double SmallFireballEntity::GetHeight() const
    {
        return 0.3125;
    }


    std::string SmallFireballEntity::GetClassName()
    {
        return "small_fireball";
    }

    EntityType SmallFireballEntity::GetClassType()
    {
        return EntityType::SmallFireball;
    }

}
