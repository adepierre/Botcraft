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
        return "DragonFireball";
    }

    EntityType DragonFireballEntity::GetType() const
    {
        return EntityType::DragonFireball;
    }

    AABB DragonFireballEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "DragonFireball";
    }

    EntityType DragonFireballEntity::GetClassType()
    {
        return EntityType::DragonFireball;
    }

}
