#pragma once

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/Enums.hpp"

namespace Botcraft
{
    class BehaviourClient;
    enum class Status;

    /// @brief Dig a block at a given location. If too far, will try to pathfind toward it
    /// @param c The client performing the action
    /// @param pos Location of block to dig
    /// @param send_swing If true, will send swing packets to show other players digging in progress
    /// @param face Digging direction
    /// @return Success if the block is broken, Failure otherwise
    Status Dig(BehaviourClient& c, const Position& pos, const bool send_swing = false, const PlayerDiggingFace face = PlayerDiggingFace::Up);
        
    /// @brief Same thing as Dig, but reads its parameters from the blackboard
    /// @param c The client performing the action
    /// @return Success if the block is broken, Failure otherwise
    Status DigBlackboard(BehaviourClient& c);
}