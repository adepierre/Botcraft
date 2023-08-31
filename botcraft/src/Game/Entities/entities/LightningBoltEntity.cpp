#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#include "botcraft/Game/Entities/entities/LightningBoltEntity.hpp"

namespace Botcraft
{
    LightningBoltEntity::LightningBoltEntity()
    {

    }

    LightningBoltEntity::~LightningBoltEntity()
    {

    }


    std::string LightningBoltEntity::GetName() const
    {
        return "lightning_bolt";
    }

    EntityType LightningBoltEntity::GetType() const
    {
        return EntityType::LightningBolt;
    }

    double LightningBoltEntity::GetWidth() const
    {
        return 0.0;
    }

    double LightningBoltEntity::GetHeight() const
    {
        return 0.0;
    }


    std::string LightningBoltEntity::GetClassName()
    {
        return "lightning_bolt";
    }

    EntityType LightningBoltEntity::GetClassType()
    {
        return EntityType::LightningBolt;
    }

}
#endif
