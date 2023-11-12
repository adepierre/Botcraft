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
        return "shulker_bullet";
    }

    EntityType ShulkerBulletEntity::GetType() const
    {
        return EntityType::ShulkerBullet;
    }


    std::string ShulkerBulletEntity::GetClassName()
    {
        return "shulker_bullet";
    }

    EntityType ShulkerBulletEntity::GetClassType()
    {
        return EntityType::ShulkerBullet;
    }


    double ShulkerBulletEntity::GetWidthImpl() const
    {
        return 0.3125;
    }

    double ShulkerBulletEntity::GetHeightImpl() const
    {
        return 0.3125;
    }

}
