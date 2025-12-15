#include "botcraft/Game/Entities/entities/monster/skeleton/StrayEntity.hpp"

namespace Botcraft
{
    StrayEntity::StrayEntity()
    {

    }

    StrayEntity::~StrayEntity()
    {

    }


    std::string StrayEntity::GetName() const
    {
        return "stray";
    }

    EntityType StrayEntity::GetType() const
    {
        return EntityType::Stray;
    }


    std::string StrayEntity::GetClassName()
    {
        return "stray";
    }

    EntityType StrayEntity::GetClassType()
    {
        return EntityType::Stray;
    }


    double StrayEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double StrayEntity::GetHeightImpl() const
    {
        return 1.99;
    }

}
