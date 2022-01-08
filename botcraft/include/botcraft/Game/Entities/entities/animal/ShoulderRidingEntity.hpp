#pragma once

#include "botcraft/Game/Entities/entities/TamableAnimalEntity.hpp"

namespace Botcraft
{
    class ShoulderRidingEntity : public TamableAnimalEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = TamableAnimalEntity::metadata_count + TamableAnimalEntity::hierarchy_metadata_count;

    public:
        ShoulderRidingEntity();
        virtual ~ShoulderRidingEntity();

        virtual bool IsShoulderRidingEntity() const override;
    };
}
