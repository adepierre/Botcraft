#include "botcraft/Game/Entities/entities/projectile/LlamaSpitEntity.hpp"

namespace Botcraft
{
    LlamaSpitEntity::LlamaSpitEntity()
    {

    }

    LlamaSpitEntity::~LlamaSpitEntity()
    {

    }


    std::string LlamaSpitEntity::GetName() const
    {
        return "llama_spit";
    }

    EntityType LlamaSpitEntity::GetType() const
    {
        return EntityType::LlamaSpit;
    }


    std::string LlamaSpitEntity::GetClassName()
    {
        return "llama_spit";
    }

    EntityType LlamaSpitEntity::GetClassType()
    {
        return EntityType::LlamaSpit;
    }


    double LlamaSpitEntity::GetWidthImpl() const
    {
        return 0.25;
    }

    double LlamaSpitEntity::GetHeightImpl() const
    {
        return 0.25;
    }

}
