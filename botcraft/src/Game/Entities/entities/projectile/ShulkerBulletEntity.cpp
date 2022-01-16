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
