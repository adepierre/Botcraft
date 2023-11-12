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


    std::string GlowItemFrameEntity::GetClassName()
    {
        return "glow_item_frame";
    }

    EntityType GlowItemFrameEntity::GetClassType()
    {
        return EntityType::GlowItemFrame;
    }


    double GlowItemFrameEntity::GetWidthImpl() const
    {
        return 0.5;
    }

    double GlowItemFrameEntity::GetHeightImpl() const
    {
        return 0.5;
    }

}
#endif
