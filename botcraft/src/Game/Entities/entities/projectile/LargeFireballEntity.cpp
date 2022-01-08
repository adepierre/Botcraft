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
        return "LargeFireball";
    }

    EntityType LargeFireballEntity::GetType() const
    {
        return EntityType::LargeFireball;
    }

    AABB LargeFireballEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "LargeFireball";
    }

    EntityType LargeFireballEntity::GetClassType()
    {
        return EntityType::LargeFireball;
    }

}
