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

    AABB LlamaSpitEntity::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + GetHeight() / 2.0, position.z), Vector3<double>(GetWidth() / 2.0, GetHeight() / 2.0, GetWidth() / 2.0));
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
