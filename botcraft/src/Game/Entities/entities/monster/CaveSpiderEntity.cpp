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
        return "cave_spider";
    }

    EntityType CaveSpiderEntity::GetType() const
    {
        return EntityType::CaveSpider;
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
        return "cave_spider";
    }

    EntityType CaveSpiderEntity::GetClassType()
    {
        return EntityType::CaveSpider;
    }

}
