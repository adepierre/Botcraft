#if PROTOCOL_VERSION > 404
#include "botcraft/Game/Entities/entities/animal/horse/TraderLlamaEntity.hpp"

namespace Botcraft
{
    TraderLlamaEntity::TraderLlamaEntity()
    {

    }

    TraderLlamaEntity::~TraderLlamaEntity()
    {

    }


    std::string TraderLlamaEntity::GetName() const
    {
        return "TraderLlama";
    }

    EntityType TraderLlamaEntity::GetType() const
    {
        return EntityType::TraderLlama;
    }

    AABB TraderLlamaEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
    }

    double TraderLlamaEntity::GetWidth() const
    {
        return 0.9;
    }

    double TraderLlamaEntity::GetHeight() const
    {
        return 1.87;
    }


    std::string TraderLlamaEntity::GetClassName()
    {
        return "TraderLlama";
    }

    EntityType TraderLlamaEntity::GetClassType()
    {
        return EntityType::TraderLlama;
    }

}
#endif
