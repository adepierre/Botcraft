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
        return "husk";
    }

    EntityType HuskEntity::GetType() const
    {
        return EntityType::Husk;
    }


    std::string HuskEntity::GetClassName()
    {
        return "husk";
    }

    EntityType HuskEntity::GetClassType()
    {
        return EntityType::Husk;
    }


    double HuskEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double HuskEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
