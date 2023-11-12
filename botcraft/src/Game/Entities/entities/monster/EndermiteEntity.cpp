#include "botcraft/Game/Entities/entities/monster/EndermiteEntity.hpp"

namespace Botcraft
{
    EndermiteEntity::EndermiteEntity()
    {

    }

    EndermiteEntity::~EndermiteEntity()
    {

    }


    std::string EndermiteEntity::GetName() const
    {
        return "endermite";
    }

    EntityType EndermiteEntity::GetType() const
    {
        return EntityType::Endermite;
    }


    std::string EndermiteEntity::GetClassName()
    {
        return "endermite";
    }

    EntityType EndermiteEntity::GetClassType()
    {
        return EntityType::Endermite;
    }


    double EndermiteEntity::GetWidthImpl() const
    {
        return 0.4;
    }

    double EndermiteEntity::GetHeightImpl() const
    {
        return 0.3;
    }

}
