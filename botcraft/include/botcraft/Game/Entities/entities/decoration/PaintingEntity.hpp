#pragma once

#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"

namespace Botcraft
{
    class PaintingEntity : public HangingEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = HangingEntity::metadata_count + HangingEntity::hierarchy_metadata_count;

    public:
        PaintingEntity();
        virtual ~PaintingEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual AABB GetCollider() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}
