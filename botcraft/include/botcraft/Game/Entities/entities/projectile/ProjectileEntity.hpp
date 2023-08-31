#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class ProjectileEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        ProjectileEntity();
        virtual ~ProjectileEntity();

        virtual bool IsProjectile() const override;
    };
}
#endif
