#include "botcraft/Game/Entities/entities/projectile/SnowballEntity.hpp"

namespace Botcraft
{
    SnowballEntity::SnowballEntity()
    {

    }

    SnowballEntity::~SnowballEntity()
    {

    }


    std::string SnowballEntity::GetName() const
    {
        return "snowball";
    }

    EntityType SnowballEntity::GetType() const
    {
        return EntityType::Snowball;
    }


    std::string SnowballEntity::GetClassName()
    {
        return "snowball";
    }

    EntityType SnowballEntity::GetClassType()
    {
        return EntityType::Snowball;
    }


    double SnowballEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double SnowballEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
