#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    /// @brief Dig a block at a given location. If too far, will try to pathfind toward it
    /// @param c The client performing the action
    /// @param pos Location of block to dig
    /// @param send_swing If true, will send swing packets to show other players digging in progress
    /// @param face Digging direction
    /// @param mining_time In seconds. If >= 0.0, will use this time instead of the computed one
    /// @return Success if the block is broken, Failure otherwise
    Status Dig(BehaviourClient& c, const Position& pos, const bool send_swing = false, const PlayerDiggingFace face = PlayerDiggingFace::Up, const float mining_time = -1.0f);
        
    /// @brief Same thing as Dig, but reads its parameters from the blackboard
    /// @param c The client performing the action
    /// @return Success if the block is broken, Failure otherwise
    Status DigBlackboard(BehaviourClient& c);
}