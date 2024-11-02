#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    class AgeableWaterCreatureEntity : public AgeableMobEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;

    public:
        AgeableWaterCreatureEntity();
        virtual ~AgeableWaterCreatureEntity();

        virtual bool IsAgeableWaterCreature() const override;
    };
}
#endif
