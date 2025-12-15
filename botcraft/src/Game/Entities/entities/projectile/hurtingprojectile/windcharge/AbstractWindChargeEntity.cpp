#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/windcharge/AbstractWindChargeEntity.hpp"

namespace Botcraft
{
    AbstractWindChargeEntity::AbstractWindChargeEntity()
    {

    }

    AbstractWindChargeEntity::~AbstractWindChargeEntity()
    {

    }


    bool AbstractWindChargeEntity::IsAbstractWindCharge() const
    {
        return true;
    }

}
#endif
