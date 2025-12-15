#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/SmallFireballEntity.hpp"

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


    std::string SmallFireballEntity::GetClassName()
    {
        return "small_fireball";
    }

    EntityType SmallFireballEntity::GetClassType()
    {
        return EntityType::SmallFireball;
    }


    double SmallFireballEntity::GetWidthImpl() const
    {
        return 0.3125;
    }

    double SmallFireballEntity::GetHeightImpl() const
    {
        return 0.3125;
    }

}
