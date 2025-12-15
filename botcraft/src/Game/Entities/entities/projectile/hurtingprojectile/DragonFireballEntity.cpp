#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/DragonFireballEntity.hpp"

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


    std::string DragonFireballEntity::GetClassName()
    {
        return "dragon_fireball";
    }

    EntityType DragonFireballEntity::GetClassType()
    {
        return EntityType::DragonFireball;
    }


    double DragonFireballEntity::GetWidthImpl() const
    {
        return 1.0;
    }

    double DragonFireballEntity::GetHeightImpl() const
    {
        return 1.0;
    }

}
