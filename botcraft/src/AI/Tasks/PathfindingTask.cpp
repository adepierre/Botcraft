#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"

#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/MiscUtilities.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"

#define PI 3.14159265359

namespace Botcraft
{
    class PathfindingBlockstate
    {
    public:
        PathfindingBlockstate() = default;
        PathfindingBlockstate(const Blockstate* block, const Position& pos, const bool take_damage) : block(block)
        {
            height = pos.y;
            if (block == nullptr)
            {
                empty = true;
                return;
            }
            empty = false;

            if (take_damage && block->IsHazardous())
            {
                hazardous = true;
                return;
            }

            if (block->IsFluidOrWaterlogged() && !block->IsSolid())
            {
                climbable = true;
                fluid = true;
                return;
            }

            if (block->IsClimbable())
            {
                climbable = true;
                return;
            }

            if (block->IsSolid())
            {
                solid = true;
                const auto& colliders = block->GetCollidersAtPos(pos);
                for (const auto& c : colliders)
                {
                    height = std::max(static_cast<float>(c.GetMax().y), height);
                }
            }
            else
            {
                empty = true;
            }
        }

        const Blockstate* GetBlockstate() const { return block; }
        bool IsEmpty() const { return empty; }
        bool IsSolid() const { return solid; }
        bool IsHazardous() const { return hazardous; }
        bool IsClimbable() const { return climbable; }
        bool IsFluid() const { return fluid; }
        float GetHeight() const { return height; }

    private:
        const Blockstate* block = nullptr;
        bool empty = true;
        bool solid = false;
        bool hazardous = false;
        bool climbable = false;
        bool fluid = false;
        float height = 0.0f;
    };

    std::vector<Position> FindPath(const BehaviourClient& client, const Position& start, const Position& end, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const bool allow_jump)
    {
        struct PathNode
        {
            Position pos; // Block in which the feet are
            float height; // y height of feet
            float score; // distance from start + heuristic to goal
            PathNode(const Position& p, const float h, const float s)
            {
                pos = p;
                height = h;
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

        const bool takes_damage = !client.GetLocalPlayer()->GetInvulnerable();
        std::shared_ptr<World> world = client.GetWorld();
        const Blockstate* block = world->GetBlock(start);
        nodes_to_explore.emplace(PathNode(start, PathfindingBlockstate(block, start, takes_damage).GetHeight(), 0.0f));
        came_from[start] = start;
        cost[start] = 0.0f;

        int count_visit = 0;
        // We found one location matching all the criterion, but
        // continue the search to see if we can find a better one
        bool suitable_location_found = false;
        // We found a path to the desired goal
        bool end_reached = false;

        bool end_is_inside_solid = false;
        block = world->GetBlock(end);
        end_is_inside_solid = block != nullptr && block->IsSolid();

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
            std::array<PathfindingBlockstate, 6> vertical_surroundings;

            // Assuming the player is standing on 3 (feeet on 2 and head on 1)
            // 0
            // 1
            // 2
            // 3
            // 4
            // 5
            Position pos = current_node.pos + Position(0, 2, 0);
            block = world->GetBlock(pos);
            vertical_surroundings[0] = PathfindingBlockstate(block, pos, takes_damage);
            pos = current_node.pos + Position(0, 1, 0);
            block = world->GetBlock(pos);
            vertical_surroundings[1] = PathfindingBlockstate(block, pos, takes_damage);
            // Current feet block
            pos = current_node.pos;
            block = world->GetBlock(pos);
            vertical_surroundings[2] = PathfindingBlockstate(block, pos, takes_damage);

            // if 2 is solid or hazardous, no down pathfinding is possible,
            // so we can skip a few checks
            if (!vertical_surroundings[2].IsSolid() && !vertical_surroundings[2].IsHazardous())
            {
                // if 3 is solid or hazardous, no down pathfinding is possible,
                // so we can skip a few checks
                pos = current_node.pos + Position(0, -1, 0);
                block = world->GetBlock(pos);
                vertical_surroundings[3] = PathfindingBlockstate(block, pos, takes_damage);

                // If we can move down, we need 4 and 5
                if (!vertical_surroundings[3].IsSolid() && !vertical_surroundings[3].IsHazardous())
                {
                    pos = current_node.pos + Position(0, -2, 0);
                    block = world->GetBlock(pos);
                    vertical_surroundings[4] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = current_node.pos + Position(0, -3, 0);
                    block = world->GetBlock(pos);
                    vertical_surroundings[5] = PathfindingBlockstate(block, pos, takes_damage);
                }
            }


            // Check all vertical cases that would allow the bot to pass
            // -
            // x
            // ^
            // ?
            // ?
            // ?
            if (vertical_surroundings[2].IsClimbable()
                && !vertical_surroundings[1].IsSolid()
                && !vertical_surroundings[1].IsHazardous()
                && !vertical_surroundings[0].IsSolid()
                && !vertical_surroundings[0].IsHazardous()
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
                    nodes_to_explore.emplace(PathNode(new_pos, new_pos.y, new_cost + PathNode::Heuristic(new_pos, end)));
                    came_from[new_pos] = current_node.pos;
                }
            }

            // -
            // ^
            // x
            // o
            // ?
            // ?
            if (vertical_surroundings[1].IsClimbable()
                && !vertical_surroundings[0].IsSolid()
                && !vertical_surroundings[0].IsHazardous()
                && (vertical_surroundings[2].IsSolid() || // we stand on top of 2
                    (!vertical_surroundings[2].IsClimbable() && vertical_surroundings[3].IsSolid()) // if not, it means we stand on 3. Height difference check is not necessary, as the feet are in 2, we know 3 is at least 1 tall
                   )
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
                    nodes_to_explore.emplace(PathNode(new_pos, new_pos.y, new_cost + PathNode::Heuristic(new_pos, end)));
                    came_from[new_pos] = current_node.pos;
                }
            }

            // ?
            // x
            //  
            // -
            // ?
            // ?
            if (!vertical_surroundings[2].IsSolid() &&
                vertical_surroundings[3].IsClimbable()
                )
            {
                const float new_cost = cost[current_node.pos] + 1.0f;
                const Position new_pos = current_node.pos + Position(0, -1, 0);
                auto it = cost.find(new_pos);
                // If we don't already know this node with a better path, add it
                if (it == cost.end() ||
                    new_cost < it->second)
                {
                    cost[new_pos] = new_cost;
                    nodes_to_explore.emplace(PathNode(new_pos, new_pos.y, new_cost + PathNode::Heuristic(new_pos, end)));
                    came_from[new_pos] = current_node.pos;
                }
            }

            // ?
            // x
            //  
            // -
            //  
            // o
            if (!vertical_surroundings[2].IsSolid() &&
                vertical_surroundings[3].IsClimbable()
                && vertical_surroundings[4].IsEmpty()
                && !vertical_surroundings[5].IsEmpty()
                && !vertical_surroundings[5].IsHazardous()
                )
            {
                const bool above_block = vertical_surroundings[5].IsClimbable() || vertical_surroundings[5].GetHeight() + 1e-3f > current_node.pos.y - 2;
                const float new_cost = cost[current_node.pos] + 3.0f - 1.0f * above_block;
                const Position new_pos = current_node.pos + Position(0, -3 + 1 * above_block, 0);
                auto it = cost.find(new_pos);
                // If we don't already know this node with a better path, add it
                if (it == cost.end() ||
                    new_cost < it->second)
                {
                    cost[new_pos] = new_cost;
                    // We need to take the max in case bottom block is a wall or a fence
                    nodes_to_explore.emplace(PathNode(
                        new_pos,
                        above_block ? std::max(current_node.pos.y - 2.0f, vertical_surroundings[5].GetHeight()) : vertical_surroundings[5].GetHeight(),
                        new_cost + PathNode::Heuristic(new_pos, end))
                    );
                    came_from[new_pos] = current_node.pos;
                }
            }



            // ?
            // x
            // ^
            //  
            //  
            // o
            if (vertical_surroundings[2].IsClimbable()
                && vertical_surroundings[3].IsEmpty()
                && vertical_surroundings[4].IsEmpty()
                && !vertical_surroundings[5].IsEmpty()
                && !vertical_surroundings[5].IsHazardous()
                )
            {
                const bool above_block = vertical_surroundings[5].IsClimbable() || vertical_surroundings[5].GetHeight() + 1e-3f > current_node.pos.y - 2;
                const float new_cost = cost[current_node.pos] + 3.0f - 1.0f * above_block;
                const Position new_pos = current_node.pos + Position(0, -3 + 1 * above_block, 0);
                auto it = cost.find(new_pos);
                // If we don't already know this node with a better path, add it
                if (it == cost.end() ||
                    new_cost < it->second)
                {
                    cost[new_pos] = new_cost;
                    // We need to take the max in case bottom block is a wall or a fence
                    nodes_to_explore.emplace(PathNode(
                        new_pos,
                        above_block ? std::max(current_node.pos.y - 2.0f, vertical_surroundings[5].GetHeight()) : vertical_surroundings[5].GetHeight(),
                        new_cost + PathNode::Heuristic(new_pos, end))
                    );
                    came_from[new_pos] = current_node.pos;
                }
            }


            // ?
            // x
            //  
            // -
            //  
            //  
            // Special case here, we can drop down
            // if there is a climbable at the bottom
            if (!vertical_surroundings[2].IsSolid() &&
                vertical_surroundings[3].IsClimbable()
                && vertical_surroundings[4].IsEmpty()
                && vertical_surroundings[5].IsEmpty()
                )
            {
                for (int y = -4; current_node.pos.y + y >= world->GetMinY(); --y)
                {
                    pos = current_node.pos + Position(0, y, 0);
                    block = world->GetBlock(pos);

                    if (block != nullptr && block->IsSolid() && !block->IsClimbable())
                    {
                        break;
                    }

                    const PathfindingBlockstate landing_block(block, pos, takes_damage);
                    if (landing_block.IsClimbable())
                    {
                        const float new_cost = cost[current_node.pos] + std::abs(y);
                        const Position new_pos = current_node.pos + Position(0, y + 1, 0);
                        auto it = cost.find(new_pos);
                        // If we don't already know this node with a better path, add it
                        if (it == cost.end() ||
                            new_cost < it->second)
                        {
                            cost[new_pos] = new_cost;
                            nodes_to_explore.emplace(PathNode(new_pos, new_pos.y, new_cost + PathNode::Heuristic(new_pos, end)));
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
                std::array<PathfindingBlockstate, 12> horizontal_surroundings;

                // Assuming the player is standing on v3 (feeet on v2 and head on v1)
                // v0   0   6 --> ?  ?  ?
                // v1   1   7 --> x  ?  ?
                // v2   2   8 --> x  ?  ?
                // v3   3   9 --> ?  ?  ?
                // v4   4  10 --> ?  ?  ?
                // v5   5  11 --> ?  ?  ?

                // if 1 is solid and tall, no horizontal pathfinding is possible,
                // so we can skip a lot of checks
                pos = next_location + Position(0, 2, 0);
                block = world->GetBlock(pos);
                horizontal_surroundings[0] = PathfindingBlockstate(block, pos, takes_damage);
                pos = next_location + Position(0, 1, 0);
                block = world->GetBlock(pos);
                horizontal_surroundings[1] = PathfindingBlockstate(block, pos, takes_damage);
                const bool horizontal_movement =
                    (!horizontal_surroundings[1].IsSolid() || // 1 is not solid
                        (horizontal_surroundings[1].GetHeight() - vertical_surroundings[2].GetHeight() < 1.25 && // or 1 is solid and small
                            !horizontal_surroundings[0].IsSolid() && !horizontal_surroundings[0].IsHazardous())  // and 0 does not prevent standing
                    ) && !horizontal_surroundings[1].IsHazardous();

                // If we can move horizontally, get the full column
                if (horizontal_movement)
                {
                    pos = next_location;
                    block = world->GetBlock(pos);
                    horizontal_surroundings[2] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_location + Position(0, -1, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[3] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_location + Position(0, -2, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[4] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_location + Position(0, -3, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[5] = PathfindingBlockstate(block, pos, takes_damage);
                }

                // You can't make large jumps if your feet are in a climbable block
                // If we can jump, then we need the third column
                if (allow_jump && !vertical_surroundings[2].IsClimbable())
                {
                    pos = next_next_location + Position(0, 2, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[6] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_next_location + Position(0, 1, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[7] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_next_location;
                    block = world->GetBlock(pos);
                    horizontal_surroundings[8] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_next_location + Position(0, -1, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[9] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_next_location + Position(0, -2, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[10] = PathfindingBlockstate(block, pos, takes_damage);
                    pos = next_next_location + Position(0, -3, 0);
                    block = world->GetBlock(pos);
                    horizontal_surroundings[11] = PathfindingBlockstate(block, pos, takes_damage);
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
                if (!horizontal_surroundings[1].IsSolid()
                    && !horizontal_surroundings[1].IsHazardous()
                    && !horizontal_surroundings[2].IsSolid()
                    && !horizontal_surroundings[2].IsHazardous()
                    && !horizontal_surroundings[3].IsEmpty()
                    && !horizontal_surroundings[3].IsHazardous()
                    && (!horizontal_surroundings[3].IsFluid()   // We can't go from above a fluid to above
                        || !vertical_surroundings[3].IsFluid()  // another one to avoid "walking on water"
                        || horizontal_surroundings[2].IsFluid() // except if one or both "leg level" blocks
                        || vertical_surroundings[2].IsFluid())  // are also fluids
                    )
                {
                    const bool above_block = horizontal_surroundings[2].IsClimbable() || horizontal_surroundings[3].IsClimbable() || horizontal_surroundings[3].GetHeight() + 1e-3f > current_node.pos.y;
                    const float new_cost = cost[current_node.pos] + 2.0f - 1.0f * above_block;
                    const Position new_pos = next_location + Position(0, 1 - 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(static_cast<float>(next_location.y), horizontal_surroundings[3].GetHeight()) : std::max(horizontal_surroundings[3].GetHeight(), horizontal_surroundings[4].GetHeight()),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }


                // -  -  ?
                // x  o  ?
                // x  ?  ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (!vertical_surroundings[0].IsSolid()
                    && !vertical_surroundings[0].IsHazardous()
                    && vertical_surroundings[1].IsEmpty()
                    && !vertical_surroundings[2].IsClimbable()
                    && vertical_surroundings[3].IsSolid()
                    && !horizontal_surroundings[0].IsSolid()
                    && !horizontal_surroundings[0].IsHazardous()
                    && !horizontal_surroundings[1].IsEmpty()
                    && !horizontal_surroundings[1].IsHazardous()
                    && horizontal_surroundings[1].GetHeight() - vertical_surroundings[2].GetHeight() < 1.25
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
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            std::max(horizontal_surroundings[1].GetHeight(), horizontal_surroundings[2].GetHeight()), // for the carpet on wall trick
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // -  -  ?
                // x  -  ?
                // x  o  ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (!vertical_surroundings[0].IsSolid()
                    && !vertical_surroundings[0].IsHazardous()
                    && vertical_surroundings[1].IsEmpty()
                    && vertical_surroundings[3].IsSolid()
                    && !horizontal_surroundings[0].IsSolid()
                    && !horizontal_surroundings[0].IsHazardous()
                    && !horizontal_surroundings[1].IsSolid()
                    && !horizontal_surroundings[1].IsHazardous()
                    && !horizontal_surroundings[2].IsEmpty()
                    && !horizontal_surroundings[2].IsHazardous()
                    && horizontal_surroundings[2].GetHeight() - vertical_surroundings[2].GetHeight() < 1.25
                    )
                {
                    const bool above_block = horizontal_surroundings[1].IsClimbable() || horizontal_surroundings[2].IsClimbable() || horizontal_surroundings[2].GetHeight() + 1e-3f > current_node.pos.y + 1;
                    const float new_cost = cost[current_node.pos] + 1.0f + 1.0f * above_block + 0.5f * (horizontal_surroundings[1].IsClimbable() || horizontal_surroundings[2].GetHeight() - vertical_surroundings[2].GetHeight() > 0.5);
                    const Position new_pos = next_location + Position(0, 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(current_node.pos.y + 1.0f, horizontal_surroundings[2].GetHeight()) : std::max(horizontal_surroundings[2].GetHeight(), horizontal_surroundings[3].GetHeight()),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x  -  ?
                // x     ?
                //---    ?
                //    o  ?
                //    ?  ?
                if (!horizontal_surroundings[1].IsSolid()
                    && !horizontal_surroundings[1].IsHazardous()
                    && horizontal_surroundings[2].IsEmpty()
                    && horizontal_surroundings[3].IsEmpty()
                    && !horizontal_surroundings[4].IsEmpty()
                    && !horizontal_surroundings[4].IsHazardous()
                    )
                {
                    const bool above_block = horizontal_surroundings[4].IsClimbable() || horizontal_surroundings[4].GetHeight() + 1e-3f > current_node.pos.y - 1;
                    const float new_cost = cost[current_node.pos] + 3.5f - 1.0f * above_block;
                    const Position new_pos = next_location + Position(0, -2 + 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(current_node.pos.y - 1.0f, horizontal_surroundings[4].GetHeight()) : std::max(horizontal_surroundings[4].GetHeight(), horizontal_surroundings[5].GetHeight()),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x  -  ?
                // x     ?
                //---    ?
                //       ?
                //    o  ?
                if (!horizontal_surroundings[1].IsSolid()
                    && !horizontal_surroundings[1].IsHazardous()
                    && horizontal_surroundings[2].IsEmpty()
                    && horizontal_surroundings[3].IsEmpty()
                    && horizontal_surroundings[4].IsEmpty()
                    && !horizontal_surroundings[5].IsEmpty()
                    && !horizontal_surroundings[5].IsHazardous()
                    )
                {
                    const bool above_block = horizontal_surroundings[5].IsClimbable() || horizontal_surroundings[5].GetHeight() + 1e-3f > current_node.pos.y - 2;
                    const float new_cost = cost[current_node.pos] + 4.5f - 1.0f * above_block;
                    const Position new_pos = next_location + Position(0, -3 + 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(current_node.pos.y - 2.0f, horizontal_surroundings[5].GetHeight()) : horizontal_surroundings[5].GetHeight(), // no carpet on wall check here as we don't have the block below
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
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
                if (!horizontal_surroundings[1].IsSolid()
                    && !horizontal_surroundings[1].IsHazardous()
                    && horizontal_surroundings[2].IsEmpty()
                    && horizontal_surroundings[3].IsEmpty()
                    && horizontal_surroundings[4].IsEmpty()
                    && horizontal_surroundings[5].IsEmpty()
                    )
                {
                    for (int y = -4; next_location.y + y >= world->GetMinY(); --y)
                    {
                        pos = next_location + Position(0, y, 0);
                        block = world->GetBlock(pos);

                        if (block != nullptr && block->IsSolid() && !block->IsClimbable())
                        {
                            break;
                        }

                        const PathfindingBlockstate landing_block(block, pos, takes_damage);
                        if (landing_block.IsClimbable())
                        {
                            const float new_cost = cost[current_node.pos] + std::abs(y) + 1.5f;
                            const Position new_pos = next_location + Position(0, y + 1, 0);
                            auto it = cost.find(new_pos);
                            // If we don't already know this node with a better path, add it
                            if (it == cost.end() ||
                                new_cost < it->second)
                            {
                                cost[new_pos] = new_cost;
                                nodes_to_explore.emplace(PathNode(new_pos, new_pos.y, new_cost + PathNode::Heuristic(new_pos, end)));
                                came_from[new_pos] = current_node.pos;
                            }

                            break;
                        }
                    }
                }

                // If we can't make jumps, don't bother explore the rest
                // of the cases
                if (!allow_jump
                    || vertical_surroundings[0].IsSolid()       // Block above
                    || vertical_surroundings[0].IsHazardous()   // Block above
                    || !vertical_surroundings[1].IsEmpty()      // Block above
                    || vertical_surroundings[2].IsClimbable()   // Feet inside climbable
                    || vertical_surroundings[3].IsFluid()       // "Walking" on fluid
                    || vertical_surroundings[3].IsEmpty()       // Feet on nothing (inside climbable)
                    || horizontal_surroundings[0].IsSolid()     // Block above next column
                    || horizontal_surroundings[0].IsHazardous() // Hazard above next column
                    || !horizontal_surroundings[1].IsEmpty()    // Non empty block in next column, can't jump through it
                    || !horizontal_surroundings[2].IsEmpty()    // Non empty block in next column, can't jump through it
                    || horizontal_surroundings[6].IsSolid()     // Block above nextnext column
                    || horizontal_surroundings[6].IsHazardous() // Hazard above nextnext column
                    )
                {
                    continue;
                }

                /************ BIG JUMP **************/
                // -  -  -
                // x     o
                // x     ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (!horizontal_surroundings[7].IsEmpty()
                    && !horizontal_surroundings[7].IsHazardous()
                    && horizontal_surroundings[7].GetHeight() - vertical_surroundings[2].GetHeight() < 1.25
                    )
                {
                    // 5 > 4.5 as if horizontal_surroundings[3] is solid we prefer to walk then jump instead of big jump
                    // but if horizontal_surroundings[3] is hazardous we can jump over it
                    const float new_cost = cost[current_node.pos] + 5.0f;
                    const Position new_pos = next_next_location + Position(0, 1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            std::max(horizontal_surroundings[7].GetHeight(), horizontal_surroundings[8].GetHeight()), // for the carpet on wall trick
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // -  -  -
                // x      
                // x     o
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (horizontal_surroundings[7].IsEmpty()
                    && !horizontal_surroundings[8].IsEmpty()
                    && !horizontal_surroundings[8].IsHazardous()
                    && horizontal_surroundings[8].GetHeight() - vertical_surroundings[2].GetHeight() < 1.25
                    )
                {
                    const bool above_block = horizontal_surroundings[8].IsClimbable() || horizontal_surroundings[8].GetHeight() + 1e-3f > current_node.pos.y + 1;
                    // 4 > 3.5 as if horizontal_surroundings[3] is solid we prefer to walk then jump instead of big jump
                    // but if horizontal_surroundings[3] is hazardous we can jump over it
                    const float new_cost = cost[current_node.pos] + 3.0f + 1.0f * above_block;
                    const Position new_pos = next_next_location + Position(0, above_block * 1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(current_node.pos.y + 1.0f, horizontal_surroundings[8].GetHeight()) : std::max(horizontal_surroundings[8].GetHeight(), horizontal_surroundings[9].GetHeight()),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // -  -  -
                // x      
                // x      
                //--- ?  o
                //    ?  ?
                //    ?  ?
                if (horizontal_surroundings[7].IsEmpty()
                    && horizontal_surroundings[8].IsEmpty()
                    && !horizontal_surroundings[9].IsEmpty()
                    && !horizontal_surroundings[9].IsHazardous()
                    && horizontal_surroundings[9].GetHeight() - vertical_surroundings[2].GetHeight() < 1.25
                    )
                {
                    const bool above_block = horizontal_surroundings[9].IsClimbable() || horizontal_surroundings[9].GetHeight() + 1e-3f > current_node.pos.y;
                    const float new_cost = cost[current_node.pos] + 3.5f - 1.0f * above_block;
                    const Position new_pos = next_next_location + Position(0,  -1 + 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(static_cast<float>(current_node.pos.y), horizontal_surroundings[9].GetHeight()) : std::max(horizontal_surroundings[9].GetHeight(), horizontal_surroundings[10].GetHeight()),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // -  -  -
                // x      
                // x      
                //--- ?   
                //    ?  o
                //    ?  ?
                if (horizontal_surroundings[7].IsEmpty()
                    && horizontal_surroundings[8].IsEmpty()
                    && horizontal_surroundings[9].IsEmpty()
                    && !horizontal_surroundings[10].IsEmpty()
                    && !horizontal_surroundings[10].IsHazardous()
                    )
                {
                    const bool above_block = horizontal_surroundings[10].IsClimbable() || horizontal_surroundings[10].GetHeight() + 1e-3f > current_node.pos.y - 1;
                    const float new_cost = cost[current_node.pos] + 4.5f - 1.0f * above_block;
                    const Position new_pos = next_next_location + Position(0, -2 + 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(current_node.pos.y - 1.0f, horizontal_surroundings[10].GetHeight()) : std::max(horizontal_surroundings[10].GetHeight(), horizontal_surroundings[11].GetHeight()),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // -  -  -
                // x      
                // x      
                //--- ?   
                //    ?   
                //    ?  o
                if (horizontal_surroundings[7].IsEmpty()
                    && horizontal_surroundings[8].IsEmpty()
                    && horizontal_surroundings[9].IsEmpty()
                    && horizontal_surroundings[10].IsEmpty()
                    && !horizontal_surroundings[11].IsEmpty()
                    && !horizontal_surroundings[11].IsHazardous()
                    )
                {
                    const bool above_block = horizontal_surroundings[11].IsClimbable() || horizontal_surroundings[11].GetHeight() + 1e-3f > current_node.pos.y - 2;
                    const float new_cost = cost[current_node.pos] + 6.5f - 1.0f * above_block;
                    const Position new_pos = next_next_location + Position(0, -3 + 1 * above_block, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(
                            new_pos,
                            above_block ? std::max(current_node.pos.y - 2.0f, horizontal_surroundings[11].GetHeight()) : horizontal_surroundings[1].GetHeight(),
                            new_cost + PathNode::Heuristic(new_pos, end))
                        );
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

        // There were no node respecting the criteria in the search,
        // this might mean we reached search limit
        // Take closest node to the goal in this case
        if (best_dist == std::numeric_limits<int>::max())
        {
            for (auto it = came_from.begin(); it != came_from.end(); ++it)
            {
                const Position diff = it->first - end;
                const int d_xz = std::abs(diff.x) + std::abs(diff.z);
                const int d = d_xz + std::abs(diff.y);
                const Position diff_start = it->first - start;
                const int d_start = std::abs(diff_start.x) + std::abs(diff_start.y) + std::abs(diff_start.z);
                if (d < best_dist || (d == best_dist && d_start < best_dist_start))
                {
                    best_dist = d;
                    best_dist_start = d_start;
                    it_end_path = it;
                }
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

    // a75f87e0-0583-435b-847a-cf0c18ede2d1
    static constexpr std::array<unsigned char, 16> botcraft_pathfinding_speed_uuid = {
        0xA7, 0x5F, 0x87, 0xE0,
        0x05, 0x83,
        0x43, 0x5B,
        0x84, 0x7A,
        0xCF, 0x0C, 0x18, 0xED, 0xE2, 0xD1
    };

    bool Move(BehaviourClient& client, std::shared_ptr<LocalPlayer>& local_player, const Position& target_pos, const float speed_factor, const bool sprint)
    {
        const Vector3<double> target_position(target_pos.x + 0.5, target_pos.y, target_pos.z + 0.5);
        const Vector3<double> look_at_target = target_position + Vector3<double>(0.0, local_player->GetEyeHeight(), 0.0);
        const Vector3<double> motion_vector = target_position - local_player->GetPosition();
        const double half_player_width = 0.5 * local_player->GetWidth();
        const Vector3<double> horizontal_target_position(target_position.x, 0.0, target_position.z);

        std::shared_ptr<World> world = client.GetWorld();

        if (speed_factor != 1.0f)
        {
            local_player->SetAttributeModifier(
                EntityAttribute::Type::MovementSpeed,
                botcraft_pathfinding_speed_uuid,
                EntityAttribute::Modifier{
                    speed_factor - 1.0f, // -1 as MultiplyTotal will multiply by (1.0 + x)
                    EntityAttribute::Modifier::Operation::MultiplyTotal
                });
        }
        Utilities::OnEndScope botcraft_speed_modifier_remover([&]() {
            local_player->RemoveAttributeModifier(EntityAttribute::Type::MovementSpeed, botcraft_pathfinding_speed_uuid);
        });

        local_player->LookAt(look_at_target, true);

        // Move horizontally (with a jump if necessary)
        if (std::abs(motion_vector.x) > 0.5 || std::abs(motion_vector.z) > 0.5)
        {
            // If we need to jump
            if (motion_vector.y > 0.5 || std::abs(motion_vector.x) > 1.5 || std::abs(motion_vector.z) > 1.5)
            {
                // If not a jump above a gap, wait until reaching the next Y value before moving X/Z
                if (std::abs(motion_vector.x) < 1.5 && std::abs(motion_vector.z) < 1.5)
                {
                    local_player->SetInputsJump(true);

                    if (!Utilities::YieldForCondition([&]() -> bool
                        {
                            return local_player->GetY() >= target_pos.y;
                        }, client, 2000))
                    {
                        return false;
                    }
                }
                // It's a long jump above a gap
                else
                {
                    const Vector3<double> current_block_center_xz(
                        std::floor(local_player->GetX()) + 0.5,
                        0.0,
                        std::floor(local_player->GetZ()) + 0.5
                    );
                    // Start to move forward to have speed before jumping
                    if (!Utilities::YieldForCondition([&]() -> bool
                        {
                            if (local_player->GetDirtyInputs())
                            {
                                return false;
                            }

                            // We need to add the forward input even for the tick we do the jump
                            local_player->LookAt(look_at_target, false);
                            local_player->SetInputsForward(1.0);
                            local_player->SetInputsSprint(sprint);

                            if (Vector3<double>(local_player->GetX(), 0.0, local_player->GetZ()).SqrDist(current_block_center_xz) > half_player_width * half_player_width)
                            {
                                // Then jump
                                local_player->SetInputsJump(true);
                                return true;
                            }

                            return false;
                        }, client, 1000))
                    {
                        return false;
                    }
                }
            }
            // Move forward to the right X/Z location
            if (!Utilities::YieldForCondition([&]() -> bool
                {
                    if (local_player->GetDirtyInputs())
                    {
                        return false;
                    }

                    const Vector3<double> current_pos = local_player->GetPosition();
                    if (Vector3<double>(current_pos.x, 0.0, current_pos.z).SqrDist(horizontal_target_position) < (0.5 - half_player_width) * (0.5 - half_player_width))
                    {
                        return true;
                    }

                    local_player->LookAt(look_at_target, false);
                    const Vector3<double> speed = local_player->GetSpeed();
                    double forward = 1.0;
                    // If we need to fall, stop accelerating to prevent "overshooting" and potentially
                    // hit some block on the bottom or on the side of the dropshoot
                    if (motion_vector.y < -0.5 &&
                        static_cast<int>(std::floor(current_pos.x)) == target_pos.x &&
                        static_cast<int>(std::floor(current_pos.z)) == target_pos.z)
                    {
                        if (std::max(std::abs(speed.x), std::abs(speed.z)) > 0.12) // 0.12 because I needed a value so why not
                        {
                            forward = -1.0;
                        }
                        else if (std::max(std::abs(speed.x), std::abs(speed.z)) > 0.06)
                        {
                            forward = 0.0;
                        }
                    }
                    local_player->SetInputsForward(forward);
                    local_player->SetInputsSprint(sprint && (forward == 1.0));

                    return false;
                }, client, (std::abs(motion_vector.x) + std::abs(motion_vector.z) + (motion_vector.y < -0.5)) * 1000))
            {
                return false;
            }
        }

        // If we need to go down, let the gravity do it's job, unless we are in a scaffholding or water,
        // in which case we need to press sneak to go down. If free falling in air, press sneak to catch
        // climbable at the bottom, preventing fall damage
        if (local_player->GetY() > target_position.y && !Utilities::YieldForCondition([&]() -> bool
            {
                // Previous inputs have not been processed by physics thread yet
                if (local_player->GetDirtyInputs())
                {
                    return false;
                }

                if (static_cast<int>(std::floor(local_player->GetY())) <= target_pos.y &&
                    (local_player->GetOnGround() || local_player->IsClimbing() || local_player->IsInFluid()))
                {
                    return true;
                }

                const Vector3<double> current_pos = local_player->GetPosition();
                const Blockstate* feet_block = world->GetBlock(Position(
                    static_cast<int>(std::floor(current_pos.x)),
                    static_cast<int>(std::floor(current_pos.y)),
                    static_cast<int>(std::floor(current_pos.z))
                ));
                local_player->SetInputsSneak(feet_block != nullptr &&
                    (feet_block->IsFluidOrWaterlogged() || feet_block->IsScaffolding() || (feet_block->IsAir() && motion_vector.y < -2.5)));
                local_player->SetInputsJump(local_player->GetFlying()); // Stop flying

                // If we drifted too much, adjust toward target X/Z position
                if (Vector3<double>(current_pos.x, 0.0, current_pos.z).SqrDist(horizontal_target_position) > (0.5 - half_player_width) * (0.5 - half_player_width))
                {
                    local_player->LookAt(look_at_target, false);
                    local_player->SetInputsForward(1.0);
                }

                return false;
            }, client, 1000 + 1000 * std::abs(motion_vector.y)))
        {
            return false;
        }

        // We need to go up (either from ground or in a climbable/water)
        if (local_player->GetY() < target_position.y && !Utilities::YieldForCondition([&]() -> bool
            {
                // Previous inputs have not been processed by physics thread yet
                if (local_player->GetDirtyInputs())
                {
                    return false;
                }

                const Vector3<double> current_pos = local_player->GetPosition();
                if (static_cast<int>(std::floor(current_pos.y)) >= target_pos.y)
                {
                    return true;
                }

                local_player->SetInputsJump(true);

                // If we drifted too much, adjust toward target X/Z position
                if (Vector3<double>(current_pos.x, 0.0, current_pos.z).SqrDist(horizontal_target_position) > (0.5 - half_player_width) * (0.5 - half_player_width))
                {
                    local_player->LookAt(look_at_target, false);
                    local_player->SetInputsForward(1.0);
                }

                return false;
            }, client, 1000 + 1000 * std::abs(motion_vector.y)))
        {
            return false;
        }

        // We are in the target block, make sure we are not a bit too high
        return Utilities::YieldForCondition([&]() -> bool
            {
                if (local_player->GetDirtyInputs())
                {
                    return false;
                }

                // One physics tick climbing down is 0.15 at most, so this should never get too low in theory
                if (local_player->GetY() >= target_position.y && local_player->GetY() - target_position.y < 0.2)
                {
                    return true;
                }

                const Vector3<double> current_pos = local_player->GetPosition();
                const Blockstate* feet_block = world->GetBlock(Position(
                    static_cast<int>(std::floor(current_pos.x)),
                    static_cast<int>(std::floor(current_pos.y)),
                    static_cast<int>(std::floor(current_pos.z))
                ));
                local_player->SetInputsSneak(feet_block != nullptr &&
                    (feet_block->IsFluidOrWaterlogged() || feet_block->IsScaffolding() || (feet_block->IsAir() && motion_vector.y < -2.5)));
                local_player->SetInputsJump(local_player->GetFlying()); // Stop flying

                // If we drifted too much, adjust toward target X/Z position
                if (Vector3<double>(current_pos.x, 0.0, current_pos.z).SqrDist(horizontal_target_position) > (0.5 - half_player_width) * (0.5 - half_player_width))
                {
                    local_player->LookAt(look_at_target, false);
                    local_player->SetInputsForward(1.0);
                }

                return false;
            }, client, 1000);
    }

    // Try to cancel speed while going toward the center of the block
    void AdjustPosSpeed(BehaviourClient& client)
    {
        std::shared_ptr<LocalPlayer> player = client.GetLocalPlayer();
        const Vector3<double> pos = player->GetPosition();
        const Vector3<double> target(
            std::floor(pos.x) + 0.5,
            std::floor(pos.y),
            std::floor(pos.z) + 0.5
        );

        Utilities::YieldForCondition([&]() -> bool
            {
                if (player->GetDirtyInputs())
                {
                    return false;
                }

                const Vector3<double> pos = player->GetPosition();
                const Vector3<double> speed = player->GetSpeed();
                if (std::abs(pos.x - target.x) < 0.2 &&
                    std::abs(pos.z - target.z) < 0.2 &&
                    std::abs(speed.x) < 0.05 &&
                    std::abs(speed.z) < 0.05)
                {
                    return true;
                }

                const float yaw_rad = player->GetYaw() * PI / 180.0;
                const double cos_yaw = std::cos(yaw_rad);
                const double sin_yaw = std::sin(yaw_rad);

                // Project on forward/left axis
                const double delta_forward = (target.z - pos.z) * cos_yaw - (target.x - pos.x) * sin_yaw;
                const double delta_left = (target.x - pos.x) * cos_yaw + (target.z - pos.z) * sin_yaw;
                const double speed_forward = speed.z * cos_yaw - speed.x * sin_yaw;
                const double speed_left = speed.x * cos_yaw + speed.z * sin_yaw;

                // If going too fast, reduce speed
                if (std::abs(speed_forward) > 0.1)
                {
                    player->SetInputsForward(speed_forward > 0.0 ? -1.0 : 1.0);
                }
                // Opposite signs or going toward the same direction but slowly
                else if (delta_forward * speed_forward < 0.0 || std::abs(speed_forward) < 0.02)
                {
                    player->SetInputsForward(delta_forward > 0.0 ? 1.0 : -1.0);
                }
                else
                {
                    player->SetInputsForward(0.0);
                }

                // Same thing on left axis
                if (std::abs(speed_left) > 0.1)
                {
                    player->SetInputsLeft(speed_left > 0.0 ? -1.0 : 1.0);
                }
                else if (delta_left * speed_left < 0.0 || std::abs(speed_left) < 0.02)
                {
                    player->SetInputsLeft(delta_left > 0.0 ? 1.0 : -1.0);
                }
                else
                {
                    player->SetInputsLeft(0.0);
                }

                return false;
            }, client, 1000);
    }

    Status GoToImpl(BehaviourClient& client, const Position& goal, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const bool allow_jump, const bool sprint, float speed_factor)
    {
        if (min_end_dist > dist_tolerance)
        {
            LOG_WARNING("GoTo.min_end_dist should be <= dist_tolerance if you want pathfinding to work as expected");
        }
        if (min_end_dist_xz > dist_tolerance)
        {
            LOG_WARNING("GoTo.min_end_dist_xz should be <= dist_tolerance if you want pathfinding to work as expected");
        }
        if (speed_factor <= 0.0f)
        {
            LOG_WARNING("GoTo.speed_factor should be >0 or the bot won't move. Setting it to default value of 1.0");
            speed_factor = 1.0f;
        }
        std::shared_ptr<LocalPlayer> local_player = client.GetLocalPlayer();

        // Don't bother with pathfinding in spectator mode, directly go to the goal
        if (local_player->GetGameMode() == GameType::Spectator)
        {
            const Vector3<double> target(0.5 + goal.x, 0.5 + goal.y, 0.5 + goal.z);
            const double square_half_width = local_player->GetWidth() * local_player->GetWidth() / 4.0;
            const double dist = std::sqrt((target - local_player->GetPosition()).SqrNorm());
            if (Utilities::YieldForCondition([&]() -> bool
                {
                    if (!local_player->GetDirtyInputs())
                    {
                        local_player->LookAt(target, true);
                        local_player->SetInputsForward(1.0);
                    }

                    return local_player->GetPosition().SqrDist(target) < square_half_width;
                }, client, dist * 1000))
            {
                AdjustPosSpeed(client);
                return Status::Success;
            }
            else
            {
                return Status::Failure;
            }
        }

        if (StopFlying(client) == Status::Failure)
        {
            return Status::Failure;
        }

        std::shared_ptr<World> world = client.GetWorld();
        Position current_position;
        do
        {
            // Wait until we are on the ground or climbing
            const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            while (!local_player->GetOnGround() && !local_player->IsClimbing() && !local_player->IsInFluid())
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
            const bool is_goal_loaded = world->IsLoaded(goal);

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
                    AdjustPosSpeed(client);
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
                    AdjustPosSpeed(client);
                    return Status::Success;
                }
                else
                {
                    if (current_diff <= dist_tolerance)
                    {
                        AdjustPosSpeed(client);
                        return Status::Success;
                    }
                    else
                    {
                        return Status::Failure;
                    }
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
                const Blockstate* next_target = world->GetBlock(path[i]);
                const Blockstate* below = world->GetBlock(path[i] + Position(0, -1, 0));
                if ((next_target == nullptr || (!next_target->IsClimbable() && !next_target->IsFluid())) &&
                    (below == nullptr || below->IsAir()))
                {
                    break;
                }

                // If something went wrong, break and
                // replan the whole path to the goal
                if (!Move(client, local_player, path[i], speed_factor, sprint))
                {
                    break;
                }
                // Otherwise just update current position for
                // next move
                else
                {
                    const Vector3<double> local_player_pos = local_player->GetPosition();
                    // Get the position, we add 0.25 to Y in case we are at X.97 instead of X+1
                    current_position = Position(
                        static_cast<int>(std::floor(local_player_pos.x)),
                        static_cast<int>(std::floor(local_player_pos.y + 0.25)),
                        static_cast<int>(std::floor(local_player_pos.z))
                    );
                }
            }
        } while (current_position != goal);

        AdjustPosSpeed(client);
        return Status::Success;
    }

    Status GoTo(BehaviourClient& client, const Position& goal, const int dist_tolerance, const int min_end_dist, const int min_end_dist_xz, const bool allow_jump, const bool sprint, const float speed_factor)
    {
        constexpr std::array variable_names = {
            "GoTo.goal",
            "GoTo.dist_tolerance",
            "GoTo.min_end_dist",
            "GoTo.min_end_dist_xz",
            "GoTo.allow_jump",
            "GoTo.sprint",
            "GoTo.speed_factor"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<Position>(variable_names[0], goal);
        blackboard.Set<int>(variable_names[1], dist_tolerance);
        blackboard.Set<int>(variable_names[2], min_end_dist);
        blackboard.Set<int>(variable_names[3], min_end_dist_xz);
        blackboard.Set<bool>(variable_names[4], allow_jump);
        blackboard.Set<bool>(variable_names[5], sprint);
        blackboard.Set<float>(variable_names[6], speed_factor);

        return GoToImpl(client, goal, dist_tolerance, min_end_dist, min_end_dist_xz, allow_jump, sprint, speed_factor);
    }

    Status GoToBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "GoTo.goal",
            "GoTo.dist_tolerance",
            "GoTo.min_end_dist",
            "GoTo.min_end_dist_xz",
            "GoTo.allow_jump",
            "GoTo.sprint",
            "GoTo.speed_factor"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const Position& goal = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const int dist_tolerance = blackboard.Get(variable_names[1], 0);
        const int min_end_dist = blackboard.Get(variable_names[2], 0);
        const int min_end_dist_xz = blackboard.Get(variable_names[3], 0);
        const bool allow_jump = blackboard.Get(variable_names[4], true);
        const bool sprint = blackboard.Get(variable_names[5], true);
        const float speed_factor = blackboard.Get(variable_names[6], 1.0f);

        return GoToImpl(client, goal, dist_tolerance, min_end_dist, min_end_dist_xz, allow_jump, sprint, speed_factor);
    }


    Status LookAtImpl(BehaviourClient& client, const Vector3<double>& target, const bool set_pitch)
    {
        std::shared_ptr<LocalPlayer> local_player = client.GetLocalPlayer();
        local_player->LookAt(target, set_pitch);

        std::shared_ptr<ProtocolCraft::ServerboundMovePlayerPacketRot> rot = std::make_shared<ProtocolCraft::ServerboundMovePlayerPacketRot>();
        rot->SetOnGround(local_player->GetOnGround());
        rot->SetYRot(local_player->GetYaw());
        rot->SetXRot(local_player->GetPitch());

        client.GetNetworkManager()->Send(rot);

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

    Status StartFlying(BehaviourClient& client)
    {
        std::shared_ptr<LocalPlayer> local_player = client.GetLocalPlayer();
        if (!local_player->GetMayFly())
        {
            return Status::Failure;
        }

        if (local_player->GetFlying())
        {
            return Status::Success;
        }

        local_player->SetInputsJump(true);
        if (!Utilities::YieldForCondition([&]() -> bool
            {
                return !local_player->GetDirtyInputs();
            }, client, 150))
        {
            return Status::Failure;
        }
        local_player->SetInputsJump(false);
        if (!Utilities::YieldForCondition([&]() -> bool
            {
                return !local_player->GetDirtyInputs();
            }, client, 150))
        {
            return Status::Failure;
        }
        local_player->SetInputsJump(true);
        if (!Utilities::YieldForCondition([&]() -> bool
            {
                return !local_player->GetDirtyInputs();
            }, client, 150))
        {
            return Status::Failure;
        }

        return local_player->GetFlying() ? Status::Success : Status::Failure;
    }

    Status StopFlying(BehaviourClient& client)
    {
        std::shared_ptr<LocalPlayer> local_player = client.GetLocalPlayer();
        if (!local_player->GetFlying())
        {
            return Status::Success;
        }

        local_player->SetInputsJump(true);
        if (!Utilities::YieldForCondition([&]() -> bool
            {
                return !local_player->GetDirtyInputs();
            }, client, 150))
        {
            return Status::Failure;
        }
        local_player->SetInputsJump(false);
        if (!Utilities::YieldForCondition([&]() -> bool
            {
                return !local_player->GetDirtyInputs();
            }, client, 150))
        {
            return Status::Failure;
        }
        local_player->SetInputsJump(true);
        if (!Utilities::YieldForCondition([&]() -> bool
            {
                return !local_player->GetDirtyInputs();
            }, client, 150))
        {
            return Status::Failure;
        }

        return local_player->GetFlying() ? Status::Failure : Status::Success;
    }
}
