#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/npc/WanderingTraderEntity.hpp"

namespace Botcraft
{
    WanderingTraderEntity::WanderingTraderEntity()
    {

    }

    WanderingTraderEntity::~WanderingTraderEntity()
    {

    }


    std::string WanderingTraderEntity::GetName() const
    {
        return "WanderingTrader";
    }

    EntityType WanderingTraderEntity::GetType() const
    {
        return EntityType::WanderingTrader;
    }

    AABB WanderingTraderEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double WanderingTraderEntity::GetWidth() const
    {
        return 0.6;
    }

    double WanderingTraderEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string WanderingTraderEntity::GetClassName()
    {
        return "WanderingTrader";
    }

    EntityType WanderingTraderEntity::GetClassType()
    {
        return EntityType::WanderingTrader;
    }

}
#endif
