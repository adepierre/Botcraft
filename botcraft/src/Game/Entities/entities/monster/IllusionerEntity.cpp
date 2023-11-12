#include "botcraft/Game/Entities/entities/monster/IllusionerEntity.hpp"

namespace Botcraft
{
    IllusionerEntity::IllusionerEntity()
    {

    }

    IllusionerEntity::~IllusionerEntity()
    {

    }


    std::string IllusionerEntity::GetName() const
    {
        return "illusioner";
    }

    EntityType IllusionerEntity::GetType() const
    {
        return EntityType::Illusioner;
    }


    std::string IllusionerEntity::GetClassName()
    {
        return "illusioner";
    }

    EntityType IllusionerEntity::GetClassType()
    {
        return EntityType::Illusioner;
    }


    double IllusionerEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double IllusionerEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
