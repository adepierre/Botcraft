#include "botcraft/Game/Entities/entities/monster/HuskEntity.hpp"

namespace Botcraft
{
    HuskEntity::HuskEntity()
    {

    }

    HuskEntity::~HuskEntity()
    {

    }


    std::string HuskEntity::GetName() const
    {
        return "Husk";
    }

    EntityType HuskEntity::GetType() const
    {
        return EntityType::Husk;
    }

    AABB HuskEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double HuskEntity::GetWidth() const
    {
        return 0.6;
    }

    double HuskEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string HuskEntity::GetClassName()
    {
        return "Husk";
    }

    EntityType HuskEntity::GetClassType()
    {
        return EntityType::Husk;
    }

}
