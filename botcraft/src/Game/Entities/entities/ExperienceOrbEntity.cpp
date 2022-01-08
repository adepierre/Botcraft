#include "botcraft/Game/Entities/entities/ExperienceOrbEntity.hpp"

namespace Botcraft
{
    ExperienceOrbEntity::ExperienceOrbEntity()
    {

    }

    ExperienceOrbEntity::~ExperienceOrbEntity()
    {

    }


    std::string ExperienceOrbEntity::GetName() const
    {
        return "ExperienceOrb";
    }

    EntityType ExperienceOrbEntity::GetType() const
    {
        return EntityType::ExperienceOrb;
    }

    AABB ExperienceOrbEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ExperienceOrbEntity::GetWidth() const
    {
        return 0.5;
    }

    double ExperienceOrbEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string ExperienceOrbEntity::GetClassName()
    {
        return "ExperienceOrb";
    }

    EntityType ExperienceOrbEntity::GetClassType()
    {
        return EntityType::ExperienceOrb;
    }

}
