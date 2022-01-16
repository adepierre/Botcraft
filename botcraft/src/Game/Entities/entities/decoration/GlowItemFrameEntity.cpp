#if PROTOCOL_VERSION > 754
#include "botcraft/Game/Entities/entities/decoration/GlowItemFrameEntity.hpp"

namespace Botcraft
{
    GlowItemFrameEntity::GlowItemFrameEntity()
    {

    }

    GlowItemFrameEntity::~GlowItemFrameEntity()
    {

    }


    std::string GlowItemFrameEntity::GetName() const
    {
        return "GlowItemFrame";
    }

    EntityType GlowItemFrameEntity::GetType() const
    {
        return EntityType::GlowItemFrame;
    }

    double GlowItemFrameEntity::GetWidth() const
    {
        return 0.5;
    }

    double GlowItemFrameEntity::GetHeight() const
    {
        return 0.5;
    }


    std::string GlowItemFrameEntity::GetClassName()
    {
        return "GlowItemFrame";
    }

    EntityType GlowItemFrameEntity::GetClassType()
    {
        return EntityType::GlowItemFrame;
    }

}
#endif
