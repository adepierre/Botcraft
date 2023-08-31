#if PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
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
        return "glow_item_frame";
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
        return "glow_item_frame";
    }

    EntityType GlowItemFrameEntity::GetClassType()
    {
        return EntityType::GlowItemFrame;
    }

}
#endif
