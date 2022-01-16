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
        return "Vindicator";
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
        return "Vindicator";
    }

    EntityType VindicatorEntity::GetClassType()
    {
        return EntityType::Vindicator;
    }

}
