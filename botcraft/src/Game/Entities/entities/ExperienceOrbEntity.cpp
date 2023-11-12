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
        return "experience_orb";
    }

    EntityType ExperienceOrbEntity::GetType() const
    {
        return EntityType::ExperienceOrb;
    }


    std::string ExperienceOrbEntity::GetClassName()
    {
        return "experience_orb";
    }

    EntityType ExperienceOrbEntity::GetClassType()
    {
        return EntityType::ExperienceOrb;
    }


    double ExperienceOrbEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double ExperienceOrbEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
