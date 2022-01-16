#include "botcraft/Game/Entities/entities/monster/HuskEntity.hpp"

namespace Botcraft
{
    HuskEntity::HuskEntity()
    {

    }

    HuskEntity::~HuskEntity()
    {

    }


    std::string HuskEntity::GetName() const
    {
        return "Husk";
    }

    EntityType HuskEntity::GetType() const
    {
        return EntityType::Husk;
    }

    double HuskEntity::GetWidth() const
    {
        return 0.6;
    }

    double HuskEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string HuskEntity::GetClassName()
    {
        return "Husk";
    }

    EntityType HuskEntity::GetClassType()
    {
        return EntityType::Husk;
    }

}
