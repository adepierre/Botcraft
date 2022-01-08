#include "botcraft/Game/Entities/entities/projectile/ShulkerBulletEntity.hpp"

namespace Botcraft
{
    ShulkerBulletEntity::ShulkerBulletEntity()
    {

    }

    ShulkerBulletEntity::~ShulkerBulletEntity()
    {

    }


    std::string ShulkerBulletEntity::GetName() const
    {
        return "ShulkerBullet";
    }

    EntityType ShulkerBulletEntity::GetType() const
    {
        return EntityType::ShulkerBullet;
    }

    AABB ShulkerBulletEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ShulkerBulletEntity::GetWidth() const
    {
        return 0.3125;
    }

    double ShulkerBulletEntity::GetHeight() const
    {
        return 0.3125;
    }


    std::string ShulkerBulletEntity::GetClassName()
    {
        return "ShulkerBullet";
    }

    EntityType ShulkerBulletEntity::GetClassType()
    {
        return EntityType::ShulkerBullet;
    }

}
