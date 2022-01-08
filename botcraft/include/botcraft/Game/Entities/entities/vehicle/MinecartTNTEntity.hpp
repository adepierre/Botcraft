#pragma once

#include "botcraft/Game/Entities/entities/vehicle/AbstractMinecartEntity.hpp"

namespace Botcraft
{
    class MinecartTNTEntity : public AbstractMinecartEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractMinecartEntity::metadata_count + AbstractMinecartEntity::hierarchy_metadata_count;

    public:
        MinecartTNTEntity();
        virtual ~MinecartTNTEntity();

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
