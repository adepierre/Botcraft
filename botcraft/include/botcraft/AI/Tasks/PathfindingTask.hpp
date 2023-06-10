#pragma once

#include "botcraft/AI/Status.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    class BehaviourClient;

    /// @brief Find a path to a position and navigate to it.
    /// @param client The client performing the action
    /// @param goal The end goal
    /// @param dist_tolerance If != 0 and the distance between final position and goal is < dist_tolerance, return Success even if goal is not reached
    /// @param min_end_dist Desired minimal distance between the final position and goal (useful if you want to place a block, you don't want to be at the exact spot, but close to it)
    /// @param speed Travel speed (block per s)
    /// @param allow_jump If true, allow to jump above 1-wide gaps
    /// @return Success if goal is reached, Failure otherwise
    Status GoTo(BehaviourClient& client, const Position& goal, const int dist_tolerance = 0, const int min_end_dist = 0, const float speed = 4.317f, const bool allow_jump = true);

    /// @brief Same thing as GoTo, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if goal is reached, Failure otherwise
    Status GoToBlackboard(BehaviourClient& client);


    /// @brief Turn the camera to look at a given target, and wait at least one tick so the server register it
    /// @param client The client performing the action
    /// @param target The target to look at
    /// @param set_pitch If false, only the yaw will be changed
    /// @return Always return Success
    Status LookAt(BehaviourClient& client, const Vector3<double>& target, const bool set_pitch = true);

    /// @brief Same thing as LookAt, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status LookAtBlackboard(BehaviourClient& client);

} // namespace Botcraft
