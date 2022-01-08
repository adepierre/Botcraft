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
        return "ElderGuardian";
    }

    EntityType ElderGuardianEntity::GetType() const
    {
        return EntityType::ElderGuardian;
    }

    AABB ElderGuardianEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "ElderGuardian";
    }

    EntityType ElderGuardianEntity::GetClassType()
    {
        return EntityType::ElderGuardian;
    }

}
