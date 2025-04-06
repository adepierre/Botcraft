#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/ThrowableItemProjectileEntity.hpp"


namespace Botcraft
{
    class AbstractThrownPotionEntity : public ThrowableItemProjectileEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = ThrowableItemProjectileEntity::metadata_count + ThrowableItemProjectileEntity::hierarchy_metadata_count;


    public:
        AbstractThrownPotionEntity();
        virtual ~AbstractThrownPotionEntity();

        virtual bool IsAbstractThrownPotion() const override;
    };
}
#endif
