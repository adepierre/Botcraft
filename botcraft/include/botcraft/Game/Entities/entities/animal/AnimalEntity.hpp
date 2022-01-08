#pragma once

#include "botcraft/Game/Entities/entities/AgeableMobEntity.hpp"

namespace Botcraft
{
    class AnimalEntity : public AgeableMobEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AgeableMobEntity::metadata_count + AgeableMobEntity::hierarchy_metadata_count;

    public:
        AnimalEntity();
        virtual ~AnimalEntity();

        virtual bool IsAnimal() const override;
    };
}
