#include "botcraft/Game/Entities/Player.hpp"


namespace Botcraft
{
    Player::Player()
    {

    }

    const EntityType Player::GetType() const
    {
        return EntityType::Player;
    }

    const AABB Player::GetCollider() const
    {
        return AABB(Vector3<double>(position.x, position.y + 0.9, position.z), Vector3<double>(0.3, 0.9, 0.3));
    }
} //Botcraft