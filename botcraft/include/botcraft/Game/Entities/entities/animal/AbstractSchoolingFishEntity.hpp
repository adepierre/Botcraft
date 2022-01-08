#pragma once

#include "botcraft/Game/Entities/entities/animal/AbstractFishEntity.hpp"

namespace Botcraft
{
    class AbstractSchoolingFishEntity : public AbstractFishEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractFishEntity::metadata_count + AbstractFishEntity::hierarchy_metadata_count;

    public:
        AbstractSchoolingFishEntity();
        virtual ~AbstractSchoolingFishEntity();

        virtual bool IsAbstractSchoolingFish() const override;
    };
}
