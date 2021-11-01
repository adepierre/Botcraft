#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    /// <summary>
    /// Compute a path to pos and go to this position.
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <param name="goal">The end goal</param>
    /// <param name="dist_tolerance">If != 0 and the distance between end position and goal is < dist_tolerance, return success even if goal is not reached</param>
    /// <param name="min_end_dist">Minimum distance between the end position and goal (useful if you want to place a block, you don't want to be at the exact spot, but close to it)</param>
    /// <param name="speed">Travel speed (block per s)</param>
    /// <param name="allow_jump">If true, allow to jump above 1-wide gaps</param>
    /// <returns>Success if goal is reached, Failure otherwise</returns>
    Status GoTo(BehaviourClient& client, const Position& goal, const int dist_tolerance = 0,
        const int min_end_dist = 0, const float speed = 4.317f, const bool allow_jump = true);

    /// <summary>
    /// GoTo version that reads parameters from the blackboard
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <returns>Success if goal is reached, Failure otherwise</returns>
    Status GoToBlackboard(BehaviourClient& client);

} // namespace Botcraft
