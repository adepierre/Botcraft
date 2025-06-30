#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
#include "botcraft/Game/Entities/entities/FlyingMobEntity.hpp"

namespace Botcraft
{
    FlyingMobEntity::FlyingMobEntity()
    {

    }

    FlyingMobEntity::~FlyingMobEntity()
    {

    }

    bool FlyingMobEntity::IsFlyingMob() const
    {
        return true;
    }

}
#endif
