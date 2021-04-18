#pragma once

#include <mutex>

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/AABB.hpp"
#include "botcraft/Game/Entities/Entity.hpp"

namespace Botcraft 
{
    class Player : public Entity
    {
    public:
        Player();

        virtual const EntityType GetType() const override;
        virtual const AABB GetCollider() const override;
    };
} // Botcraft