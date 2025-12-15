#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include "botcraft/Game/Entities/entities/projectile/throwableitemprojectile/ThrownLingeringPotionEntity.hpp"

namespace Botcraft
{
    ThrownLingeringPotionEntity::ThrownLingeringPotionEntity()
    {

    }

    ThrownLingeringPotionEntity::~ThrownLingeringPotionEntity()
    {

    }


    std::string ThrownLingeringPotionEntity::GetName() const
    {
        return "thrown_lingering_potion";
    }

    EntityType ThrownLingeringPotionEntity::GetType() const
    {
        return EntityType::ThrownLingeringPotion;
    }


    std::string ThrownLingeringPotionEntity::GetClassName()
    {
        return "thrown_lingering_potion";
    }

    EntityType ThrownLingeringPotionEntity::GetClassType()
    {
        return EntityType::ThrownLingeringPotion;
    }


    double ThrownLingeringPotionEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double ThrownLingeringPotionEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
#endif
