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
