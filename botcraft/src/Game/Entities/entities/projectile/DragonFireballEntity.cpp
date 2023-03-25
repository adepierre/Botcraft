#include "botcraft/Game/Entities/entities/projectile/DragonFireballEntity.hpp"

namespace Botcraft
{
    DragonFireballEntity::DragonFireballEntity()
    {

    }

    DragonFireballEntity::~DragonFireballEntity()
    {

    }


    std::string DragonFireballEntity::GetName() const
    {
        return "dragon_fireball";
    }

    EntityType DragonFireballEntity::GetType() const
    {
        return EntityType::DragonFireball;
    }

    double DragonFireballEntity::GetWidth() const
    {
        return 1.0;
    }

    double DragonFireballEntity::GetHeight() const
    {
        return 1.0;
    }


    std::string DragonFireballEntity::GetClassName()
    {
        return "dragon_fireball";
    }

    EntityType DragonFireballEntity::GetClassType()
    {
        return EntityType::DragonFireball;
    }

}
