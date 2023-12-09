#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/AbstractHurtingProjectileEntity.hpp"

namespace Botcraft
{
    class WindChargeEntity : public AbstractHurtingProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractHurtingProjectileEntity::metadata_count + AbstractHurtingProjectileEntity::hierarchy_metadata_count;

    public:
        WindChargeEntity();
        virtual ~WindChargeEntity();

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
#endif
