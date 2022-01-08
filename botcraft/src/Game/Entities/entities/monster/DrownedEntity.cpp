#if PROTOCOL_VERSION > 340
#include "botcraft/Game/Entities/entities/monster/DrownedEntity.hpp"

namespace Botcraft
{
    DrownedEntity::DrownedEntity()
    {

    }

    DrownedEntity::~DrownedEntity()
    {

    }


    std::string DrownedEntity::GetName() const
    {
        return "Drowned";
    }

    EntityType DrownedEntity::GetType() const
    {
        return EntityType::Drowned;
    }

    AABB DrownedEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double DrownedEntity::GetWidth() const
    {
        return 0.6;
    }

    double DrownedEntity::GetHeight() const
    {
        return 1.95;
    }


    std::string DrownedEntity::GetClassName()
    {
        return "Drowned";
    }

    EntityType DrownedEntity::GetClassType()
    {
        return EntityType::Drowned;
    }

}
#endif
