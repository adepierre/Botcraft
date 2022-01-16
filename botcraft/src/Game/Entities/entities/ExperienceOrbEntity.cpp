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
