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

    double EndermiteEntity::GetWidth() const
    {
        return 0.4;
    }

    double EndermiteEntity::GetHeight() const
    {
        return 0.3;
    }


    std::string EndermiteEntity::GetClassName()
    {
        return "endermite";
    }

    EntityType EndermiteEntity::GetClassType()
    {
        return EntityType::Endermite;
    }

}
