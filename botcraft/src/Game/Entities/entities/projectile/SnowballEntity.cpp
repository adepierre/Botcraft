#include "botcraft/Game/Entities/entities/projectile/SnowballEntity.hpp"

namespace Botcraft
{
    SnowballEntity::SnowballEntity()
    {

    }

    SnowballEntity::~SnowballEntity()
    {

    }


    std::string SnowballEntity::GetName() const
    {
        return "Snowball";
    }

    EntityType SnowballEntity::GetType() const
    {
        return EntityType::Snowball;
    }

    AABB SnowballEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SnowballEntity::GetWidth() const
    {
        return 0.25;
    }

    double SnowballEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string SnowballEntity::GetClassName()
    {
        return "Snowball";
    }

    EntityType SnowballEntity::GetClassType()
    {
        return EntityType::Snowball;
    }

}
