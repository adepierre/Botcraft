#include "botcraft/Game/Entities/entities/monster/EvokerEntity.hpp"

namespace Botcraft
{
    EvokerEntity::EvokerEntity()
    {

    }

    EvokerEntity::~EvokerEntity()
    {

    }


    std::string EvokerEntity::GetName() const
    {
        return "Evoker";
    }

    EntityType EvokerEntity::GetType() const
    {
        return EntityType::Evoker;
    }

    double EvokerEntity::GetWidth() const
    {
        return 0.6;
    }

    double EvokerEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string EvokerEntity::GetClassName()
    {
        return "Evoker";
    }

    EntityType EvokerEntity::GetClassType()
    {
        return EntityType::Evoker;
    }

}
