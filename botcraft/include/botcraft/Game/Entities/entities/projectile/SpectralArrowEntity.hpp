#pragma once

#include "botcraft/Game/Entities/entities/projectile/AbstractArrowEntity.hpp"

namespace Botcraft
{
    class SpectralArrowEntity : public AbstractArrowEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractArrowEntity::metadata_count + AbstractArrowEntity::hierarchy_metadata_count;

    public:
        SpectralArrowEntity();
        virtual ~SpectralArrowEntity();

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
