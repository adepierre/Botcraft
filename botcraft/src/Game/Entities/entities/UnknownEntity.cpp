#include "botcraft/Game/Entities/entities/UnknownEntity.hpp"

namespace Botcraft
{
    UnknownEntity::UnknownEntity()
    {

    }

    UnknownEntity::~UnknownEntity()
    {

    }

    std::string UnknownEntity::GetName() const
    {
        return "";
    }

    EntityType UnknownEntity::GetType() const
    {
        return EntityType::None;
    }

    AABB UnknownEntity::GetCollider() const
    {
        return AABB(position, Vector3<double>(0.5, 0.5, 0.5));
    }
}
