#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/animal/CodEntity.hpp"

namespace Botcraft
{
    CodEntity::CodEntity()
    {

    }

    CodEntity::~CodEntity()
    {

    }


    std::string CodEntity::GetName() const
    {
        return "Cod";
    }

    EntityType CodEntity::GetType() const
    {
        return EntityType::Cod;
    }

    AABB CodEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double CodEntity::GetWidth() const
    {
        return 0.5;
    }

    double CodEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string CodEntity::GetClassName()
    {
        return "Cod";
    }

    EntityType CodEntity::GetClassType()
    {
        return EntityType::Cod;
    }

}
#endif
