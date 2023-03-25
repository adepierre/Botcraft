#include "botcraft/Game/Entities/entities/monster/ElderGuardianEntity.hpp"

namespace Botcraft
{
    ElderGuardianEntity::ElderGuardianEntity()
    {

    }

    ElderGuardianEntity::~ElderGuardianEntity()
    {

    }


    std::string ElderGuardianEntity::GetName() const
    {
        return "elder_guardian";
    }

    EntityType ElderGuardianEntity::GetType() const
    {
        return EntityType::ElderGuardian;
    }

    double ElderGuardianEntity::GetWidth() const
    {
        return 1.9975;
    }

    double ElderGuardianEntity::GetHeight() const
    {
        return 1.9975;
    }


    std::string ElderGuardianEntity::GetClassName()
    {
        return "elder_guardian";
    }

    EntityType ElderGuardianEntity::GetClassType()
    {
        return EntityType::ElderGuardian;
    }

}
