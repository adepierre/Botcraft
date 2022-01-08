#include "botcraft/Game/Entities/entities/animal/SquidEntity.hpp"

namespace Botcraft
{
    SquidEntity::SquidEntity()
    {

    }

    SquidEntity::~SquidEntity()
    {

    }


    std::string SquidEntity::GetName() const
    {
        return "Squid";
    }

    EntityType SquidEntity::GetType() const
    {
        return EntityType::Squid;
    }

    AABB SquidEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SquidEntity::GetWidth() const
    {
        return 0.8;
    }

    double SquidEntity::GetHeight() const
    {
        return 0.8;
    }


    std::string SquidEntity::GetClassName()
    {
        return "Squid";
    }

    EntityType SquidEntity::GetClassType()
    {
        return EntityType::Squid;
    }

}
