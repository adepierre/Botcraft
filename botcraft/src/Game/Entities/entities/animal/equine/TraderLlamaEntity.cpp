#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#include "botcraft/Game/Entities/entities/animal/equine/TraderLlamaEntity.hpp"

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
        return "trader_llama";
    }

    EntityType TraderLlamaEntity::GetType() const
    {
        return EntityType::TraderLlama;
    }


    std::string TraderLlamaEntity::GetClassName()
    {
        return "trader_llama";
    }

    EntityType TraderLlamaEntity::GetClassType()
    {
        return EntityType::TraderLlama;
    }


    double TraderLlamaEntity::GetWidthImpl() const
    {
        return 0.9;
    }

    double TraderLlamaEntity::GetHeightImpl() const
    {
        return 1.87;
    }

}
#endif
