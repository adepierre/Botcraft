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
        return "Chicken";
    }

    EntityType ChickenEntity::GetType() const
    {
        return EntityType::Chicken;
    }

    AABB ChickenEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "Chicken";
    }

    EntityType ChickenEntity::GetClassType()
    {
        return EntityType::Chicken;
    }

}
