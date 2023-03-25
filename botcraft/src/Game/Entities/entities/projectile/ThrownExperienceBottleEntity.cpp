#include "botcraft/Game/Entities/entities/projectile/ThrownExperienceBottleEntity.hpp"

namespace Botcraft
{
    ThrownExperienceBottleEntity::ThrownExperienceBottleEntity()
    {

    }

    ThrownExperienceBottleEntity::~ThrownExperienceBottleEntity()
    {

    }


    std::string ThrownExperienceBottleEntity::GetName() const
    {
        return "experience_bottle";
    }

    EntityType ThrownExperienceBottleEntity::GetType() const
    {
        return EntityType::ThrownExperienceBottle;
    }

    double ThrownExperienceBottleEntity::GetWidth() const
    {
        return 0.25;
    }

    double ThrownExperienceBottleEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string ThrownExperienceBottleEntity::GetClassName()
    {
        return "experience_bottle";
    }

    EntityType ThrownExperienceBottleEntity::GetClassType()
    {
        return EntityType::ThrownExperienceBottle;
    }

}
