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
        return "evoker_fangs";
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
        return "evoker_fangs";
    }

    EntityType EvokerFangsEntity::GetClassType()
    {
        return EntityType::EvokerFangs;
    }

}
