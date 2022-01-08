#include "botcraft/Game/Entities/entities/monster/SilverfishEntity.hpp"

namespace Botcraft
{
    SilverfishEntity::SilverfishEntity()
    {

    }

    SilverfishEntity::~SilverfishEntity()
    {

    }


    std::string SilverfishEntity::GetName() const
    {
        return "Silverfish";
    }

    EntityType SilverfishEntity::GetType() const
    {
        return EntityType::Silverfish;
    }

    AABB SilverfishEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SilverfishEntity::GetWidth() const
    {
        return 0.4;
    }

    double SilverfishEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string SilverfishEntity::GetClassName()
    {
        return "Silverfish";
    }

    EntityType SilverfishEntity::GetClassType()
    {
        return EntityType::Silverfish;
    }

}
