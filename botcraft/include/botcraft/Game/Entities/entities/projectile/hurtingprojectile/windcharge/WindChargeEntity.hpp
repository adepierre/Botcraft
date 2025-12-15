#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/AbstractHurtingProjectileEntity.hpp"
#else
#include "botcraft/Game/Entities/entities/projectile/hurtingprojectile/windcharge/AbstractWindChargeEntity.hpp"
#endif

namespace Botcraft
{
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
    class WindChargeEntity : public AbstractHurtingProjectileEntity
#else
    class WindChargeEntity : public AbstractWindChargeEntity
#endif
    {
    protected:
        static constexpr int metadata_count = 0;
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int hierarchy_metadata_count = AbstractHurtingProjectileEntity::metadata_count + AbstractHurtingProjectileEntity::hierarchy_metadata_count;
#else
        static constexpr int hierarchy_metadata_count = AbstractWindChargeEntity::metadata_count + AbstractWindChargeEntity::hierarchy_metadata_count;
#endif

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
