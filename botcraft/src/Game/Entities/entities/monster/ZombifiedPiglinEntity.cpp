#if PROTOCOL_VERSION > 578
#include "botcraft/Game/Entities/entities/monster/ZombifiedPiglinEntity.hpp"

namespace Botcraft
{
    ZombifiedPiglinEntity::ZombifiedPiglinEntity()
    {

    }

    ZombifiedPiglinEntity::~ZombifiedPiglinEntity()
    {

    }


    std::string ZombifiedPiglinEntity::GetName() const
    {
        return "ZombifiedPiglin";
    }

    EntityType ZombifiedPiglinEntity::GetType() const
    {
        return EntityType::ZombifiedPiglin;
    }

    AABB ZombifiedPiglinEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double ZombifiedPiglinEntity::GetWidth() const
    {
        return 0.6;
    }

    double ZombifiedPiglinEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string ZombifiedPiglinEntity::GetClassName()
    {
        return "ZombifiedPiglin";
    }

    EntityType ZombifiedPiglinEntity::GetClassType()
    {
        return EntityType::ZombifiedPiglin;
    }

}
#endif
