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
        return "leash_knot";
    }

    EntityType LeashFenceKnotEntity::GetType() const
    {
        return EntityType::LeashFenceKnotEntity;
    }


    std::string LeashFenceKnotEntity::GetClassName()
    {
        return "leash_knot";
    }

    EntityType LeashFenceKnotEntity::GetClassType()
    {
        return EntityType::LeashFenceKnotEntity;
    }


    double LeashFenceKnotEntity::GetWidthImpl() const
    {
#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        return 0.375;
#else
        return 0.5;
#endif
    }

    double LeashFenceKnotEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
