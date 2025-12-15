#pragma once

#include "botcraft/Game/Entities/entities/PathfinderMobEntity.hpp"

namespace Botcraft
{
    class WaterAnimalEntity : public PathfinderMobEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = PathfinderMobEntity::metadata_count + PathfinderMobEntity::hierarchy_metadata_count;

    public:
        WaterAnimalEntity();
        virtual ~WaterAnimalEntity();

        virtual bool IsWaterAnimal() const override;
    };
}
