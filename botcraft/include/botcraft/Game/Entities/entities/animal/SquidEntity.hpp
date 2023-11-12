#pragma once

#include "botcraft/Game/Entities/entities/animal/WaterAnimalEntity.hpp"

namespace Botcraft
{
    class SquidEntity : public WaterAnimalEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = WaterAnimalEntity::metadata_count + WaterAnimalEntity::hierarchy_metadata_count;

    public:
        SquidEntity();
        virtual ~SquidEntity();

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
