#pragma once

#include "botcraft/Game/Entities/entities/vehicle/minecart/AbstractMinecartEntity.hpp"

namespace Botcraft
{
    class MinecartEntity : public AbstractMinecartEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractMinecartEntity::metadata_count + AbstractMinecartEntity::hierarchy_metadata_count;

    public:
        MinecartEntity();
        virtual ~MinecartEntity();

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
