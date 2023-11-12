#pragma once

#include "botcraft/Game/Entities/entities/decoration/HangingEntity.hpp"

namespace Botcraft
{
    class LeashFenceKnotEntity : public HangingEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = HangingEntity::metadata_count + HangingEntity::hierarchy_metadata_count;

    public:
        LeashFenceKnotEntity();
        virtual ~LeashFenceKnotEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    protected:
        virtual double GetWidthImpl() const override;
        virtual double GetHeightImpl() const override;

    };
}
