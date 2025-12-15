#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/npc/wanderingtrader/WanderingTraderEntity.hpp"

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
        return "wandering_trader";
    }

    EntityType WanderingTraderEntity::GetType() const
    {
        return EntityType::WanderingTrader;
    }


    std::string WanderingTraderEntity::GetClassName()
    {
        return "wandering_trader";
    }

    EntityType WanderingTraderEntity::GetClassType()
    {
        return EntityType::WanderingTrader;
    }


    double WanderingTraderEntity::GetWidthImpl() const
    {
        return 0.6;
    }

    double WanderingTraderEntity::GetHeightImpl() const
    {
        return 1.95;
    }

}
#endif
