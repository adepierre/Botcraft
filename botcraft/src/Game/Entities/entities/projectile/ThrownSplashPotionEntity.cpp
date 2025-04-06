#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "botcraft/Game/Entities/entities/projectile/ThrownSplashPotionEntity.hpp"

namespace Botcraft
{
    ThrownSplashPotionEntity::ThrownSplashPotionEntity()
    {

    }

    ThrownSplashPotionEntity::~ThrownSplashPotionEntity()
    {

    }


    std::string ThrownSplashPotionEntity::GetName() const
    {
        return "thrown_splash_potion";
    }

    EntityType ThrownSplashPotionEntity::GetType() const
    {
        return EntityType::ThrownSplashPotion;
    }


    std::string ThrownSplashPotionEntity::GetClassName()
    {
        return "thrown_splash_potion";
    }

    EntityType ThrownSplashPotionEntity::GetClassType()
    {
        return EntityType::ThrownSplashPotion;
    }


    double ThrownSplashPotionEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownSplashPotionEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
#endif
