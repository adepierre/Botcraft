#include "botcraft/Game/Entities/entities/monster/VindicatorEntity.hpp"

namespace Botcraft
{
    VindicatorEntity::VindicatorEntity()
    {

    }

    VindicatorEntity::~VindicatorEntity()
    {

    }


    std::string VindicatorEntity::GetName() const
    {
        return "vindicator";
    }

    EntityType VindicatorEntity::GetType() const
    {
        return EntityType::Vindicator;
    }

    double VindicatorEntity::GetWidth() const
    {
        return 0.6;
    }

    double VindicatorEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string VindicatorEntity::GetClassName()
    {
        return "vindicator";
    }

    EntityType VindicatorEntity::GetClassType()
    {
        return EntityType::Vindicator;
    }

}
