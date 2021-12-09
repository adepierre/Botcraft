#include <iostream>

#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"

#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"

namespace Botcraft
{
    const std::vector<Position> FindPath(BehaviourClient& client, const Position& start, const Position& end, const int min_end_dist, const bool allow_jump)
    {
        struct PathNode
        {
            Position pos;
            float score; // distance from start + heuristic to goal
            PathNode(const Position& p, const float s)
            {
                pos = p;
                score = s;
            }

            bool operator>(const PathNode& rhs) const
            {
                return score > rhs.score;
            }

            static const float Heuristic(const Position& a, const Position& b)
            {
                return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
            }
        };

        const std::vector<Position> neighbour_offsets({ Position(1, 0, 0), Position(-1, 0, 0), Position(0, 0, 1), Position(0, 0, -1) });
        std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode> > nodes_to_explore;
        std::unordered_map<Position, Position> came_from;
        std::unordered_map<Position, float> cost;

        nodes_to_explore.emplace(PathNode(start, 0.0f));
        came_from[start] = start;
        cost[start] = 0.0f;

        int count_visit = 0;

        std::shared_ptr<World> world = client.GetWorld();

        while (!nodes_to_explore.empty())
        {
            count_visit++;
            PathNode current_node = nodes_to_explore.top();
            nodes_to_explore.pop();

            if (count_visit > 10000 ||
                (std::abs(end.x - start.x) + std::abs(end.z - start.z) >= min_end_dist && current_node.pos == end) ||
                (std::abs(end.x - start.x) + std::abs(end.z - start.z) < min_end_dist) && (std::abs(end.x - current_node.pos.x) + std::abs(end.z - current_node.pos.z) >= min_end_dist))
            {
                break;
            }

            // For each neighbour, check if it's reachable
            // and add it to the search list if it is
            for (int i = 0; i < neighbour_offsets.size(); ++i)
            {
                const Position next_location = current_node.pos + neighbour_offsets[i];
                const Position next_next_location = next_location + neighbour_offsets[i];
                // Get the state around the player in the given location
                // True = solid, False = go through
                std::array<bool, 13> surroundings = { false, false, false, false, false, false,
                    false, false, false, false, false, false, false };
                // 0  1  7
                // x  2  8
                // x  3  9
                //--- 4  10
                //    5  11
                //    6  12
                bool is_in_fluid;
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());

                    const Block* block = world->GetBlock(current_node.pos);
                    is_in_fluid = block && block->GetBlockstate()->IsFluid();

                    // Start with 2 because if 2 is solid, no pathfinding is possible
                    block = world->GetBlock(next_location + Position(0, 1, 0));
                    surroundings[2] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    if (surroundings[2])
                    {
                        continue;
                    }

                    block = world->GetBlock(current_node.pos + Position(0, 2, 0));
                    surroundings[0] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));

                    block = world->GetBlock(next_location + Position(0, 2, 0));
                    surroundings[1] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location);
                    surroundings[3] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location + Position(0, -1, 0));
                    surroundings[4] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location + Position(0, -2, 0));
                    surroundings[5] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location + Position(0, -3, 0));
                    surroundings[6] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));

                    // You can't make large jumps if your feet are in fluid
                    if (allow_jump && !is_in_fluid)
                    {
                        block = world->GetBlock(next_next_location + Position(0, 2, 0));
                        surroundings[7] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, 1, 0));
                        surroundings[8] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location);
                        surroundings[9] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, -1, 0));
                        surroundings[10] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, -2, 0));
                        surroundings[11] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, -3, 0));
                        surroundings[12] = block && block->GetBlockstate()->IsSolid();
                    }
                }

                // We can check all cases that could allow the bot to pass
                //       ?
                // x     ?
                // x  o  ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && surroundings[3])
                {
                    const float new_cost = cost[current_node.pos] + 2.0f;
                    const Position new_pos = next_location + Position(0, 1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ?
                // x     ?
                //--- o  ?
                //    ?  ?
                //    ?  ?
                if (!surroundings[2] && !surroundings[3]
                    && surroundings[4])
                {
                    const float new_cost = cost[current_node.pos] + 1.0f;
                    auto it = cost.find(next_location);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[next_location] = new_cost;
                        nodes_to_explore.emplace(PathNode(next_location, new_cost + PathNode::Heuristic(next_location, end)));
                        came_from[next_location] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ? 
                // x     ?
                //---    ?
                //    o  ?
                //    ?  ?
                if (!surroundings[2] && !surroundings[3]
                    && !surroundings[4] && surroundings[5])
                {
                    const float new_cost = cost[current_node.pos] + 2.0f;
                    const Position new_pos = next_location + Position(0, -1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ?
                // x     ?
                //---    ?
                //       ?
                //    o  ?
                if (!surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && surroundings[6])
                {
                    const float new_cost = cost[current_node.pos] + 3.0f;
                    const Position new_pos = next_location + Position(0, -2, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ?
                // x     ?
                //---    ?
                //       ?
                //       ?
                // Special case here, we can drop down
                // if there is some water at the bottom
                if (!surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[6])
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());

                    const Block* block;

                    for (int y = -4; next_location.y + y >= world->GetMinY(); --y)
                    {
                        block = world->GetBlock(next_location + Position(0, y, 0));

                        if (block && block->GetBlockstate()->IsSolid())
                        {
                            break;
                        }

                        if (block && block->GetBlockstate()->IsFluid()
                            && block->GetBlockstate()->GetName() == "minecraft:water")
                        {
                            const float new_cost = cost[current_node.pos] + std::abs(y);
                            const Position new_pos = next_location + Position(0, y + 1, 0);
                            auto it = cost.find(new_pos);
                            // If we don't already know this node with a better path, add it
                            if (it == cost.end() ||
                                new_cost < it->second)
                            {
                                cost[new_pos] = new_cost;
                                nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                                came_from[new_pos] = current_node.pos;
                            }

                            break;
                        }
                    }
                }

                if (!allow_jump || is_in_fluid)
                {
                    continue;
                }

                //        
                // x      
                // x     o
                //---    ?
                //    ?  ?
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[7]
                    && !surroundings[8] && surroundings[9])
                {
                    const float new_cost = cost[current_node.pos] + 3.0f;
                    const Position new_pos = next_next_location + Position(0, 1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                //        
                // x      
                // x      
                //---    o
                //       ?
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[7] && !surroundings[8]
                    && !surroundings[9] && surroundings[10])
                {
                    const float new_cost = cost[current_node.pos] + 3.0f;
                    auto it = cost.find(next_next_location);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[next_next_location] = new_cost;
                        nodes_to_explore.emplace(PathNode(next_next_location, new_cost + PathNode::Heuristic(next_next_location, end)));
                        came_from[next_next_location] = current_node.pos;
                    }
                }

                //        
                // x      
                // x      
                //---     
                //       o
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[7] && !surroundings[8]
                    && !surroundings[9] && !surroundings[10]
                    && surroundings[11])
                {
                    const float new_cost = cost[current_node.pos] + 4.0f;
                    const Position new_pos = next_next_location + Position(0, -1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                //        
                // x      
                // x      
                //---     
                //        
                //    ?  o
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[7] && !surroundings[8]
                    && !surroundings[9] && !surroundings[10]
                    && !surroundings[11] && surroundings[12])
                {
                    const float new_cost = cost[current_node.pos] + 5.0f;
                    const Position new_pos = next_next_location + Position(0, -2, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + PathNode::Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }
            } // neighbour loop
        }

        auto it_end_path = came_from.begin();

        // We search for the closest node
        // respecting the min_end_dist criterion
        float best_float_dist = std::numeric_limits<float>::max();
        for (auto it = came_from.begin(); it != came_from.end(); ++it)
        {
            const Position diff = it->first - end;
            const float distXZ = std::abs(diff.x) + std::abs(diff.z);
            const float d = std::abs(diff.y) + distXZ;
            if (d < best_float_dist && distXZ >= min_end_dist)
            {
                best_float_dist = d;
                it_end_path = it;
            }
        }

        std::deque<Position> output_deque;
        output_deque.push_front(it_end_path->first);
        while (it_end_path->second != start)
        {
            it_end_path = came_from.find(it_end_path->second);
            output_deque.push_front(it_end_path->first);
        }
        return std::vector<Position>(output_deque.begin(), output_deque.end());
    }

    Status GoTo(BehaviourClient& client, const Position& goal, const int dist_tolerance,
        const int min_end_dist, const float speed, const bool allow_jump)
    {
        std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
        std::shared_ptr<World> world = client.GetWorld();
        Position current_position;
        do
        {
            // Wait until we are on the ground
            while (!local_player->GetOnGround())
            {
                client.Yield();
            }

            // Get the position
            current_position = Position(std::floor(local_player->GetPosition().x), std::floor(local_player->GetPosition().y), std::floor(local_player->GetPosition().z));

            std::vector<Position> path;
            bool is_goal_loaded;
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                is_goal_loaded = world->IsLoaded(goal);
            }

            // Path finding step
            if (!is_goal_loaded)
            {
                std::cout << "[" << client.GetNetworkManager()->GetMyName() << "] Current goal position " << goal << " is either air or not loaded, trying to get closer to load the chunk" << std::endl;
                Vector3<double> goal_direction(goal.x - current_position.x, goal.y - current_position.y, goal.z - current_position.z);
                goal_direction.Normalize();
                path = FindPath(client, current_position,
                    current_position + Position(goal_direction.x * 32, goal_direction.y * 32, goal_direction.z * 32), min_end_dist, allow_jump);
            }
            else
            {
                Position diff = goal - current_position;
                if (dist_tolerance && diff.dot(diff) <= dist_tolerance * dist_tolerance && std::abs(diff.x) + std::abs(diff.z) >= min_end_dist)
                {
                    return Status::Success;
                }
                path = FindPath(client, current_position, goal, min_end_dist, allow_jump);
            }

            if (path.size() == 0 || path[path.size() - 1] == current_position)
            {
                if (!dist_tolerance)
                {
                    std::cout << "Warning, pathfinding cannot find a better position than " << current_position << ". Staying there." << std::endl;
                    return Status::Failure;
                }
                else
                {
                    Position diff = goal - current_position;
                    return diff.dot(diff) <= dist_tolerance * dist_tolerance ? Status::Success : Status::Failure;
                }
            }

            for (int i = 0; i < path.size(); ++i)
            {
                const Vector3<double> initial_position = local_player->GetPosition();
                const Vector3<double> target_position(path[i].x + 0.5, path[i].y, path[i].z + 0.5);
                const Vector3<double> motion_vector = target_position - initial_position;
                local_player->LookAt(target_position);

                // If we have to jump to get to the next position
                if (path[i].y > current_position.y ||
                    std::abs(motion_vector.x) > 1.5 ||
                    std::abs(motion_vector.z) > 1.5)
                {
                    // Jump
                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        local_player->SetSpeedY(0.4196141); // Not sure about this. I tried to calculate it in order to get a 1.25 block height jump (reached in 6 ticks)
                    }

                    if (std::abs(motion_vector.x) < 1.5 &&
                        std::abs(motion_vector.z) < 1.5)
                    {
                        auto now = std::chrono::system_clock::now();
                        bool has_timeout = false;
                        while (local_player->GetY() - initial_position.y < 1.0f)
                        {
                            // This indicates that a jump we wanted to make is not possible anymore
                            // recalculating the path
                            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - now).count() >= 3000)
                            {
                                has_timeout = true;
                                break;
                            }
                            client.Yield();
                        }
                        if (has_timeout)
                        {
                            break;
                        }
                    }
                }

                auto start = std::chrono::system_clock::now();
                auto previous_step = start;
                const double motion_norm_xz = std::abs(motion_vector.x) + std::abs(motion_vector.z);
                while (true)
                {
                    auto now = std::chrono::system_clock::now();
                    long long int time_count = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
                    // If we are over the time we have at speed to travel one block
                    if (time_count > 1000 * motion_norm_xz / speed)
                    {
                        {
                            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                            local_player->SetSpeedX(target_position.x - local_player->GetX());
                            local_player->SetY(local_player->GetY() + 0.001);
                            local_player->SetSpeedZ(target_position.z - local_player->GetZ());

                            // If the target motion requires going down
                            if (motion_vector.y < 0)
                            {
                                local_player->SetOnGround(false);
                            }
                        }
                        break;
                    }
                    // Otherwise just move partially toward the goal
                    else
                    {
                        long long int delta_t = std::chrono::duration_cast<std::chrono::milliseconds>(now - previous_step).count();
                        Vector3<double> delta_v = motion_vector * delta_t / (1000.0 * motion_norm_xz) * speed;
                        {
                            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                            local_player->SetSpeedX(local_player->GetSpeed().x + delta_v.x);
                            local_player->SetY(local_player->GetY() + 0.001);
                            local_player->SetSpeedZ(local_player->GetSpeed().z + delta_v.z);
                        }
                        previous_step = now;
                    }
                    client.Yield();
                }

                // Wait for the confirmation that we arrived at the destination
                start = std::chrono::system_clock::now();
                bool has_timeout = false;
                while (true)
                {
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 3000)
                    {
                        has_timeout = true;
                        break;
                    }

                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        const Vector3<double> diff = local_player->GetPosition() - target_position;
                        if (std::abs(diff.x) + std::abs(diff.z) < 1e-2)
                        {
                            break;
                        }
                    }
                    client.Yield();
                }

                // Wait until we are on the ground
                while (!local_player->GetOnGround())
                {
                    client.Yield();
                }

                current_position = Position(std::floor(local_player->GetPosition().x), std::floor(local_player->GetPosition().y), std::floor(local_player->GetPosition().z));

                if (has_timeout)
                {
                    // Something went wrong during the movement,
                    // replanning the path is safer
                    break;
                }
            }
        } while (current_position != goal);

        return Status::Success;
    }

    Status GoToBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
        "GoTo.goal", "GoTo.dist_tolerance", "GoTo.min_end_dist",
        "GoTo.speed", "GoTo.allow_jump" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const Position& goal = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const int dist_tolerance = blackboard.Get(variable_names[1], 0);
        const int min_end_dist = blackboard.Get(variable_names[2], 0);
        const float speed = blackboard.Get(variable_names[3], 4.317f);
        const bool allow_jump = blackboard.Get(variable_names[4], true);

        return GoTo(client, goal, dist_tolerance, min_end_dist, speed, allow_jump);;
    }
}
