#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/projectile/ProjectileEntity.hpp"

namespace Botcraft
{
    ProjectileEntity::ProjectileEntity()
    {

    }

    ProjectileEntity::~ProjectileEntity()
    {

    }

    bool ProjectileEntity::IsProjectile() const
    {
        return true;
    }

}
#endif
