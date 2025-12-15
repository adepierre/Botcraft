#pragma once

#include "botcraft/Game/Entities/entities/monster/skeleton/AbstractSkeletonEntity.hpp"

namespace Botcraft
{
    class WitherSkeletonEntity : public AbstractSkeletonEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractSkeletonEntity::metadata_count + AbstractSkeletonEntity::hierarchy_metadata_count;

    public:
        WitherSkeletonEntity();
        virtual ~WitherSkeletonEntity();

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
