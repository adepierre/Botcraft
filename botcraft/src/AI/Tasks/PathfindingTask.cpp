#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/Physics/PhysicsManager.hpp"

#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/MiscUtilities.hpp"

namespace Botcraft
{
    enum class BlockPathfindingState: char
    {
        Empty = 0,
        /// @brief Can walk on, can't go through
        Solid = 1 << 0,
        /// @brief Take damage if walk through/on
        Hazardous = 1 << 1,
        /// @brief Can climb up/down
        Climbable = 1 << 2,
        /// @brief Can climb but can't walk on
        Fluid = 1 << 3
    };

    BlockPathfindingState operator|(const BlockPathfindingState a, const BlockPathfindingState b)
    {
        return static_cast<BlockPathfindingState>(static_cast<char>(a) | static_cast<char>(b));
    }

    bool operator&(const BlockPathfindingState a, const BlockPathfindingState b)
    {
        return (static_cast<char>(a) & static_cast<char>(b)) > 0;
    }

    BlockPathfindingState GetBlockGoThroughState(const Block* block, const bool take_damage)
    {
        if (block == nullptr)
        {
            return BlockPathfindingState::Empty;
        }

        if (take_damage && block->GetBlockstate()->IsHazardous())
        {
            return BlockPathfindingState::Hazardous;
        }

        if (block->GetBlockstate()->IsFluid())
        {
            return BlockPathfindingState::Climbable | BlockPathfindingState::Fluid;
        }

        if (block->GetBlockstate()->IsClimbable())
        {
            return BlockPathfindingState::Climbable;
        }

        return block->GetBlockstate()->IsSolid() ? BlockPathfindingState::Solid : BlockPathfindingState::Empty;
    }

    std::vector<Position> FindPath(const BehaviourClient& client, const Position& start, const Position& end, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const bool allow_jump)
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
                return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z));
            }
        };

        constexpr int budget_visit = 15000;

        const std::vector<Position> neighbour_offsets({ Position(1, 0, 0), Position(-1, 0, 0), Position(0, 0, 1), Position(0, 0, -1) });
        std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode> > nodes_to_explore;
        std::unordered_map<Position, Position> came_from;
        std::unordered_map<Position, float> cost;

        nodes_to_explore.emplace(PathNode(start, 0.0f));
        came_from[start] = start;
        cost[start] = 0.0f;

        int count_visit = 0;
        // We found one location matching all the criterion, but
        // continue the search to see if we can find a better one
        bool suitable_location_found = false;
        // We found a path to the desired goal
        bool end_reached = false;

        bool end_is_inside_solid = false;
        std::shared_ptr<World> world = client.GetWorld();
        {
            std::lock_guard<std::mutex> lock(world->GetMutex());
            const Block* block = world->GetBlock(end);
            end_is_inside_solid = block != nullptr && block->GetBlockstate()->IsSolid();
        }
        const bool takes_damage = !client.GetCreativeMode();

        while (!nodes_to_explore.empty())
        {
            count_visit++;
            PathNode current_node = nodes_to_explore.top();
            nodes_to_explore.pop();

            end_reached |= current_node.pos == end;
            suitable_location_found |=
                std::abs(end.x - current_node.pos.x) + std::abs(end.y - current_node.pos.y) + std::abs(end.z - current_node.pos.z) <= dist_tolerance &&
                std::abs(end.x - current_node.pos.x) + std::abs(end.y - current_node.pos.y) + std::abs(end.z - current_node.pos.z) >= min_end_dist &&
                std::abs(end.x - current_node.pos.x) + std::abs(end.z - current_node.pos.z) >= min_end_dist_xz;

            if (// If we exceeded the search budget
                count_visit > budget_visit ||
                // Or if we found a suitable location in the process and already reached the goal/can't reach it anyway
                (suitable_location_found && (end_reached || end_is_inside_solid)))
            {
                break;
            }

            // Get the state around the player in the given location
            std::array<BlockPathfindingState, 6> vertical_surroundings = {
                BlockPathfindingState::Solid, BlockPathfindingState::Solid, BlockPathfindingState::Solid,
                BlockPathfindingState::Solid, BlockPathfindingState::Solid, BlockPathfindingState::Solid
            };

            // Assuming the player is standing on 3 (feeet on 2 and head on 1)
            // 0
            // 1
            // 2
            // 3
            // 4
            // 5
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());

                const Block* block = world->GetBlock(current_node.pos + Position(0, 2, 0));
                vertical_surroundings[0] = GetBlockGoThroughState(block, takes_damage);
                block = world->GetBlock(current_node.pos + Position(0, 1, 0));
                vertical_surroundings[1] = GetBlockGoThroughState(block, takes_damage);
                // Our feet block (should be climbable or empty)
                block = world->GetBlock(current_node.pos);
                vertical_surroundings[2] = GetBlockGoThroughState(block, takes_damage);

                // if 3 is solid or hazardous, no down pathfinding is possible,
                // so we can skip a few checks
                block = world->GetBlock(current_node.pos + Position(0, -1, 0));
                vertical_surroundings[3] = GetBlockGoThroughState(block, takes_damage);

                // If we can move down, we need 4 and 5
                if (vertical_surroundings[3] != BlockPathfindingState::Solid && vertical_surroundings[3] != BlockPathfindingState::Hazardous)
                {
                    block = world->GetBlock(current_node.pos + Position(0, -2, 0));
                    vertical_surroundings[4] = GetBlockGoThroughState(block, takes_damage);
                    block = world->GetBlock(current_node.pos + Position(0, -3, 0));
                    vertical_surroundings[5] = GetBlockGoThroughState(block, takes_damage);
                }
            }


            // Check all vertical cases that would allow the bot to pass
            // -
            // x
            // ^
            // ?
            // ?
            // ?
            if (vertical_surroundings[2] & BlockPathfindingState::Climbable
                && vertical_surroundings[1] != BlockPathfindingState::Solid
                && vertical_surroundings[1] != BlockPathfindingState::Hazardous
                && vertical_surroundings[0] != BlockPathfindingState::Solid
                && vertical_surroundings[0] != BlockPathfindingState::Hazardous
                )
            {
                const float new_cost = cost[current_node.pos] + 1.0f;
                const Position new_pos = current_node.pos + Position(0, 1, 0);
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

            // -
            // ^
            //  
            // o
            // ?
            // ?
            if (vertical_surroundings[3] == BlockPathfindingState::Solid
                && vertical_surroundings[2] == BlockPathfindingState::Empty
                && vertical_surroundings[1] & BlockPathfindingState::Climbable
                && vertical_surroundings[0] != BlockPathfindingState::Solid
                && vertical_surroundings[0] != BlockPathfindingState::Hazardous
                )
            {
                const float new_cost = cost[current_node.pos] + 1.5f;
                const Position new_pos = current_node.pos + Position(0, 1, 0);
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

            // ?
            // x
            // x
            // -
            // ?
            // ?
            if (vertical_surroundings[3] & BlockPathfindingState::Climbable)
            {
                const float new_cost = cost[current_node.pos] + 1.0f;
                const Position new_pos = current_node.pos + Position(0, -1, 0);
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

            // ?
            // x
            // x
            // -
            //  
            // o
            if (vertical_surroundings[3] & BlockPathfindingState::Climbable
                && vertical_surroundings[4] == BlockPathfindingState::Empty
                && vertical_surroundings[5] != BlockPathfindingState::Empty
                && vertical_surroundings[5] != BlockPathfindingState::Hazardous
                )
            {
                const float new_cost = cost[current_node.pos] + 2.0f;
                const Position new_pos = current_node.pos + Position(0, -2, 0);
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



            // ?
            // x
            // ^
            //  
            //  
            // o
            if (vertical_surroundings[2] & BlockPathfindingState::Climbable
                && vertical_surroundings[3] == BlockPathfindingState::Empty
                && vertical_surroundings[4] == BlockPathfindingState::Empty
                && vertical_surroundings[5] != BlockPathfindingState::Empty
                && vertical_surroundings[5] != BlockPathfindingState::Hazardous
                )
            {
                const float new_cost = cost[current_node.pos] + 2.0f;
                const Position new_pos = current_node.pos + Position(0, -2, 0);
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


            // ?
            // x
            // x
            // -
            //  
            //  
            // Special case here, we can drop down
            // if there is a climbable at the bottom
            if (vertical_surroundings[3] & BlockPathfindingState::Climbable
                && vertical_surroundings[4] == BlockPathfindingState::Empty
                && vertical_surroundings[5] == BlockPathfindingState::Empty
                )
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());

                const Block* block;

                for (int y = -4; current_node.pos.y + y >= world->GetMinY(); --y)
                {
                    block = world->GetBlock(current_node.pos + Position(0, y, 0));

                    if (block && block->GetBlockstate()->IsSolid())
                    {
                        break;
                    }

                    if (block && block->GetBlockstate()->IsClimbable())
                    {
                        const float new_cost = cost[current_node.pos] + std::abs(y);
                        const Position new_pos = current_node.pos + Position(0, y + 1, 0);
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


            // For each neighbour, check if it's reachable
            // and add it to the search list if it is
            for (int i = 0; i < neighbour_offsets.size(); ++i)
            {
                const Position next_location = current_node.pos + neighbour_offsets[i];
                const Position next_next_location = next_location + neighbour_offsets[i];

                // Get the state around the player in the given direction
                std::array<BlockPathfindingState, 12> horizontal_surroundings = {
                    BlockPathfindingState::Solid, BlockPathfindingState::Solid, BlockPathfindingState::Solid,
                    BlockPathfindingState::Solid, BlockPathfindingState::Solid, BlockPathfindingState::Solid,
                    BlockPathfindingState::Solid, BlockPathfindingState::Solid, BlockPathfindingState::Solid,
                    BlockPathfindingState::Solid, BlockPathfindingState::Solid, BlockPathfindingState::Solid
                };

                // Assuming the player is standing on v3 (feeet on v2 and head on v1)
                // v0   0   6 --> ?  ?  ?
                // v1   1   7 --> x  ?  ?
                // v2   2   8 --> x  ?  ?
                // v3   3   9 --> ?  ?  ?
                // v4   4  10 --> ?  ?  ?
                // v5   5  11 --> ?  ?  ?
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());

                    // if 1 is solid, no horizontal pathfinding is possible,
                    // so we can skip a lot of checks
                    const Block* block = world->GetBlock(next_location + Position(0, 1, 0));
                    horizontal_surroundings[1] = GetBlockGoThroughState(block, takes_damage);
                    const bool horizontal_movement = horizontal_surroundings[1] != BlockPathfindingState::Solid && horizontal_surroundings[1] != BlockPathfindingState::Hazardous;

                    // If we can move horizontally, we need the full column
                    if (horizontal_movement)
                    {
                        block = world->GetBlock(next_location + Position(0, 2, 0));
                        horizontal_surroundings[0] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_location);
                        horizontal_surroundings[2] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_location + Position(0, -1, 0));
                        horizontal_surroundings[3] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_location + Position(0, -2, 0));
                        horizontal_surroundings[4] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_location + Position(0, -3, 0));
                        horizontal_surroundings[5] = GetBlockGoThroughState(block, takes_damage);
                    }

                    // You can't make large jumps if your feet are in a climbable block
                    // If we can jump, then we need the third column
                    if (allow_jump && !(vertical_surroundings[2] & BlockPathfindingState::Climbable))
                    {
                        block = world->GetBlock(next_next_location + Position(0, 2, 0));
                        horizontal_surroundings[6] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_next_location + Position(0, 1, 0));
                        horizontal_surroundings[7] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_next_location);
                        horizontal_surroundings[8] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_next_location + Position(0, -1, 0));
                        horizontal_surroundings[9] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_next_location + Position(0, -2, 0));
                        horizontal_surroundings[10] = GetBlockGoThroughState(block, takes_damage);
                        block = world->GetBlock(next_next_location + Position(0, -3, 0));
                        horizontal_surroundings[11] = GetBlockGoThroughState(block, takes_damage);
                    }
                }

                // Now that we know the surroundings, we can check all
                // horizontal cases that would allow the bot to pass

                /************ HORIZONTAL **************/

                // ?  ?  ?
                // x  -  ?
                // x  -  ?
                //--- o  ?
                //    ?  ?
                //    ?  ?
                if (horizontal_surroundings[1] != BlockPathfindingState::Solid
                    && horizontal_surroundings[1] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[2] != BlockPathfindingState::Solid
                    && horizontal_surroundings[2] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[3] != BlockPathfindingState::Empty
                    && horizontal_surroundings[3] != BlockPathfindingState::Hazardous
                    && (!(horizontal_surroundings[3] & BlockPathfindingState::Fluid)  // We can't go from above a fluid to above
                        || !(vertical_surroundings[3] & BlockPathfindingState::Fluid) // another one to avoid "walking on water"
                        || horizontal_surroundings[2] & BlockPathfindingState::Fluid  // except if one or both "leg level" blocks
                        || vertical_surroundings[2] & BlockPathfindingState::Fluid)   // are also fluids
                    )
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


                // -  -  ?
                // x  ^  ?
                // x  ?  ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (vertical_surroundings[0] != BlockPathfindingState::Solid
                    && vertical_surroundings[0] != BlockPathfindingState::Hazardous
                    && vertical_surroundings[1] == BlockPathfindingState::Empty
                    && vertical_surroundings[2] == BlockPathfindingState::Empty
                    && vertical_surroundings[3] == BlockPathfindingState::Solid
                    && horizontal_surroundings[0] != BlockPathfindingState::Solid
                    && horizontal_surroundings[0] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[1] & BlockPathfindingState::Climbable
                    )
                {
                    const float new_cost = cost[current_node.pos] + 2.5f;
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

                // -  -  ?
                // x  -  ?
                // x  o  ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (vertical_surroundings[0] != BlockPathfindingState::Solid
                    && vertical_surroundings[0] != BlockPathfindingState::Hazardous
                    && vertical_surroundings[1] == BlockPathfindingState::Empty
                    && vertical_surroundings[2] == BlockPathfindingState::Empty
                    && vertical_surroundings[3] == BlockPathfindingState::Solid
                    && horizontal_surroundings[0] != BlockPathfindingState::Solid
                    && horizontal_surroundings[0] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[1] != BlockPathfindingState::Solid
                    && horizontal_surroundings[1] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[2] != BlockPathfindingState::Empty
                    && horizontal_surroundings[2] != BlockPathfindingState::Hazardous
                    )
                {
                    const float new_cost = cost[current_node.pos] + 2.5f;
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
                // x  -  ?
                // x     ?
                //---    ?
                //    o  ?
                //    ?  ?
                if (horizontal_surroundings[1] != BlockPathfindingState::Solid
                    && horizontal_surroundings[1] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[2] == BlockPathfindingState::Empty
                    && horizontal_surroundings[3] == BlockPathfindingState::Empty
                    && horizontal_surroundings[4] != BlockPathfindingState::Empty
                    && horizontal_surroundings[4] != BlockPathfindingState::Hazardous
                    )
                {
                    const float new_cost = cost[current_node.pos] + 2.5f;
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
                // x  -  ?
                // x     ?
                //---    ?
                //       ?
                //    o  ?
                if (horizontal_surroundings[1] != BlockPathfindingState::Solid
                    && horizontal_surroundings[1] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[2] == BlockPathfindingState::Empty
                    && horizontal_surroundings[3] == BlockPathfindingState::Empty
                    && horizontal_surroundings[4] == BlockPathfindingState::Empty
                    && horizontal_surroundings[5] != BlockPathfindingState::Empty
                    && horizontal_surroundings[5] != BlockPathfindingState::Hazardous
                    )
                {
                    const float new_cost = cost[current_node.pos] + 3.5f;
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
                // x  -  ?
                // x     ?
                //---    ?
                //       ?
                //       ?
                // Special case here, we can drop down
                // if there is a climbable at the bottom
                if (horizontal_surroundings[1] != BlockPathfindingState::Solid
                    && horizontal_surroundings[1] != BlockPathfindingState::Hazardous
                    && horizontal_surroundings[2] == BlockPathfindingState::Empty
                    && horizontal_surroundings[3] == BlockPathfindingState::Empty
                    && horizontal_surroundings[4] == BlockPathfindingState::Empty
                    && horizontal_surroundings[5] == BlockPathfindingState::Empty
                    )
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

                        if (block && block->GetBlockstate()->IsClimbable())
                        {
                            const float new_cost = cost[current_node.pos] + std::abs(y) + 1.5f;
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

                // If we can't make jumps, don't bother explore the rest
                // of the cases
                if (!allow_jump
                    || vertical_surroundings[0] == BlockPathfindingState::Solid       // Block above
                    || vertical_surroundings[0] == BlockPathfindingState::Hazardous   // Block above
                    || vertical_surroundings[1] != BlockPathfindingState::Empty       // Block above
                    || vertical_surroundings[2] != BlockPathfindingState::Empty       // Feet inside climbable
                    || vertical_surroundings[3] & BlockPathfindingState::Fluid        // "Walking" on fluid
                    || vertical_surroundings[3] == BlockPathfindingState::Empty       // Feet on nothing (inside climbable)
                    || horizontal_surroundings[0] == BlockPathfindingState::Solid     // Block above next column
                    || horizontal_surroundings[0] == BlockPathfindingState::Hazardous // Hazard above next column
                    || horizontal_surroundings[1] != BlockPathfindingState::Empty     // Non empty block in next column, can't jump through it
                    || horizontal_surroundings[2] != BlockPathfindingState::Empty     // Non empty block in next column, can't jump through it
                    || horizontal_surroundings[6] == BlockPathfindingState::Solid     // Block above nextnext column
                    || horizontal_surroundings[6] == BlockPathfindingState::Hazardous // Hazard above nextnext column
                    || horizontal_surroundings[7] != BlockPathfindingState::Empty     // Non empty block in nextnext column, can't jump through it
                    )
                {
                    continue;
                }

                /************ BIG JUMP **************/
                // -  -  -
                // x      
                // x     o
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (horizontal_surroundings[8] != BlockPathfindingState::Empty
                    && horizontal_surroundings[8] != BlockPathfindingState::Hazardous
                    )
                {
                    // 4 > 3.5 as if horizontal_surroundings[3] is solid we prefer to walk then jump instead of big jump
                    // but if horizontal_surroundings[3] is hazardous we can jump over it
                    const float new_cost = cost[current_node.pos] + 4.0f;
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

                // -  -  -
                // x      
                // x      
                //--- ?  o
                //    ?  ?
                //    ?  ?
                if (horizontal_surroundings[8] == BlockPathfindingState::Empty
                    && horizontal_surroundings[9] != BlockPathfindingState::Empty
                    && horizontal_surroundings[9] != BlockPathfindingState::Hazardous
                    )
                {
                    const float new_cost = cost[current_node.pos] + 2.5f;
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

                // -  -  -
                // x      
                // x      
                //--- ?   
                //    ?  o
                //    ?  ?
                if (horizontal_surroundings[8] == BlockPathfindingState::Empty
                    && horizontal_surroundings[9] == BlockPathfindingState::Empty
                    && horizontal_surroundings[10] != BlockPathfindingState::Empty
                    && horizontal_surroundings[10] != BlockPathfindingState::Hazardous
                    )
                {
                    const float new_cost = cost[current_node.pos] + 4.5f;
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

                // -  -  -
                // x      
                // x      
                //--- ?   
                //    ?   
                //    ?  o
                if (horizontal_surroundings[8] == BlockPathfindingState::Empty
                    && horizontal_surroundings[9] == BlockPathfindingState::Empty
                    && horizontal_surroundings[10] == BlockPathfindingState::Empty
                    && horizontal_surroundings[11] != BlockPathfindingState::Empty
                    && horizontal_surroundings[11] != BlockPathfindingState::Hazardous
                    )
                {
                    const float new_cost = cost[current_node.pos] + 5.5f;
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

        // We search for the node respecting
        // the criteria AND the closest to
        // start as it should often lead
        // to a shorter path. In case of a tie,
        // take the one the closest to the end
        int best_dist = std::numeric_limits<int>::max();
        int best_dist_start = std::numeric_limits<int>::max();
        for (auto it = came_from.begin(); it != came_from.end(); ++it)
        {
            const Position diff = it->first - end;
            const int d_xz = std::abs(diff.x) + std::abs(diff.z);
            const int d = d_xz + std::abs(diff.y);
            const Position diff_start = it->first - start;
            const int d_start = std::abs(diff_start.x) + std::abs(diff_start.y) + std::abs(diff_start.z);
            if (d <= dist_tolerance && d >= min_end_dist && d_xz >= min_end_dist_xz &&
                (d_start < best_dist_start || (d_start == best_dist_start && d < best_dist))
                )
            {
                best_dist = d;
                best_dist_start = d_start;
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

    bool Move(BehaviourClient& client, std::shared_ptr<LocalPlayer>& local_player, const Position& target_pos, const float speed, const float climbing_speed)
    {
        bool is_climbing;
        Vector3<double> initial_position;
        Position initial_block_pos;
        const Vector3<double> target_position(target_pos.x + 0.5, target_pos.y, target_pos.z + 0.5);

        {
            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
            is_climbing = local_player->GetIsClimbing();
            initial_position = local_player->GetPosition();
            initial_block_pos = Position(
                static_cast<int>(std::floor(local_player->GetPosition().x)),
                static_cast<int>(std::floor(local_player->GetPosition().y + 0.25)),
                static_cast<int>(std::floor(local_player->GetPosition().z))
            );
            local_player->LookAt(target_position + Vector3<double>(0.0, 1.62, 0.0), true);
        }
        const Vector3<double> motion_vector = target_position - initial_position;

        // If need to jump to catch climbable at head level
        if (std::abs(motion_vector.x) < 0.5
            && std::abs(motion_vector.z) < 0.5
            && motion_vector.y > 0.5
            && !is_climbing
            )
        {
            // Jump
            {
                std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                local_player->Jump();
            }

            auto now = std::chrono::steady_clock::now();
            while (true)
            {
                // Something went wrong during jumping
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count() >= 2000)
                {
                    return false;
                }
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    if (local_player->GetY() - initial_position.y >= 1.0f
                        || local_player->GetIsClimbing())
                    {
                        break;
                    }
                }
                client.Yield();
            }

            // We are in the climbable block we want to reach,
            // now adjust Y position to target
            {
                std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                local_player->SetPlayerInputsY(target_position.y + 0.001 - local_player->GetY() - local_player->GetSpeedY());
            }

            // Wait for physics thread to update position
            now = std::chrono::steady_clock::now();
            while (true)
            {
                // Something went wrong
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count() >= 1000)
                {
                    return false;
                }
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    if (std::abs(local_player->GetY() - target_position.y) <= 1e-2)
                    {
                        break;
                    }
                }
                client.Yield();
            }
        }
        // If we need to climb/go down
        else if (std::abs(motion_vector.x) < 0.5
            && std::abs(motion_vector.z) < 0.5
            && std::abs(motion_vector.y) > 0.5
            )
        {
            // Get the real movement that has to be done
            // (without the optional free fall after)
            Vector3<double> player_movement = motion_vector;

            if (player_movement.y < -2.05)
            {
                player_movement.y = -2.0;
            }

            auto start = std::chrono::steady_clock::now();
            auto previous_step = start;
            while (true)
            {
                auto now = std::chrono::steady_clock::now();
                long long int time_count = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
                // Something went wrong
                if (time_count > 1000 + 1000 * std::abs(player_movement.y) / climbing_speed)
                {
                    return false;
                }
                // We climb/go down at climbing_speed block/s
                // Set the input to adjust position
                else if (time_count > 1000 * std::abs(player_movement.y) / climbing_speed)
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    // If the physics thread has updated the position to the target, we're good
                    if (std::abs(local_player->GetY() - (initial_position.y + player_movement.y)) <= 1e-2)
                    {
                        break;
                    }
                    // Else adjust the position to reach it on the next physics update
                    local_player->SetPlayerInputsY(initial_position.y + player_movement.y + 0.001 - local_player->GetY() - local_player->GetSpeedY());
                }
                // Otherwise just move partially toward the goal
                else
                {
                    long long int delta_t = std::chrono::duration_cast<std::chrono::milliseconds>(now - previous_step).count();
                    const double delta_y = player_movement.y * delta_t / 1000.0 * climbing_speed;
                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        local_player->AddPlayerInputsY(delta_y);
                    }
                    previous_step = now;
                }
                client.Yield();
            }

            if (motion_vector.y > -2.05)
            {
                return true;
            }

            // If we are here, it means we need to
            // free fall into a climbable block
            start = std::chrono::steady_clock::now();
            {
                std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                local_player->SetOnGround(false);
            }
            while (true)
            {
                // It took more than fall height * 500 ms to
                // get to the bottom, there is probably an issue
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= std::abs(motion_vector.y) * 500)
                {
                    return false;
                }

                // Crouch while we are above the target
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    const double diff = local_player->GetPosition().y - target_position.y;
                    if (diff > 0)
                    {
                        local_player->SetPlayerInputsY(-0.1);
                    }
                    else if (local_player->GetOnGround() || local_player->GetIsClimbing())
                    {
                        break;
                    }
                }
                client.Yield();
            }

            start = std::chrono::steady_clock::now();
            // Now we are inside the climbable block, we need to get back on top of it
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 1000)
                {
                    return false;
                }

                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    const double diff = local_player->GetPosition().y - target_position.y;

                    if (diff < 0)
                    {
                        local_player->SetPlayerInputsY(0.1);
                    }
                    // We are on top
                    else if (local_player->GetOnGround() || local_player->GetIsClimbing())
                    {
                        break;
                    }
                }
                client.Yield();
            }
        }
        // Move horizontally (with a jump if necessary)
        else if ((std::abs(motion_vector.x) > 0.5 && std::abs(motion_vector.x) < 2.5)
            || (std::abs(motion_vector.z) > 0.5 && std::abs(motion_vector.z) < 2.5))
        {
            // If we need to jump to reach an higher block, or to jump over a gap
            if (motion_vector.y > 0.5 || std::abs(motion_vector.x) > 1.5 || std::abs(motion_vector.z) > 1.5)
            {
                // Jump
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    local_player->Jump();
                }

                // If not a jump above a gap, wait until reaching the next Y value before moving X/Z
                auto now = std::chrono::steady_clock::now();
                while (std::abs(motion_vector.x) < 1.5 && std::abs(motion_vector.z) < 1.5)
                {
                    // Something went wrong during jumping
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - now).count() >= 2000)
                    {
                        return false;
                    }

                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        if (local_player->GetY() >= target_pos.y)
                        {
                            break;
                        }
                    }
                    client.Yield();
                }
            }

            auto start = std::chrono::steady_clock::now();
            auto previous_step = start;
            const double motion_norm_xz = std::abs(motion_vector.x) + std::abs(motion_vector.z);
            // Move forward to the right X/Z location
            while (true)
            {
                auto now = std::chrono::steady_clock::now();
                long long int time_count = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
                // If we are way over the time we have to travel one block, something went wrong
                if (time_count > 1000 * motion_norm_xz / speed + 500)
                {
                    return false;
                }
                // We should be arrived
                else if (time_count > 1000 * motion_norm_xz / speed)
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    const Vector3<double> diff = local_player->GetPosition() - target_position;

                    // We are at X/Z destination
                    if (std::abs(diff.x) + std::abs(diff.z) < 1e-2)
                    {
                        local_player->SetOnGround(false);
                        break;
                    }

                    // Otherwise, set X and Z inputs to reach the goal
                    local_player->SetPlayerInputsX(target_position.x - local_player->GetX() - local_player->GetSpeedX());
                    // if we only move horizontally, directly set the target pos
                    if (target_pos.y == initial_block_pos.y && motion_norm_xz < 1.5)
                    {
                        local_player->SetY(target_pos.y + 0.001);
                    }
                    else
                    {
                        local_player->SetY(local_player->GetY() + 0.001);
                    }
                    local_player->SetPlayerInputsZ(target_position.z - local_player->GetZ() - local_player->GetSpeedZ());
                }
                // Otherwise just move partially toward the goal
                else
                {
                    const double delta_t = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(now - previous_step).count());
                    Vector3<double> delta_v = motion_vector * delta_t / (1000.0 * motion_norm_xz) * speed;
                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        local_player->AddPlayerInputsX(delta_v.x);
                        // if we only move horizontally, directly set the target pos
                        if (target_pos.y == initial_block_pos.y && motion_norm_xz < 1.5)
                        {
                            local_player->SetY(target_pos.y + 0.001);
                        }
                        else
                        {
                            local_player->SetY(local_player->GetY() + 0.001);
                        }
                        local_player->AddPlayerInputsZ(delta_v.z);
                    }
                    previous_step = now;
                }
                client.Yield();
            }

            start = std::chrono::steady_clock::now();
            // Wait until not falling anymore
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= std::max(1000, static_cast<int>(std::abs(motion_vector.y) * 500)))
                {
                    return false;
                }

                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    // This is a long fall, we need to crouch to pass through the landing block without damage
                    if (motion_vector.y < -2.5)
                    {
                        local_player->SetPlayerInputsY(-0.1);
                    }

                    if (local_player->GetOnGround() || local_player->GetIsClimbing())
                    {
                        break;
                    }
                }
                client.Yield();
            }

            // This is a long fall
            if (motion_vector.y < -2.5)
            {
                // Now we are inside the climbable block, we need to get back on top of it
                start = std::chrono::steady_clock::now();
                while (true)
                {
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 1000)
                    {
                        return false;
                    }

                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        const double diff = local_player->GetPosition().y - target_position.y;

                        if (diff < 0)
                        {
                            local_player->SetPlayerInputsY(0.1);
                        }
                        // We are on top
                        else
                        {
                            break;
                        }
                    }
                    client.Yield();
                }
            }
            // We are potentially in a climbabale block, and need to go down to reach target Y
            else
            {
                start = std::chrono::steady_clock::now();
                previous_step = start;
                while (true)
                {
                    auto now = std::chrono::steady_clock::now();

                    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() >= std::max(1000, static_cast<int>(std::abs(motion_vector.y) * 1000)))
                    {
                        return false;
                    }

                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());

                        // If not climbing, wait for landing on the target block
                        if (!local_player->GetIsClimbing())
                        {
                            break;
                        }

                        const double diff = target_position.y - local_player->GetY();

                        if (std::abs(diff) <= 0.01)
                        {
                            break;
                        }

                        const double delta_y = std::chrono::duration_cast<std::chrono::milliseconds>(now - previous_step).count() * 1000.0 / climbing_speed;
                        if (local_player->GetY() > target_position.y)
                        {
                            local_player->AddPlayerInputsY(std::max(delta_y, diff - local_player->GetSpeedY() - local_player->GetPlayerInputsY()));
                        }
                        previous_step = now;
                    }

                    client.Yield();
                }

                // Make sure we are not falling anymore
                // (no need for a timeout as we can't fall/fly forever anyway)
                while (true)
                {
                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        if (local_player->GetOnGround() || local_player->GetIsClimbing())
                        {
                            break;
                        }
                    }
                    client.Yield();
                }
            }
        }
        else
        {
            LOG_ERROR("I don't know how to go from " << initial_position << " to " << target_position);
        }

        return true;
    }


    Status GoToImpl(BehaviourClient& client, const Position& goal, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const float speed, const bool allow_jump)
    {
        if (min_end_dist > dist_tolerance)
        {
            LOG_WARNING("min_end_dist should be <= dist_tolerance if you want pathfinding to work as expected");
        }
        if (min_end_dist_xz > dist_tolerance)
        {
            LOG_WARNING("min_end_dist_xz should be <= dist_tolerance if you want pathfinding to work as expected");
        }
        std::shared_ptr<EntityManager> entity_manager = client.GetEntityManager();
        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
        std::shared_ptr<World> world = client.GetWorld();
        std::shared_ptr<PhysicsManager> physics_manager = client.GetPhysicsManager();
        // Enable gravity in case we are in creative mode
        const bool has_gravity = physics_manager->GetHasGravity();
        physics_manager->SetHasGravity(true);
        // Reset gravity when returning
        Utilities::OnEndScope reset_gravity([physics_manager, has_gravity]() { if (physics_manager != nullptr) physics_manager->SetHasGravity(has_gravity); });

        // Get real movement speed
        float movement_speed = speed;
        if (movement_speed == 0.0f)
        {
            const float base_speed = local_player->GetIsRunning() ? LocalPlayer::SPRINTING_SPEED : LocalPlayer::WALKING_SPEED;

            std::scoped_lock<std::mutex> entity_manager_lock(entity_manager->GetMutex());

            // Get speed effect
            unsigned char speed_amplifier = 0;
            for (const EntityEffect& effect : local_player->GetEffects())
            {
                if (effect.type == EntityEffectType::Speed && effect.end > std::chrono::steady_clock::now())
                {
                    speed_amplifier = effect.amplifier + 1; // amplifier is 0 for "Effect I"
                    continue;
                }
            }
            movement_speed = base_speed * (1.0f + 0.2f * speed_amplifier);
        }

        Position current_position;
        do
        {
            // Wait until we are on the ground or climbing
            const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            while (!local_player->GetOnGround() && !local_player->GetIsClimbing())
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 2000)
                {
                    LOG_WARNING("Timeout waiting for the bot to land on the floor between two block move. Staying at " << local_player->GetPosition());
                    return Status::Failure;
                }
                client.Yield();
            }

            // Get the position, we add 0.25 to Y in case we are at X.97 instead of X+1
            current_position = Position(
                static_cast<int>(std::floor(local_player->GetPosition().x)),
                static_cast<int>(std::floor(local_player->GetPosition().y + 0.25)),
                static_cast<int>(std::floor(local_player->GetPosition().z))
            );

            std::vector<Position> path;
            bool is_goal_loaded;
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                is_goal_loaded = world->IsLoaded(goal);
            }

            const int current_diff_xz = std::abs(goal.x - current_position.x) + std::abs(goal.z - current_position.z);
            const int current_diff = current_diff_xz + std::abs(goal.y - current_position.y);
            // Path finding step
            if (!is_goal_loaded)
            {
                LOG_INFO('[' << client.GetNetworkManager()->GetMyName() << "] Current goal position " << goal << " is either air or not loaded, trying to get closer to load the chunk");
                Vector3<double> goal_direction(goal.x - current_position.x, goal.y - current_position.y, goal.z - current_position.z);
                goal_direction.Normalize();
                path = FindPath(client, current_position,
                    current_position + Position(
                        static_cast<int>(goal_direction.x * 32.0),
                        static_cast<int>(goal_direction.y * 32.0),
                        static_cast<int>(goal_direction.z * 32.0)
                    ), dist_tolerance, min_end_dist, min_end_dist_xz, allow_jump);
            }
            else
            {
                if (dist_tolerance && current_diff <= dist_tolerance && current_diff >= min_end_dist && current_diff_xz >= min_end_dist_xz)
                {
                    return Status::Success;
                }
                path = FindPath(client, current_position, goal, dist_tolerance, min_end_dist, min_end_dist_xz, allow_jump);
            }

            if (path.size() == 0 || path.back() == current_position)
            {
                if (!dist_tolerance && current_diff > 0)
                {
                    LOG_WARNING("Pathfinding cannot find a better position than " << current_position << " (asked " << goal << "). Staying there.");
                    return Status::Failure;
                }
                else if (!dist_tolerance)
                {
                    return Status::Success;
                }
                else
                {
                    return current_diff <= dist_tolerance ? Status::Success : Status::Failure;
                }
            }
            // To avoid going back and forth two positions that are at the same distance of an unreachable goal
            else if (current_diff >= min_end_dist && current_diff_xz >= min_end_dist_xz && std::abs(goal.x - path.back().x) + std::abs(goal.y - path.back().y) + std::abs(goal.z - path.back().z) >= current_diff)
            {
                LOG_WARNING("Pathfinding cannot find a better position than " << current_position << " (asked " << goal << "). Staying there.");
                return Status::Failure;
            }

            for (int i = 0; i < path.size(); ++i)
            {
                // Basic verification to check we won't try to walk on air.
                // If so, it means some blocks have changed, better to
                // recompute a new path
                {
                    std::lock_guard<std::mutex> lock(world->GetMutex());
                    const Block* next_target = world->GetBlock(path[i]);
                    const Block* below = world->GetBlock(path[i] + Position(0, -1, 0));
                    if ((next_target == nullptr || (!next_target->GetBlockstate()->IsClimbable() && !next_target->GetBlockstate()->IsFluid())) &&
                        (below == nullptr || below->GetBlockstate()->IsAir()))
                    {
                        break;
                    }
                }
                const bool succeeded = Move(client, local_player, path[i], movement_speed, 0.5f * movement_speed);

                // If something went wrong, break and
                // replan the whole path to the goal
                if (!succeeded)
                {
                    break;
                }
                // Otherwise just update current position for
                // next move
                else
                {
                    std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                    // Get the position, we add 0.25 to Y in case we are at X.97 instead of X+1
                    current_position = Position(
                        static_cast<int>(std::floor(local_player->GetPosition().x)),
                        static_cast<int>(std::floor(local_player->GetPosition().y + 0.25)),
                        static_cast<int>(std::floor(local_player->GetPosition().z))
                    );
                }
            }
        } while (current_position != goal);

        return Status::Success;
    }

    Status GoTo(BehaviourClient& client, const Position& goal, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const float speed, const bool allow_jump)
    {
        constexpr std::array variable_names = {
            "GoTo.goal",
            "GoTo.dist_tolerance",
            "GoTo.min_end_dist",
            "GoTo.min_end_dist_xz",
            "GoTo.speed",
            "GoTo.allow_jump"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<Position>(variable_names[0], goal);
        blackboard.Set<int>(variable_names[1], dist_tolerance);
        blackboard.Set<int>(variable_names[2], min_end_dist);
        blackboard.Set<int>(variable_names[3], min_end_dist_xz);
        blackboard.Set<float>(variable_names[4], speed);
        blackboard.Set<bool>(variable_names[5], allow_jump);

        return GoToImpl(client, goal, dist_tolerance, min_end_dist, min_end_dist_xz, speed, allow_jump);
    }

    Status GoToBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "GoTo.goal",
            "GoTo.dist_tolerance",
            "GoTo.min_end_dist",
            "GoTo.min_end_dist_xz",
            "GoTo.speed",
            "GoTo.allow_jump"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const Position& goal = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const int dist_tolerance = blackboard.Get(variable_names[1], 0);
        const int min_end_dist = blackboard.Get(variable_names[2], 0);
        const int min_end_dist_xz = blackboard.Get(variable_names[3], 0);
        const float speed = blackboard.Get(variable_names[4], 0.0f);
        const bool allow_jump = blackboard.Get(variable_names[5], true);

        return GoToImpl(client, goal, dist_tolerance, min_end_dist, min_end_dist_xz, speed, allow_jump);
    }


    Status LookAtImpl(BehaviourClient& client, const Vector3<double>& target, const bool set_pitch)
    {
        std::shared_ptr<ProtocolCraft::ServerboundMovePlayerPacketRot> rot = std::make_shared<ProtocolCraft::ServerboundMovePlayerPacketRot>();
        {
            std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
            std::lock_guard<std::mutex> lock_player(local_player->GetMutex());
            local_player->LookAt(target, set_pitch);
            rot->SetOnGround(local_player->GetOnGround());
            rot->SetYRot(local_player->GetYaw());
            rot->SetXRot(local_player->GetPitch());
        }
        std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();
        network_manager->Send(rot);

        return Status::Success;
    }

    Status LookAt(BehaviourClient& client, const Vector3<double>& target, const bool set_pitch)
    {
        const std::array variable_names = {
            "LookAt.target",
            "LookAt.set_pitch"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<Vector3<double>>(variable_names[0], target);
        blackboard.Set<bool>(variable_names[1], set_pitch);

        return LookAtImpl(client, target, set_pitch);
    }

    Status LookAtBlackboard(BehaviourClient& client)
    {
        const std::array variable_names = {
            "LookAt.target",
            "LookAt.set_pitch"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const Vector3<double>& target = blackboard.Get<Vector3<double>>(variable_names[0]);

        // Optional
        const bool set_pitch = blackboard.Get(variable_names[1], true);

        return LookAtImpl(client, target, set_pitch);
    }


    Status StartSprinting(BehaviourClient& client)
    {
        if (client.GetEntityManager()->GetLocalPlayer()->GetIsRunning())
        {
            return Status::Success;
        }

        client.GetEntityManager()->GetLocalPlayer()->SetIsRunning(true);

        std::shared_ptr<ProtocolCraft::ServerboundPlayerCommandPacket> player_command = std::make_shared<ProtocolCraft::ServerboundPlayerCommandPacket>();
        player_command->SetAction(3); // 3 is start sprinting
        player_command->SetId_(client.GetEntityManager()->GetLocalPlayer()->GetEntityID());
        player_command->SetData(0);

        client.GetNetworkManager()->Send(player_command);

        return Status::Success;
    }

    Status StopSprinting(BehaviourClient& client)
    {
        if (!client.GetEntityManager()->GetLocalPlayer()->GetIsRunning())
        {
            return Status::Success;
        }

        client.GetEntityManager()->GetLocalPlayer()->SetIsRunning(false);

        std::shared_ptr<ProtocolCraft::ServerboundPlayerCommandPacket> player_command = std::make_shared<ProtocolCraft::ServerboundPlayerCommandPacket>();
        player_command->SetAction(4); // 4 is stop sprinting
        player_command->SetId_(client.GetEntityManager()->GetLocalPlayer()->GetEntityID());
        player_command->SetData(0);

        client.GetNetworkManager()->Send(player_command);

        return Status::Success;
    }
}
