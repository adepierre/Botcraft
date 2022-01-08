#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/SalmonEntity.hpp"

namespace Botcraft
{
    SalmonEntity::SalmonEntity()
    {

    }

    SalmonEntity::~SalmonEntity()
    {

    }


    std::string SalmonEntity::GetName() const
    {
        return "Salmon";
    }

    EntityType SalmonEntity::GetType() const
    {
        return EntityType::Salmon;
    }

    AABB SalmonEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double SalmonEntity::GetWidth() const
    {
        return 0.7;
    }

    double SalmonEntity::GetHeight() const
    {
        return 0.4;
    }


    std::string SalmonEntity::GetClassName()
    {
        return "Salmon";
    }

    EntityType SalmonEntity::GetClassType()
    {
        return EntityType::Salmon;
    }

}
#endif
