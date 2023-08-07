#include <botcraft/AI/Tasks/PathfindingTask.hpp>

#include "WorldEaterUtilities.hpp"


using namespace Botcraft;

std::unordered_set<std::string> SplitString(const std::string& s, const char delimiter)
{
    std::unordered_set<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.insert(token);
    }
    return tokens;
}

bool IdentifyBaseCampLayout(SimpleBehaviourClient& client)
{
    Blackboard& blackboard = client.GetBlackboard();

    const int bot_index = blackboard.Get<int>("Eater.bot_index");

    std::unordered_map<std::string, std::string> block_item_mapping = {
        { "minecraft:red_concrete", "drop" },
        { "minecraft:lime_concrete", "out" },
        { "minecraft:orange_shulker_box", "lava_bucket" },
        { "minecraft:magenta_shulker_box", "shears" },
        { "minecraft:purple_shulker_box", "hoe" },
        { "minecraft:blue_shulker_box", "shovel" },
        { "minecraft:light_blue_shulker_box", "axe" },
        { "minecraft:yellow_shulker_box", "golden_carrots" },
        { "minecraft:brown_shulker_box", "ladder" },
        { "minecraft:black_shulker_box", "temp_block" },
        { "minecraft:cyan_shulker_box", "pickaxe" }
    };

    std::unordered_map<std::string, std::vector<Position>> found_blocks;
    for (const auto& [k, v] : block_item_mapping)
    {
        found_blocks[k] = {};
    }

    std::shared_ptr<World> world = client.GetWorld();
    Position current_position;
    // Loop through all loaded blocks to find the one we are looking for
    for (const auto& [coords, chunk] : world->GetAllChunks())
    {
        for (int y = world->GetMinY(); y < world->GetMinY() + world->GetHeight(); ++y)
        {
            current_position.y = y;
            for (int x = 0; x < CHUNK_WIDTH; ++x)
            {
                current_position.x = coords.first * CHUNK_WIDTH + x;
                for (int z = 0; z < CHUNK_WIDTH; ++z)
                {
                    current_position.z = coords.second * CHUNK_WIDTH + z;
                    const Blockstate* blockstate = nullptr;
                    {
                        std::lock_guard<std::mutex> lock_world(world->GetMutex());
                        const Block* block = world->GetBlock(current_position);
                        if (block != nullptr)
                        {
                            blockstate = block->GetBlockstate();
                        }
                        else
                        {
                            continue;
                        }
                    }

                    if (const auto it = found_blocks.find(blockstate->GetName()); it != found_blocks.end())
                    {
                        it->second.push_back(current_position);
                        if (bot_index == 0)
                        {
                            LOG_INFO(blockstate->GetName() << "(" << block_item_mapping.at(blockstate->GetName()) << ") found at " << current_position);
                        }
                    }
                }
            }
        }
    }

    // Sort all positions in a consistent way for all bots
    for (auto& [_, v] : found_blocks)
    {
        std::sort(v.begin(), v.end(), [&](const Position& a, const Position& b)
            {
                return a.x < b.x ||
                    (a.x == b.x && a.y < b.y) ||
                    (a.x == b.x && a.y == b.y && a.z < b.z);
            });
    }

    // Assign dedicated positions for each bot based on index
    for (const auto& [k, v] : block_item_mapping)
    {
        const std::vector<Position>& positions = found_blocks.at(k);
        if (positions.size() == 0)
        {
            if (bot_index == 0)
            {
                LOG_ERROR("Can't find any " << k << ". I can't work without " << v);
            }
            return false;
        }
        blackboard.Set<Position>("Eater." + v + "_position", positions[bot_index % positions.size()]);
    }

    return true;
}

std::unordered_set<Position> CollectBlocks(const std::shared_ptr<World> world, const Position& start, const Position& end, const int layer, const bool fluids, const bool solids)
{
    std::unordered_set<Position> output;
    Position p(0, layer, 0);
    for (int x = start.x; x <= end.x; ++x)
    {
        p.x = x;
        for (int z = start.z; z <= end.z; ++z)
        {
            p.z = z;
            std::scoped_lock<std::mutex> lock(world->GetMutex());
            const Block* block = world->GetBlock(p);
            const Blockstate* blockstate = block == nullptr ? nullptr : block->GetBlockstate();
            if (block && !blockstate->IsAir() &&
                // For fluids, we are not interested in the corner blocks as they can't "leak" into the working area
                ((fluids && (blockstate->IsFluid() || blockstate->IsWaterlogged()) && ((x != start.x && x != end.x) || (z != start.z && z != end.z))) ||
                    (solids && blockstate->IsSolid()) ||
                    (!fluids && !solids && (!blockstate->IsFluid() || blockstate->IsHazardous()) && !blockstate->IsWaterlogged() && (!blockstate->IsSolid() || blockstate->IsHazardous()))
                ))
            {
                output.insert(Position(x, layer, z));
            }
        }
    }
    return output;
}

std::vector<std::unordered_set<Position>> GroupBlocksInComponents(const Position& start, const Position& end, const Position& start_point, const BehaviourClient& client, const std::unordered_set<Position>& positions, std::unordered_map<Position, std::unordered_set<Position>>* additional_neighbours)
{
    std::vector<std::unordered_set<Position>> components;

    std::unordered_map<Position, int> components_index;
    for (const Position& b : positions)
    {
        components_index[b] = -1;
    }

    // For all block elements
    for (const auto& p : positions)
    {
        // If we already set a component to this position, skip it
        if (components_index[p] != -1)
        {
            continue;
        }
        // Otherwise add all neighbours we can find to the current component
        std::unordered_set<Position> current_component;
        std::unordered_set<Position> neighbours = { p };
        while (neighbours.size() > 0)
        {
            // Take first element in current neighbours
            const Position current_pos = *neighbours.begin();
            neighbours.erase(current_pos);

            // This neighbour is already in a component
            if (components_index[current_pos] != -1)
            {
                continue;
            }

            current_component.insert(current_pos);
            components_index[current_pos] = components.size();

            if (current_pos.x > start.x)
            {
                const Position west = current_pos + Position(-1, 0, 0);
                if (const auto it = components_index.find(west); it != components_index.end() && it->second == -1)
                {
                    neighbours.insert(west);
                }
            }
            if (current_pos.x < end.x)
            {
                const Position east = current_pos + Position(1, 0, 0);
                if (const auto it = components_index.find(east); it != components_index.end() && it->second == -1)
                {
                    neighbours.insert(east);
                }
            }
            if (current_pos.z > start.z)
            {
                const Position north = current_pos + Position(0, 0, -1);
                if (const auto it = components_index.find(north); it != components_index.end() && it->second == -1)
                {
                    neighbours.insert(north);
                }
            }
            if (current_pos.z < end.z)
            {
                const Position south = current_pos + Position(0, 0, 1);
                if (const auto it = components_index.find(south); it != components_index.end() && it->second == -1)
                {
                    neighbours.insert(south);
                }
            }
        }

        if (current_component.size() == 0)
        {
            continue;
        }

        // If additional neighbours are not asked, don't try to merge
        // components using pathfinding
        if (additional_neighbours == nullptr)
        {
            components.push_back(current_component);
            continue;
        }
        // Check if we can pathfind from one of the previous components
        // to this one and merge them if we can
        bool merged = false;
        for (size_t i = 0; i < components.size(); ++i)
        {
            const Position pathfinding_start = *components[i].begin() + Position(0, 1, 0);
            const Position pathfinding_end = *current_component.begin() + Position(0, 1, 0);
            const std::vector<Position> path = FindPath(client, pathfinding_start, pathfinding_end, 0, 0, false, true);
            const std::vector<Position> reversed_path = FindPath(client, pathfinding_end, pathfinding_start, 0, 0, false, true);
            // If we can pathfind from start to end (both ways to prevent cliff falls that would only allow one-way travel)
            if (path.back() == pathfinding_end && reversed_path.back() == pathfinding_start)
            {
                merged = true;
                // Add link between the two components as non adjacent neighbours
                Position path_block_component1 = pathfinding_start + Position(0, -1, 0);
                for (size_t j = 0; j < path.size(); ++j)
                {
                    // If the pathfinding crosses the boundaries of the work area anywhere else than the ladder,
                    // cancel the merging of the components
                    if ((path[j].x < start.x || path[j].x > end.x || path[j].z < start.z || path[j].z > end.z) &&
                        path[j].x != start_point.x && path[j].z != start_point.z)
                    {
                        merged = false;
                        break;
                    }

                    if (additional_neighbours != nullptr)
                    {
                        // If component index of the current path position is equal to the one currently compared to (i)
                        auto it = components_index.find(path[j] + Position(0, -1, 0));
                        if (it != components_index.end() && it->second == i)
                        {
                            path_block_component1 = path[j] + Position(0, -1, 0);
                        }
                    }
                }
                Position path_block_component2 = pathfinding_end + Position(0, -1, 0);
                for (size_t j = 0; j < reversed_path.size(); ++j)
                {
                    // If the pathfinding crosses the boundaries of the work area anywhere else than the ladder,
                    // cancel the merging of the components
                    if ((reversed_path[j].x < start.x || reversed_path[j].x > end.x || reversed_path[j].z < start.z || reversed_path[j].z > end.z) &&
                        reversed_path[j].x != start_point.x && reversed_path[j].z != start_point.z)
                    {
                        merged = false;
                        break;
                    }

                    if (additional_neighbours != nullptr)
                    {
                        // If component index of the current path position is equal to the current one to add (components.size())
                        auto it = components_index.find(reversed_path[j] + Position(0, -1, 0));
                        if (it != components_index.end() && it->second == components.size())
                        {
                            path_block_component2 = reversed_path[j] + Position(0, -1, 0);
                        }
                    }
                }
                if (merged)
                {
                    for (const Position& p : current_component)
                    {
                        components_index[p] = i;
                    }
                    components[i].insert(current_component.begin(), current_component.end());
                    if (additional_neighbours != nullptr)
                    {
                        (*additional_neighbours)[path_block_component1].insert(path_block_component2);
                        (*additional_neighbours)[path_block_component2].insert(path_block_component1);
                    }
                }
            }
        }
        if (!merged)
        {
            components.push_back(current_component);
        }
    }
    return components;
}

std::vector<Position> GetBlocksToAdd(const std::vector<std::unordered_set<Position>>& components, const Position& start_point, const Position& min_bound, const Position& max_bound)
{
    if (components.empty())
    {
        return {};
    }

    std::unordered_set<int> components_already_processed = { -1 };
    std::unordered_set<int> components_to_process;

    // Add all components to "to_process" vector
    for (int i = 0; i < components.size(); ++i)
    {
        components_to_process.insert(i);
    }

    std::vector<Position> output;
    output.reserve(components_to_process.size()); // rough estimate of ~1:1 ratio block present/block to add
    while (components_to_process.size() > 0)
    {
        float min_dist = std::numeric_limits<float>::max();
        int argmin_component_idx = -1;
        Position from;
        Position to;

        // Look for the "closest" remaining component
        // from the one we already have
        for (const int c1 : components_already_processed)
        {
            for (const int c2 : components_to_process)
            {
                for (const Position& p1 : c1 != -1 ? components[c1] : std::unordered_set<Position>{ start_point })
                {
                    for (const Position& p2 : components[c2])
                    {
                        const float dist = std::abs(p1.x - p2.x) + std::abs(p1.z - p2.z);
                        if (dist < min_dist)
                        {
                            min_dist = dist;
                            argmin_component_idx = c2;
                            from = p1;
                            to = p2;
                        }
                    }
                }
            }
        }

        // Straight line to get back into the working area
        // as quickly as possible
        while (from != to && (
            from.x < min_bound.x ||
            from.x > max_bound.x ||
            from.z < min_bound.z ||
            from.z > max_bound.z))
        {
            if (from.x < min_bound.x)
            {
                from.x += 1;
            }
            else if (from.z < min_bound.z)
            {
                from.z += 1;
            }
            else if (from.x > max_bound.x)
            {
                from.x -= 1;
            }
            else if (from.z > max_bound.z)
            {
                from.z -= 1;
            }
            if (from != to)
            {
                output.push_back(from);
            }
        }

        // Dumb 2D staircase between from and to
        while (from != to)
        {
            if (std::abs(to.x - from.x) > std::abs(to.z - from.z))
            {
                from.x += from.x < to.x ? 1 : -1;
            }
            else
            {
                from.z += from.z < to.z ? 1 : -1;
            }
            if (from != to)
            {
                output.push_back(from);
            }
        }
        components_already_processed.insert(argmin_component_idx);
        // Remove start point after first time
        components_already_processed.erase(-1);
        components_to_process.erase(argmin_component_idx);
    }

    return output;
}

std::unordered_set<Position> FlattenComponentsAndAdditionalBlocks(const std::vector<std::unordered_set<Position>>& components, const std::vector<Position>& additional_blocks)
{
    std::unordered_set<Position> output;
    for (const std::unordered_set<Position>& v : components)
    {
        output.insert(v.begin(), v.end());
    }
    output.insert(additional_blocks.begin(), additional_blocks.end());
    return output;
}

std::vector<Position> ComputeBlockOrder(std::unordered_set<Position> blocks, const Position& start_block, const Direction orientation, const std::unordered_map<Position, std::unordered_set<Position>>& additional_neighbours)
{
    struct SortingNode
    {
        Position pos;
        std::vector<SortingNode> children;
    };

    // Should not happen as at least start_block should be in blocks
    if (blocks.size() == 0)
    {
        return { };
    }
    blocks.erase(start_block);

    SortingNode root{ start_block };

    std::queue<SortingNode*> to_process;
    to_process.push(&root);

    std::array<Position, 4> potential_neighbours;
    
    if (orientation == Direction::East || orientation == Direction::West)
    {
        potential_neighbours = {
            Position(-1, 0, 0),   // west
            Position(1, 0, 0),    // east
            Position(0, 0, -1),   // north
            Position(0, 0, 1)     // south
        };
    }
    else
    {
        potential_neighbours = {
            Position(0, 0, -1),   // north
            Position(0, 0, 1),    // south
            Position(-1, 0, 0),   // west
            Position(1, 0, 0)     // east
        };
    }
    

    while (blocks.size() > 0)
    {
        if (to_process.empty())
        {
            LOG_ERROR("to_process queue empty while ordering blocks to process. This should not happen (?)");
            return {};
        }
        SortingNode* current_node = to_process.front();

        // If there are some additional neighbours to this node, check them and the direct neighbours
        if (const auto it = additional_neighbours.find(current_node->pos); it != additional_neighbours.end())
        {
            for (const Position& potential_neighbour : it->second)
            {
                if (blocks.find(potential_neighbour) != blocks.end())
                {
                    SortingNode neighbour;
                    neighbour.pos = potential_neighbour;
                    current_node->children.emplace_back(neighbour);
                }
            }
            for (const Position& offset : potential_neighbours)
            {
                const Position potential_neighbour = current_node->pos + offset;
                // Only add it if it's in blocks AND we didn't already added it as a potential neighbour
                if (blocks.find(potential_neighbour) != blocks.end() && it->second.find(potential_neighbour) == it->second.end())
                {
                    SortingNode neighbour;
                    neighbour.pos = potential_neighbour;
                    current_node->children.emplace_back(neighbour);
                }
            }
        }
        // Else only check the direct neighbours
        else
        {
            for (const Position& offset : potential_neighbours)
            {
                const Position potential_neighbour = current_node->pos + offset;
                if (blocks.find(potential_neighbour) != blocks.end())
                {
                    SortingNode neighbour;
                    neighbour.pos = potential_neighbour;
                    current_node->children.emplace_back(neighbour);
                }
            }
        }

        for (size_t i = 0; i < current_node->children.size(); ++i)
        {
            to_process.push(current_node->children.data() + i);
            blocks.erase(current_node->children[i].pos);
        }
        to_process.pop();
    }

    // Recursive function to add all children, then current node
    // This allows to be sure that we will never "cut the branch
    // we are sitting on" preventing getting back to start_point
    const std::function<std::vector<Position>(const SortingNode& n)> get_sorted_positions =
        [&get_sorted_positions](const SortingNode& n) -> std::vector<Position>
    {
        std::vector<Position> output;
        for (const SortingNode& c : n.children)
        {
            const std::vector<Position> children_sorted = get_sorted_positions(c);
            output.insert(output.end(), children_sorted.begin(), children_sorted.end());
        }
        output.push_back(n.pos);

        return output;
    };

    return get_sorted_positions(root);
}
