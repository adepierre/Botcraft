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
        return "evoker";
    }

    EntityType EvokerEntity::GetType() const
    {
        return EntityType::Evoker;
    }


    std::string EvokerEntity::GetClassName()
    {
        return "evoker";
    }

    EntityType EvokerEntity::GetClassType()
    {
        return EntityType::Evoker;
    }


    double EvokerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double EvokerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
