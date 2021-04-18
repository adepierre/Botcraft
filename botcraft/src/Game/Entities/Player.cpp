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
} //Botcraft