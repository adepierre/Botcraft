#pragma once

#include "botcraft/Game/Entities/entities/Entity.hpp"

namespace Botcraft
{
    class HangingEntity : public Entity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = Entity::metadata_count + Entity::hierarchy_metadata_count;

    public:
        HangingEntity();
        virtual ~HangingEntity();

        virtual bool IsHangingEntity() const override;
    };
}
