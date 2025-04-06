#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "botcraft/Game/Entities/entities/projectile/AbstractThrownPotionEntity.hpp"

namespace Botcraft
{
    class ThrownSplashPotionEntity : public AbstractThrownPotionEntity
    {
    protected:
        static constexpr int metadata_count = 0;
        static constexpr int hierarchy_metadata_count = AbstractThrownPotionEntity::metadata_count + AbstractThrownPotionEntity::hierarchy_metadata_count;

    public:
        ThrownSplashPotionEntity();
        virtual ~ThrownSplashPotionEntity();

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
