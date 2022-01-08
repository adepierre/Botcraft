#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/monster/RavagerEntity.hpp"

namespace Botcraft
{
    RavagerEntity::RavagerEntity()
    {

    }

    RavagerEntity::~RavagerEntity()
    {

    }


    std::string RavagerEntity::GetName() const
    {
        return "Ravager";
    }

    EntityType RavagerEntity::GetType() const
    {
        return EntityType::Ravager;
    }

    AABB RavagerEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double RavagerEntity::GetWidth() const
    {
        return 1.95;
    }

    double RavagerEntity::GetHeight() const
    {
        return 2.2;
    }


    std::string RavagerEntity::GetClassName()
    {
        return "Ravager";
    }

    EntityType RavagerEntity::GetClassType()
    {
        return EntityType::Ravager;
    }

}
#endif
