#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "botcraft/Game/Entities/entities/projectile/AbstractThrownPotionEntity.hpp"

namespace Botcraft
{
    AbstractThrownPotionEntity::AbstractThrownPotionEntity()
    {

    }

    AbstractThrownPotionEntity::~AbstractThrownPotionEntity()
    {

    }

    bool AbstractThrownPotionEntity::IsAbstractThrownPotion() const
    {
        return true;
    }

}
#endif
