#pragma once

#include "botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrowableItemProjectileEntity.hpp"

namespace Botcraft
{
    class SnowballEntity : public ThrowableItemProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ThrowableItemProjectileEntity::metadata_count + ThrowableItemProjectileEntity::hierarchy_metadata_count;

    public:
        SnowballEntity();
        virtual ~SnowballEntity();

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
