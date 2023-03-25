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

    double IllusionerEntity::GetWidth() const
    {
        return 0.6;
    }

    double IllusionerEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string IllusionerEntity::GetClassName()
    {
        return "illusioner";
    }

    EntityType IllusionerEntity::GetClassType()
    {
        return EntityType::Illusioner;
    }

}
