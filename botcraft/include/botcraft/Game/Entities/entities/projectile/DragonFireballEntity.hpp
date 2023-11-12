#pragma once

#include "botcraft/Game/Entities/entities/projectile/AbstractHurtingProjectileEntity.hpp"

namespace Botcraft
{
    class DragonFireballEntity : public AbstractHurtingProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractHurtingProjectileEntity::metadata_count + AbstractHurtingProjectileEntity::hierarchy_metadata_count;

    public:
        DragonFireballEntity();
        virtual ~DragonFireballEntity();

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
