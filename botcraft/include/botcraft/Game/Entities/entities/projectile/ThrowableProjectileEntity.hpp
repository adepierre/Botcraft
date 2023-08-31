#pragma once

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/Entity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
    class ThrowableProjectileEntity : public ProjectileEntity
#else
    class ThrowableProjectileEntity : public Entity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        static constexpr int hierarchy_metadata_count = ProjectileEntity::metadata_count + ProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;
#endif

    public:
        ThrowableProjectileEntity();
        virtual ~ThrowableProjectileEntity();

        virtual bool IsThrowableProjectile() const override;
    };
}
