#pragma once

#include "botcraft/Game/Entities/entities/projectile/ThrowableItemProjectileEntity.hpp"

namespace Botcraft
{
    class ThrownExperienceBottleEntity : public ThrowableItemProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ThrowableItemProjectileEntity::metadata_count + ThrowableItemProjectileEntity::hierarchy_metadata_count;

    public:
        ThrownExperienceBottleEntity();
        virtual ~ThrownExperienceBottleEntity();

        // Object related stuff
        virtual std::string GetName() const override;
        virtual EntityType GetType() const override;
        virtual double GetWidth() const override;
        virtual double GetHeight() const override;

        // Static stuff, for easier comparison
        static std::string GetClassName();
        static EntityType GetClassType();

    };
}
