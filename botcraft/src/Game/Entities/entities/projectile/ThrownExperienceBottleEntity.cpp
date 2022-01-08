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
        return "ThrownExperienceBottle";
    }

    EntityType ThrownExperienceBottleEntity::GetType() const
    {
        return EntityType::ThrownExperienceBottle;
    }

    AABB ThrownExperienceBottleEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "ThrownExperienceBottle";
    }

    EntityType ThrownExperienceBottleEntity::GetClassType()
    {
        return EntityType::ThrownExperienceBottle;
    }

}
