#include "botcraft/Game/Entities/entities/monster/GiantEntity.hpp"

namespace Botcraft
{
    GiantEntity::GiantEntity()
    {

    }

    GiantEntity::~GiantEntity()
    {

    }


    std::string GiantEntity::GetName() const
    {
        return "giant";
    }

    EntityType GiantEntity::GetType() const
    {
        return EntityType::Giant;
    }


    std::string GiantEntity::GetClassName()
    {
        return "giant";
    }

    EntityType GiantEntity::GetClassType()
    {
        return EntityType::Giant;
    }


    double GiantEntity::GetWidthImpl() const
    {
        return 3.6;
    }

    double GiantEntity::GetHeightImpl() const
    {
        return 12.0;
    }

}
