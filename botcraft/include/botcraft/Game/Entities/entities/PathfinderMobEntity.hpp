#pragma once

#include "botcraft/Game/Entities/entities/MobEntity.hpp"

namespace Botcraft
{
    class PathfinderMobEntity : public MobEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;

    public:
        PathfinderMobEntity();
        virtual ~PathfinderMobEntity();

        virtual bool IsPathfinderMob() const override;
    };
}
