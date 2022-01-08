#pragma once

#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578
    class ShulkerBulletEntity : public ProjectileEntity
#else
    class ShulkerBulletEntity : public Entity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION > 578
        static constexpr int hierarchy_metadata_count = ProjectileEntity::metadata_count + ProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#endif

    public:
        ShulkerBulletEntity();
        virtual ~ShulkerBulletEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}
