#include "botcraft/Game/Entities/entities/animal/CowEntity.hpp"

namespace Botcraft
{
    CowEntity::CowEntity()
    {

    }

    CowEntity::~CowEntity()
    {

    }


    std::string CowEntity::GetName() const
    {
        return "Cow";
    }

    EntityType CowEntity::GetType() const
    {
        return EntityType::Cow;
    }

    AABB CowEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double CowEntity::GetWidth() const
    {
        return 0.9;
    }

    double CowEntity::GetHeight() const
    {
        return 1.4;
    }


    std::string CowEntity::GetClassName()
    {
        return "Cow";
    }

    EntityType CowEntity::GetClassType()
    {
        return EntityType::Cow;
    }

}
