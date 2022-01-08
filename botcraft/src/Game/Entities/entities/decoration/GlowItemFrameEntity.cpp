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

    AABB GlowItemFrameEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
