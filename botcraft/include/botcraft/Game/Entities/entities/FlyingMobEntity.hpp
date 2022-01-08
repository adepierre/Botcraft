#pragma once

#include "botcraft/Game/Entities/entities/MobEntity.hpp"

namespace Botcraft
{
    class FlyingMobEntity : public MobEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = MobEntity::metadata_count + MobEntity::hierarchy_metadata_count;

    public:
        FlyingMobEntity();
        virtual ~FlyingMobEntity();

        virtual bool IsFlyingMob() const override;
    };
}
