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
        return "Giant";
    }

    EntityType GiantEntity::GetType() const
    {
        return EntityType::Giant;
    }

    AABB GiantEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double GiantEntity::GetWidth() const
    {
        return 3.6;
    }

    double GiantEntity::GetHeight() const
    {
        return 12.0;
    }


    std::string GiantEntity::GetClassName()
    {
        return "Giant";
    }

    EntityType GiantEntity::GetClassType()
    {
        return EntityType::Giant;
    }

}
