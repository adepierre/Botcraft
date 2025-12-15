#include "botcraft/Game/Entities/entities/monster/spider/CaveSpiderEntity.hpp"

namespace Botcraft
{
    CaveSpiderEntity::CaveSpiderEntity()
    {
        // Initialize all attributes with default values
        attributes.insert({ EntityAttribute::Type::MaxHealth, EntityAttribute(EntityAttribute::Type::MaxHealth, 12.0) });
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


    std::string CaveSpiderEntity::GetClassName()
    {
        return "cave_spider";
    }

    EntityType CaveSpiderEntity::GetClassType()
    {
        return EntityType::CaveSpider;
    }


    double CaveSpiderEntity::GetWidthImpl() const
    {
        return 0.7;
    }

    double CaveSpiderEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
