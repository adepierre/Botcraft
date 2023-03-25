#include "botcraft/Game/Entities/entities/projectile/LargeFireballEntity.hpp"

namespace Botcraft
{
    LargeFireballEntity::LargeFireballEntity()
    {

    }

    LargeFireballEntity::~LargeFireballEntity()
    {

    }


    std::string LargeFireballEntity::GetName() const
    {
        return "fireball";
    }

    EntityType LargeFireballEntity::GetType() const
    {
        return EntityType::LargeFireball;
    }

    double LargeFireballEntity::GetWidth() const
    {
        return 1.0;
    }

    double LargeFireballEntity::GetHeight() const
    {
        return 1.0;
    }


    std::string LargeFireballEntity::GetClassName()
    {
        return "fireball";
    }

    EntityType LargeFireballEntity::GetClassType()
    {
        return EntityType::LargeFireball;
    }

}
