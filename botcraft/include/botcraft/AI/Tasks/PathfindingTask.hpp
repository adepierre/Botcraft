#pragma once

#include "botcraft/AI/Status.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    class BehaviourClient;

    /// @brief Not actually a task. Helper function to compute path between start and end. Does not perfom any movement.
    /// @param client Client used to do the pathfinding
    /// @param start Start position
    /// @param end End position
    /// @param dist_tolerance Stop the search earlier if you get closer than dist_tolerance from the end position
    /// @param min_end_dist Desired minimal checkboard distance between the final position and goal (useful if you want to place a block, you don't want to be at the exact spot, but close to it).
    /// @param min_end_dist_xz Same as min_end_dist but only considering the XZ plane (allows to ask to stand next to a block, but above for example)
    /// @param allow_jump If true, allow to jump above 1-wide gaps
    /// @return A vector of <feet block position, Y position> to go through to reach end +/- min_end_dist. If not possible, will return a path to get as close as possible
    std::vector<std::pair<Position, float>> FindPath(const BehaviourClient& client, const Position& start, const Position& end, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const bool allow_jump);

    /// @brief Find a path to a block position and navigate to it.
    /// @param client The client performing the action
    /// @param goal The end goal
    /// @param dist_tolerance If != 0 and the distance between final position and goal is < dist_tolerance, return Success even if goal is not reached.
    /// @param min_end_dist Desired minimal checkboard distance between the final position and goal (useful if you want to place a block, you don't want to be at the exact spot, but close to it). Should always be <= dist_tolerance.
    /// @param min_end_dist_xz Same as min_end_dist but only considering the XZ plane (allows to ask to stand next to a block, but above for example)
    /// @param allow_jump If true, allow to jump above 1-wide gaps
    /// @param sprint If true, the bot will sprint/swim when possible
    /// @param speed_factor Multiply vanilla speed if different from 1.0
    /// @return Success if goal is reached, Failure otherwise
    Status GoTo(BehaviourClient& client, const Position& goal, const int dist_tolerance = 0, const int min_end_dist = 0, const int min_end_dist_xz = 0, const bool allow_jump = true, const bool sprint = true, const float speed_factor = 1.0f);

    /// @brief Same thing as GoTo, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if goal is reached, Failure otherwise
    Status GoToBlackboard(BehaviourClient& client);


    /// @brief Find a path to a position and navigate to it. Will first move to block center, then adjust to be as close as possible to goal on X/Z axis. Gravity may prevent reaching Y target.
    /// @param client The client performing the action
    /// @param goal The end goal
    /// @param allow_jump If true, allow to jump above 1-wide gaps
    /// @param sprint If true, the bot will sprint/swim when possible
    /// @param speed_factor Multiply vanilla speed if different from 1.0
    /// @return Success if goal is reached, Failure otherwise
    Status GoToDouble(BehaviourClient& client, const Vector3<double>& goal, const bool allow_jump = true, const bool sprint = true, const float speed_factor = 1.0f);

    /// @brief Same thing as GoToDouble, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if goal is reached, Failure otherwise
    Status GoToDoubleBlackboard(BehaviourClient& client);


    /// @brief Turn the camera to look at a given target and send the new rotation to the server
    /// @param client The client performing the action
    /// @param target The target to look at
    /// @param set_pitch If false, only the yaw will be changed
    /// @return Always return Success
    Status LookAt(BehaviourClient& client, const Vector3<double>& target, const bool set_pitch = true);

    /// @brief Same thing as LookAt, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status LookAtBlackboard(BehaviourClient& client);

    /// @brief Make the current player fly (as in creative/spectator mode, NOT WITH ELYTRA)
    /// @param client The client performing the action
    /// @return Success if the player is now flying, failure otherwise
    Status StartFlying(BehaviourClient& client);

    /// @brief Make the current player not fly (as in creative/spectator mode, NOT WITH ELYTRA)
    /// @param client The client performing the action
    /// @return Success if the player is now not flying anymore, failure otherwise
    Status StopFlying(BehaviourClient& client);
} // namespace Botcraft
