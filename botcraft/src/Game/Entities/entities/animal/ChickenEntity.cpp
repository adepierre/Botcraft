#include "botcraft/Game/Entities/entities/animal/ChickenEntity.hpp"

namespace Botcraft
{
    ChickenEntity::ChickenEntity()
    {

    }

    ChickenEntity::~ChickenEntity()
    {

    }


    std::string ChickenEntity::GetName() const
    {
        return "chicken";
    }

    EntityType ChickenEntity::GetType() const
    {
        return EntityType::Chicken;
    }

    double ChickenEntity::GetWidth() const
    {
        return 0.4;
    }

    double ChickenEntity::GetHeight() const
    {
        return 0.7;
    }


    std::string ChickenEntity::GetClassName()
    {
        return "chicken";
    }

    EntityType ChickenEntity::GetClassType()
    {
        return EntityType::Chicken;
    }

}
