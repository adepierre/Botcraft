#include "botcraft/Game/Entities/entities/decoration/LeashFenceKnotEntity.hpp"

namespace Botcraft
{
    LeashFenceKnotEntity::LeashFenceKnotEntity()
    {

    }

    LeashFenceKnotEntity::~LeashFenceKnotEntity()
    {

    }


    std::string LeashFenceKnotEntity::GetName() const
    {
        return "LeashFenceKnotEntity";
    }

    EntityType LeashFenceKnotEntity::GetType() const
    {
        return EntityType::LeashFenceKnotEntity;
    }

    double LeashFenceKnotEntity::GetWidth() const
    {
#if PROTOCOL_VERSION > 754
        return 0.375;
#else
        return 0.5;
#endif
    }

    double LeashFenceKnotEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string LeashFenceKnotEntity::GetClassName()
    {
        return "LeashFenceKnotEntity";
    }

    EntityType LeashFenceKnotEntity::GetClassType()
    {
        return EntityType::LeashFenceKnotEntity;
    }

}
