#if PROTOCOL_VERSION > 754
#pragma once

#include "botcraft/Game/Entities/entities/decoration/ItemFrameEntity.hpp"

namespace Botcraft
{
    class GlowItemFrameEntity : public ItemFrameEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ItemFrameEntity::metadata_count + ItemFrameEntity::hierarchy_metadata_count;

    public:
        GlowItemFrameEntity();
        virtual ~GlowItemFrameEntity();

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
#endif
