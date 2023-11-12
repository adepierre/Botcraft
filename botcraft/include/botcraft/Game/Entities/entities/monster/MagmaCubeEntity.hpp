#pragma once

#include "botcraft/Game/Entities/entities/monster/SlimeEntity.hpp"

namespace Botcraft
{
    class MagmaCubeEntity : public SlimeEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = SlimeEntity::metadata_count + SlimeEntity::hierarchy_metadata_count;

    public:
        MagmaCubeEntity();
        virtual ~MagmaCubeEntity();

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
