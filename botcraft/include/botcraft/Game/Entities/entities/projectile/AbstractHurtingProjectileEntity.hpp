#pragma once

#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578
    class AbstractHurtingProjectileEntity : public ProjectileEntity
#else
    class AbstractHurtingProjectileEntity : public Entity
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
        AbstractHurtingProjectileEntity();
        virtual ~AbstractHurtingProjectileEntity();

        virtual bool IsAbstractHurtingProjectile() const override;
    };
}
