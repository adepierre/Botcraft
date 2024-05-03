#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/AbstractHurtingProjectileEntity.hpp"

namespace Botcraft
{
    class AbstractWindChargeEntity : public AbstractHurtingProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractWindChargeEntity::metadata_count + AbstractWindChargeEntity::hierarchy_metadata_count;

    public:
        AbstractWindChargeEntity();
        virtual ~AbstractWindChargeEntity();

        virtual bool IsAbstractWindCharge() const override;

    };
}
#endif
