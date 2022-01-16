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
