#include "botcraft/Game/Entities/entities/projectile/EvokerFangsEntity.hpp"

namespace Botcraft
{
    EvokerFangsEntity::EvokerFangsEntity()
    {

    }

    EvokerFangsEntity::~EvokerFangsEntity()
    {

    }


    std::string EvokerFangsEntity::GetName() const
    {
        return "EvokerFangs";
    }

    EntityType EvokerFangsEntity::GetType() const
    {
        return EntityType::EvokerFangs;
    }

    double EvokerFangsEntity::GetWidth() const
    {
        return 0.5;
    }

    double EvokerFangsEntity::GetHeight() const
    {
        return 0.8;
    }


    std::string EvokerFangsEntity::GetClassName()
    {
        return "EvokerFangs";
    }

    EntityType EvokerFangsEntity::GetClassType()
    {
        return EntityType::EvokerFangs;
    }

}
