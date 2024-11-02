#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "botcraft/Game/Entities/entities/animal/AgeableWaterCreatureEntity.hpp"

namespace Botcraft
{
    AgeableWaterCreatureEntity::AgeableWaterCreatureEntity()
    {

    }

    AgeableWaterCreatureEntity::~AgeableWaterCreatureEntity()
    {

    }

    bool AgeableWaterCreatureEntity::IsAgeableWaterCreature() const
    {
        return true;
    }
}
#endif
