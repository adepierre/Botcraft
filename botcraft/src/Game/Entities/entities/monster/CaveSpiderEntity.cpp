#include "botcraft/Game/Entities/entities/monster/CaveSpiderEntity.hpp"

namespace Botcraft
{
    CaveSpiderEntity::CaveSpiderEntity()
    {

    }

    CaveSpiderEntity::~CaveSpiderEntity()
    {

    }


    std::string CaveSpiderEntity::GetName() const
    {
        return "CaveSpider";
    }

    EntityType CaveSpiderEntity::GetType() const
    {
        return EntityType::CaveSpider;
    }

    AABB CaveSpiderEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double CaveSpiderEntity::GetWidth() const
    {
        return 0.7;
    }

    double CaveSpiderEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string CaveSpiderEntity::GetClassName()
    {
        return "CaveSpider";
    }

    EntityType CaveSpiderEntity::GetClassType()
    {
        return EntityType::CaveSpider;
    }

}
