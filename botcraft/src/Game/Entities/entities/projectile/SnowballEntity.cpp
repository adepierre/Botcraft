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

    double SnowballEntity::GetWidth() const
    {
        return 0.25;
    }

    double SnowballEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string SnowballEntity::GetClassName()
    {
        return "snowball";
    }

    EntityType SnowballEntity::GetClassType()
    {
        return EntityType::Snowball;
    }

}
