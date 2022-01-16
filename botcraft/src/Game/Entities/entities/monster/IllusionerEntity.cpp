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
        return "Illusioner";
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
        return "Illusioner";
    }

    EntityType IllusionerEntity::GetClassType()
    {
        return EntityType::Illusioner;
    }

}
