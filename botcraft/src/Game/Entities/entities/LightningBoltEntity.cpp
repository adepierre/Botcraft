#if PROTOCOL_VERSION > 340
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
        return "LightningBolt";
    }

    EntityType LightningBoltEntity::GetType() const
    {
        return EntityType::LightningBolt;
    }

    AABB LightningBoltEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
        return "LightningBolt";
    }

    EntityType LightningBoltEntity::GetClassType()
    {
        return EntityType::LightningBolt;
    }

}
#endif
