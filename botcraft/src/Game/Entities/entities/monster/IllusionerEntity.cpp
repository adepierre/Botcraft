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

    AABB IllusionerEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
