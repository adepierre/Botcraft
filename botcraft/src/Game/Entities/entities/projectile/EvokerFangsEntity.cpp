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


    std::string EvokerFangsEntity::GetClassName()
    {
        return "evoker_fangs";
    }

    EntityType EvokerFangsEntity::GetClassType()
    {
        return EntityType::EvokerFangs;
    }


    double EvokerFangsEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double EvokerFangsEntity::GetHeightImpl() const
    {
        return 0.8;
    }

}
