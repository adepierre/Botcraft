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
        return "LlamaSpit";
    }

    EntityType LlamaSpitEntity::GetType() const
    {
        return EntityType::LlamaSpit;
    }

    double LlamaSpitEntity::GetWidth() const
    {
        return 0.25;
    }

    double LlamaSpitEntity::GetHeight() const
    {
        return 0.25;
    }


    std::string LlamaSpitEntity::GetClassName()
    {
        return "LlamaSpit";
    }

    EntityType LlamaSpitEntity::GetClassType()
    {
        return EntityType::LlamaSpit;
    }

}
