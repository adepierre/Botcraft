#include "botcraft/Game/Entities/entities/monster/EndermiteEntity.hpp"

namespace Botcraft
{
    EndermiteEntity::EndermiteEntity()
    {

    }

    EndermiteEntity::~EndermiteEntity()
    {

    }


    std::string EndermiteEntity::GetName() const
    {
        return "Endermite";
    }

    EntityType EndermiteEntity::GetType() const
    {
        return EntityType::Endermite;
    }

    AABB EndermiteEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double EndermiteEntity::GetWidth() const
    {
        return 0.4;
    }

    double EndermiteEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string EndermiteEntity::GetClassName()
    {
        return "Endermite";
    }

    EntityType EndermiteEntity::GetClassType()
    {
        return EntityType::Endermite;
    }

}
