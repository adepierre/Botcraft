#include "MapCreationTasks.hpp"

#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/AI/Tasks/AllTasks.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <unordered_set>

using namespace Botcraft;
using namespace ProtocolCraft;

Status GetAllChestsAround(BehaviourClient& c)
{
    std::vector<Position> chests_pos;

    std::shared_ptr<LocalPlayer> local_player = c.GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<World> world = c.GetWorld();

    const Position player_position(
        static_cast<int>(std::floor(local_player->GetX())),
        static_cast<int>(std::floor(local_player->GetY())),
        static_cast<int>(std::floor(local_player->GetZ()))
    );

    Position checked_position;
    {
        auto all_chunks = world->GetChunks();
        for (auto it = all_chunks->begin(); it != all_chunks->end(); ++it)
        {
            for (int x = 0; x < CHUNK_WIDTH; ++x)
            {
                checked_position.x = x;
                for (int y = 0; y < it->second.GetHeight(); ++y)
                {
                    checked_position.y = y + it->second.GetMinY();
                    for (int z = 0; z < CHUNK_WIDTH; ++z)
                    {
                        checked_position.z = z;
                        const Blockstate* block = it->second.GetBlock(checked_position);
                        if (block != nullptr && block->GetName() == "minecraft:chest")
                        {
                            const Position world_position(
                                it->first.first * CHUNK_WIDTH + x,
                                y + world->GetMinY(),
                                it->first.second * CHUNK_WIDTH + z
                            );
                            chests_pos.push_back(world_position);
                        }
                    }
                }
            }
        }
    }

    c.GetBlackboard().Set("World.ChestsPos", chests_pos);

    return Status::Success;
}

Status GetSomeFood(BehaviourClient& c, const std::string& food_name)
{
    std::shared_ptr<InventoryManager> inventory_manager = c.GetInventoryManager();

    GetAllChestsAround(c);

    const std::vector<Position>& chests = c.GetBlackboard().Get<std::vector<Position>>("World.ChestsPos");

    std::vector<size_t> chests_indices(chests.size());
    for (size_t i = 0; i < chests.size(); ++i)
    {
        chests_indices[i] = i;
    }

    std::mt19937 random_engine = std::mt19937(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));

    std::shuffle(chests_indices.begin(), chests_indices.end(), random_engine);

    short container_id;
    bool item_taken = false;

    for (size_t index = 0; index < chests.size(); ++index)
    {
        const size_t i = chests_indices[index];
        // If we can't open this chest for a reason
        if (OpenContainer(c, chests[i]) == Status::Failure)
        {
            continue;
        }

        short player_dst = -1;
        while (true)
        {
            std::vector<short> slots_src;

            container_id = inventory_manager->GetFirstOpenedWindowId();
            if (container_id == -1)
            {
                continue;
            }

            const std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);
            if (container == nullptr)
            {
                continue;
            }

            const short first_player_index = container->GetFirstPlayerInventorySlot();
            player_dst = first_player_index + 9 * 3;

            const std::map<short, Slot> slots = container->GetSlots();

            slots_src.reserve(slots.size());

            for (const auto& [id, slot] : slots)
            {
                // Chest is src
                if (id >= 0
                    && id < first_player_index
                    && !slot.IsEmptySlot()
                    && AssetsManager::getInstance().Items().at(slot.GetItemID())->GetName() == food_name
                    )
                {
                    slots_src.push_back(id);
                }
            }

            if (slots_src.size() > 0)
            {
                // Select a random slot in both src and dst
                const int src_index = slots_src.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, static_cast<int>(slots_src.size()) - 1)(random_engine);

                // Try to swap the items
                if (SwapItemsInContainer(c, container_id, slots_src[src_index], player_dst) == Status::Success)
                {
                    item_taken = true;
                    break;
                }
            }
            // This means the chest doesn't have any food
            else
            {
                break;
            }
        }

        CloseContainer(c, container_id);

        if (!item_taken)
        {
            continue;
        }

        // Wait until player inventory is updated after the container is closed
        auto start = std::chrono::steady_clock::now();
        while (AssetsManager::getInstance().Items().at(inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HOTBAR_START).GetItemID())->GetName() != food_name)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 10000)
            {
                LOG_WARNING("Something went wrong trying to get food from chest (Timeout).");
                return Status::Failure;
            }
            c.Yield();
        }

        // No need to continue loooking in the other chests
        break;
    }

    return item_taken ? Status::Success : Status::Failure;
}

Status GetBlocksAvailableInInventory(BehaviourClient& c)
{
    std::shared_ptr<InventoryManager> inventory_manager = c.GetInventoryManager();

    std::set<std::string> blocks_in_inventory;
    for (const auto& [idx, slot] : inventory_manager->GetPlayerInventory()->GetSlots())
    {
        if (idx >= Window::INVENTORY_STORAGE_START &&
            idx < Window::INVENTORY_OFFHAND_INDEX &&
            !slot.IsEmptySlot())
        {
            blocks_in_inventory.insert(AssetsManager::getInstance().Items().at(slot.GetItemID())->GetName());
        }
    }

    c.GetBlackboard().Set("Inventory.block_list", blocks_in_inventory);

    return blocks_in_inventory.size() > 0 ? Status::Success : Status::Failure;
}

Status SwapChestsInventory(BehaviourClient& c, const std::string& food_name, const bool take_from_chest)
{
    std::shared_ptr<InventoryManager> inventory_manager = c.GetInventoryManager();

    GetAllChestsAround(c);

    const std::vector<Position>& chests = c.GetBlackboard().Get<std::vector<Position>>("World.ChestsPos");
    std::vector<size_t> chest_indices(chests.size());
    for (size_t i = 0; i < chests.size(); ++i)
    {
        chest_indices[i] = i;
    }

    std::mt19937 random_engine(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));

    while (true)
    {
        // We checked all the chests
        if (chest_indices.size() == 0)
        {
            return Status::Success;
        }

        // Select a chest
        size_t chest_index_index = chest_indices.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, static_cast<int>(chest_indices.size()) - 1)(random_engine);
        size_t chest_index = chest_indices[chest_index_index];

        // If we can't open this chest for a reason
        if (OpenContainer(c, chests[chest_index]) == Status::Failure)
        {
            continue;
        }

        // Find possible swaps
        const short container_id = inventory_manager->GetFirstOpenedWindowId();

        if (container_id == -1)
        {
            continue;
        }

        const std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);
        if (container == nullptr)
        {
            continue;
        }

        const short first_player_index = (static_cast<int>(container->GetType()) + 1) * 9;

        const std::map<short, Slot> slots = container->GetSlots();

        std::vector<short> slots_src;
        slots_src.reserve(slots.size());
        std::vector<short> slots_dst;
        slots_dst.reserve(slots.size());

        for (const auto& [idx, slot] : slots)
        {
            // If take, chest is src
            if (idx >= 0
                && idx < first_player_index
                && take_from_chest
                && !slot.IsEmptySlot()
                && AssetsManager::getInstance().Items().at(slot.GetItemID())->GetName() != food_name)
            {
                slots_src.push_back(idx);
            }
            // If take, player is dst
            else if (idx >= first_player_index
                && take_from_chest
                && slot.IsEmptySlot())
            {
                slots_dst.push_back(idx);
            }
            // If !take, chest is dst
            else if (idx >= 0
                && idx < first_player_index
                && !take_from_chest
                && slot.IsEmptySlot())
            {
                slots_dst.push_back(idx);
            }
            // If !take, player is src
            else if (idx >= first_player_index
                && !take_from_chest
                && !slot.IsEmptySlot()
                && AssetsManager::getInstance().Items().at(slot.GetItemID())->GetName() != food_name)
            {
                slots_src.push_back(idx);
            }
        }

        Status swap_success = Status::Failure;
        int dst_index = -1;
        int src_index = -1;
        if (slots_src.size() > 0 &&
            slots_dst.size() > 0)
        {
            // Select a random slot in both src and dst
            dst_index = slots_dst.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, static_cast<int>(slots_dst.size()) - 1)(random_engine);
            src_index = slots_src.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, static_cast<int>(slots_src.size()) - 1)(random_engine);

            // Try to swap the items
            swap_success = SwapItemsInContainer(c, container_id, slots_src[src_index], slots_dst[dst_index]);
        }

        // Close the chest
        CloseContainer(c, container_id);

        // The chest was empty/full, remove it from the list
        if ((take_from_chest && slots_src.size() == 0) ||
            (!take_from_chest && slots_dst.size() == 0))
        {
            chest_indices.erase(chest_indices.begin() + chest_index_index);
            continue;
        }
        // The player inventory was full/empty, end the function
        else if ((take_from_chest && slots_dst.size() == 0) ||
            (!take_from_chest && slots_src.size() == 0))
        {
            return Status::Success;
        }

        if (swap_success == Status::Failure)
        {
            continue;
        }

        // Wait for the confirmation from the server
        auto start = std::chrono::steady_clock::now();
        const short checked_slot_index = (take_from_chest ? slots_dst[dst_index] : slots_src[src_index]) - first_player_index + Window::INVENTORY_STORAGE_START;
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 10000)
            {
                LOG_WARNING("Something went wrong trying to get items from chest (Timeout).");
                return Status::Failure;
            }
            const Slot slot = inventory_manager->GetPlayerInventory()->GetSlot(checked_slot_index);
            if ((take_from_chest && !slot.IsEmptySlot()) ||
                (!take_from_chest && slot.IsEmptySlot()))
            {
                break;
            }
            c.Yield();
        }
    }

    return Status::Success;
}

Status FindNextTask(BehaviourClient& c)
{
    Blackboard& blackboard = c.GetBlackboard();
    std::shared_ptr<EntityManager> entity_manager = c.GetEntityManager();
    std::shared_ptr<World> world = c.GetWorld();

    const Position& start = blackboard.Get<Position>("Structure.start");
    const Position& end = blackboard.Get<Position>("Structure.end");
    const std::vector<std::vector<std::vector<short> > >& target = blackboard.Get<std::vector<std::vector<std::vector<short> > > >("Structure.target");
    const std::map<short, std::string>& palette = blackboard.Get<std::map<short, std::string> >("Structure.palette");

    const std::set<std::string>& available = blackboard.Get<std::set<std::string> >("Inventory.block_list");

    std::mt19937 random_engine(static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()));

    Position start_pos;

    start_pos.x = std::min(end.x, std::max(start.x, static_cast<int>(std::floor(entity_manager->GetLocalPlayer()->GetX()))));
    start_pos.y = std::min(end.y, std::max(start.y, static_cast<int>(std::floor(entity_manager->GetLocalPlayer()->GetY()))));
    start_pos.z = std::min(end.z, std::max(start.z, static_cast<int>(std::floor(entity_manager->GetLocalPlayer()->GetZ()))));

    std::unordered_set<Position> explored;
    std::unordered_set<Position> to_explore;

    const std::vector<Position> neighbour_offsets({ Position(0, 1, 0), Position(0, -1, 0),
        Position(0, 0, 1), Position(0, 0, -1),
        Position(1, 0, 0), Position(-1, 0, 0) });

    to_explore.insert(start_pos);

    std::vector<Position> pos_candidates;
    std::vector<std::string> item_candidates;
    std::vector<PlayerDiggingFace> face_candidates;

    while (!to_explore.empty())
    {
        // For each candidate, check if
        // 1) the target is not air
        // 2) we have the correct block in the inventory
        // 3) it is currently a free space
        // 4) it has a block under or next to it so we can put the new block

        // OR

        // 1) the placed block is not air
        // 2) it does not match the desired build
        // 3) it has a free block under or next to it so we can dig it

        for (auto it = to_explore.begin(); it != to_explore.end(); ++it)
        {
            const Position pos = *it;

            const int target_palette = target[pos.x - start.x][pos.y - start.y][pos.z - start.z];
            const std::string& target_name = palette.at(target_palette);
            const Blockstate* blockstate = world->GetBlock(pos);
            if (blockstate == nullptr)
            {
#if PROTOCOL_VERSION < 347 /* < 1.13 */
                blockstate = AssetsManager::getInstance().Blockstates().at(0).at(0).get();
#else
                blockstate = AssetsManager::getInstance().Blockstates().at(0).get();
#endif
            }

            // Empty space requiring block placement
            if (target_palette != -1
                && blockstate->IsAir()
                && available.find(target_name) != available.end())
            {
                for (int i = 0; i < neighbour_offsets.size(); ++i)
                {
                    const Blockstate* neighbour_blockstate = world->GetBlock(pos + neighbour_offsets[i]);
                    if (neighbour_blockstate != nullptr && !neighbour_blockstate->IsAir())
                    {
                        pos_candidates.push_back(pos);
                        item_candidates.push_back(target_name);
                        face_candidates.push_back(static_cast<PlayerDiggingFace>(i));
                        break;
                    }
                }
            }
            // Wrong block requiring digging
            else if ((target_palette != -1 && !blockstate->IsAir() && target_name != blockstate->GetName())
                || (target_palette == -1 && !blockstate->IsAir()))
            {
                for (int i = 0; i < neighbour_offsets.size(); ++i)
                {
                    const Blockstate* neighbour_block = world->GetBlock(pos + neighbour_offsets[i]);

                    if (neighbour_block != nullptr && !neighbour_block->IsAir())
                    {
                        pos_candidates.push_back(pos);
                        item_candidates.push_back("");
                        face_candidates.push_back((PlayerDiggingFace)i);
                        break;
                    }
                }
            }
        }

        // If we have at least one candidate
        if (pos_candidates.size() > 0)
        {
            // Get the position of all other players
            std::vector<Vector3<double> > other_player_pos;
            {
                auto entities = entity_manager->GetEntities();
                for (const auto& [id, entity] : *entities)
                {
                    if (entity->GetType() == EntityType::Player)
                    {
                        other_player_pos.push_back(entity ->GetPosition());
                    }
                }
            }

            // Get all the candidates that are as far as possible from all 
            // the other players
            std::vector<int> max_dist_indices;
            double max_dist = 0.0;
            for (int i = 0; i < pos_candidates.size(); ++i)
            {
                double dist = 0.0;
                for (int j = 0; j < other_player_pos.size(); ++j)
                {
                    dist += std::abs(pos_candidates[i].x - other_player_pos[j].x) +
                        std::abs(pos_candidates[i].y - other_player_pos[j].y) +
                        std::abs(pos_candidates[i].z - other_player_pos[j].z);

                    if (dist > max_dist)
                    {
                        max_dist_indices.clear();
                        max_dist = dist;
                    }

                    if (dist == max_dist)
                    {
                        max_dist_indices.push_back(i);
                    }
                }
            }

            // Select one randomly if multiple possibilities
            int selected_index = max_dist_indices.size() == 1 ? 0 : max_dist_indices[std::uniform_int_distribution<int>(0, static_cast<int>(max_dist_indices.size()) - 1)(random_engine)];

            blackboard.Set<std::string>("NextTask.action", item_candidates[selected_index].empty() ? "Dig" : "Place");
            blackboard.Set("NextTask.block_position", pos_candidates[selected_index]);
            blackboard.Set("NextTask.face", face_candidates[selected_index]);
            if (!item_candidates[selected_index].empty())
            {
                blackboard.Set("NextTask.item", item_candidates[selected_index]);
            }

            return Status::Success;
        }

        explored.insert(to_explore.begin(), to_explore.end());
        std::unordered_set<Position> neighbours;
        for (auto it = to_explore.begin(); it != to_explore.end(); ++it)
        {
            for (int i = 0; i < neighbour_offsets.size(); ++i)
            {
                const Position p = *it + neighbour_offsets[i];

                if (p.x < start.x ||
                    p.x > end.x ||
                    p.y < start.y ||
                    p.y > end.y ||
                    p.z < start.z ||
                    p.z > end.z)
                {
                    continue;
                }

                if (explored.find(p) == explored.end())
                {
                    neighbours.insert(p);
                }
            }
        }
        to_explore = neighbours;
    }

    return Status::Failure;
}

Status ExecuteNextTask(BehaviourClient& c)
{
    Blackboard& b = c.GetBlackboard();

    const std::string& action = b.Get<std::string>("NextTask.action");
    const Position& block_position = b.Get<Position>("NextTask.block_position");
    const PlayerDiggingFace face = b.Get<PlayerDiggingFace>("NextTask.face");
    if (action == "Dig")
    {
        return Dig(c, block_position, true, face);
    }
    else if (action == "Place")
    {
        const std::string& item_name = b.Get<std::string>("NextTask.item");
        return PlaceBlock(c, item_name, block_position, face, true, false);
    }

    LOG_WARNING("Unknown task in ExecuteNextTask");
    return Status::Failure;
}

Status CheckCompletion(BehaviourClient& c)
{
    Blackboard& blackboard = c.GetBlackboard();
    std::shared_ptr<World> world = c.GetWorld();

    Position world_pos;
    Position target_pos;

    int additional_blocks = 0;
    int wrong_blocks = 0;
    int missing_blocks = 0;

    const Position& start = blackboard.Get<Position>("Structure.start");
    const Position& end = blackboard.Get<Position>("Structure.end");
    const std::vector<std::vector<std::vector<short> > >& target = blackboard.Get<std::vector<std::vector<std::vector<short> > > >("Structure.target");
    const std::map<short, std::string>& palette = blackboard.Get<std::map<short, std::string> >("Structure.palette");

    const bool log_details = blackboard.Get<bool>("CheckCompletion.log_details", false);
    const bool log_errors = blackboard.Get<bool>("CheckCompletion.log_errors", false);
    const bool full_check = blackboard.Get<bool>("CheckCompletion.full_check", false);

    //Reset values for the next time
    blackboard.Set("CheckCompletion.log_details", false);
    blackboard.Set("CheckCompletion.log_errors", false);
    blackboard.Set("CheckCompletion.full_check", false);

    for (int x = start.x; x <= end.x; ++x)
    {
        world_pos.x = x;
        target_pos.x = x - start.x;
        for (int y = start.y; y <= end.y; ++y)
        {
            world_pos.y = y;
            target_pos.y = y - start.y;
            for (int z = start.z; z <= end.z; ++z)
            {
                world_pos.z = z;
                target_pos.z = z - start.z;

                const short target_id = target[target_pos.x][target_pos.y][target_pos.z];
                const Blockstate* blockstate = world->GetBlock(world_pos);
                if (blockstate == nullptr)
                {
                    if (target_id != -1)
                    {
                        if (!full_check)
                        {
                            return Status::Failure;
                        }
                        missing_blocks++;
                        if (log_details && missing_blocks < 100) // Don't print more than 100 missing blocks
                        {
                            LOG_INFO("Missing " << palette.at(target_id) << " in " << world_pos);
                        }
                    }
                    continue;
                }

                if (target_id == -1)
                {
                    if (!blockstate->IsAir())
                    {
                        if (!full_check)
                        {
                            return Status::Failure;
                        }
                        additional_blocks++;
                        if (log_details)
                        {
                            LOG_INFO("Additional " << blockstate->GetName() << " in " << world_pos);
                        }
                    }
                }
                else
                {
                    if (blockstate->IsAir())
                    {
                        if (!full_check)
                        {
                            return Status::Failure;
                        }
                        missing_blocks++;
                        if (log_details)
                        {
                            LOG_INFO("Missing " << palette.at(target_id) << " in " << world_pos);
                        }
                    }
                    else
                    {
                        const std::string& target_name = palette.at(target_id);
                        if (blockstate->GetName() != target_name)
                        {
                            if (!full_check)
                            {
                                return Status::Failure;
                            }
                            wrong_blocks++;
                            if (log_details)
                            {
                                LOG_INFO("Wrong " << blockstate->GetName() << " instead of " << target_name << " in " << world_pos);
                            }
                        }
                    }
                }
            }
        }
    }

    if (log_errors)
    {
        LOG_INFO("Wrong blocks: " << wrong_blocks);
        LOG_INFO("Missing blocks: " << missing_blocks);
        LOG_INFO("Additional blocks: " << additional_blocks);
    }

    return (missing_blocks + additional_blocks + wrong_blocks == 0) ? Status::Success : Status::Failure;
}

Status WarnConsole(BehaviourClient& c, const std::string& msg)
{
    LOG_WARNING("[" << c.GetNetworkManager()->GetMyName() << "]: " << msg);
    return Status::Success;
}

Status LoadNBT(BehaviourClient& c, const std::string& path, const Position& offset, const std::string& temp_block, const bool log_info)
{
    NBT::Value loaded_file;
    try
    {
        std::ifstream infile(path, std::ios_base::binary);
        infile.unsetf(std::ios::skipws);
        infile >> loaded_file;
        infile.close();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Error loading NBT file " << e.what());
        return Status::Failure;
    }

    std::map<short, std::string> palette;
    palette[-1] = "minecraft:air";
    short id_temp_block = -1;
    std::map<short, int> num_blocks_used;

    if (!loaded_file.contains("palette") ||
        !loaded_file["palette"].is_list_of<NBT::TagCompound>())
    {
        LOG_ERROR("Error loading NBT file, no palette TagCompound found");
        return Status::Failure;
    }

    const std::vector<NBT::TagCompound>& palette_list = loaded_file["palette"].as_list_of<NBT::TagCompound>();
    for (int i = 0; i < palette_list.size(); ++i)
    {
        const std::string& block_name = palette_list[i]["Name"].get<std::string>();
        palette[i] = block_name;
        num_blocks_used[i] = 0;
        if (block_name == temp_block)
        {
            id_temp_block = i;
        }
    }

    Position min(std::numeric_limits<int>().max(), std::numeric_limits<int>().max(), std::numeric_limits<int>().max());
    Position max(std::numeric_limits<int>().min(), std::numeric_limits<int>().min(), std::numeric_limits<int>().min());

    if (!loaded_file.contains("blocks") ||
        !loaded_file["blocks"].is_list_of<NBT::TagCompound>())
    {
        LOG_ERROR("Error loading NBT file, no blocks TagCompound found");
        return Status::Failure;
    }

    const std::vector<NBT::TagCompound>& block_tag = loaded_file["blocks"].as_list_of<NBT::TagCompound>();
    for (const auto& c : block_tag)
    {
        const std::vector<int>& pos_list = c["pos"].as_list_of<int>();
        const int x = pos_list[0];
        const int y = pos_list[1];
        const int z = pos_list[2];

        if (x < min.x)
        {
            min.x = x;
        }
        if (y < min.y)
        {
            min.y = y;
        }
        if (z < min.z)
        {
            min.z = z;
        }
        if (x > max.x)
        {
            max.x = x;
        }
        if (y > max.y)
        {
            max.y = y;
        }
        if (z > max.z)
        {
            max.z = z;
        }
    }

    Position size = max - min + Position(1, 1, 1);
    Position start = offset;
    Position end = offset + size - Position(1, 1, 1);

    if (log_info)
    {
        LOG_INFO("Start: " << start << " | " << "End: " << end);
    }

    // Fill the target area with air (-1)
    std::vector<std::vector<std::vector<short> > > target(size.x, std::vector<std::vector<short> >(size.y, std::vector<short>(size.z, -1)));

    // Read all block to place
    for (const auto& c : block_tag)
    {
        const int state = c["state"].get<int>();
        const std::vector<int>& pos_list = c["pos"].as_list_of<int>();
        const int x = pos_list[0];
        const int y = pos_list[1];
        const int z = pos_list[2];

        target[x - min.x][y - min.y][z - min.z] = state;
        num_blocks_used[state] += 1;
    }

    if (id_temp_block == -1)
    {
        LOG_WARNING("Can't find the given temp block " << temp_block << " in the palette");
    }
    else
    {
        int removed_layers = 0;
        // Check the bottom Y layers, if only
        // air or temp block, the layer can be removed
        while (true)
        {
            bool is_removable = true;
            int num_temp_block = 0;
            for (int x = 0; x < size.x; ++x)
            {
                for (int z = 0; z < size.z; z++)
                {
                    if (target[x][0][z] == id_temp_block)
                    {
                        num_temp_block += 1;
                    }

                    if (target[x][0][z] != -1 &&
                        target[x][0][z] != id_temp_block)
                    {
                        is_removable = false;
                        break;
                    }
                    if (!is_removable)
                    {
                        break;
                    }
                }
            }

            if (!is_removable)
            {
                break;
            }

            for (int x = 0; x < size.x; ++x)
            {
                target[x].erase(target[x].begin());
            }
            num_blocks_used[id_temp_block] -= num_temp_block;
            removed_layers++;
            size.y -= 1;
            end.y -= 1;
        }

        if (log_info)
        {
            LOG_INFO("Removed the bottom " << removed_layers << " layer" << (removed_layers > 1 ? "s" : ""));
        }
    }

    if (log_info)
    {
        LOG_INFO("Total size: " << size);

        std::stringstream needed;
        needed << "Block needed:\n";
        for (auto it = num_blocks_used.begin(); it != num_blocks_used.end(); ++it)
        {
            needed << "\t" << palette[it->first] << "\t\t" << it->second << "\n";
        }
        LOG_INFO(needed.rdbuf());

        // Check if some block can't be placed (flying blocks)
        std::stringstream flyings;
        flyings << "Flying blocks, you might have to place them yourself:\n";
        Position target_pos;

        const std::vector<Position> neighbour_offsets({ Position(0, 1, 0), Position(0, -1, 0),
            Position(0, 0, 1), Position(0, 0, -1),
            Position(1, 0, 0), Position(-1, 0, 0) });

        for (int x = 0; x < size.x; ++x)
        {
            target_pos.x = x;
            // If this block is on the floor, it's ok
            for (int y = 1; y < size.y; ++y)
            {
                target_pos.y = y;

                for (int z = 0; z < size.z; ++z)
                {
                    target_pos.z = z;

                    const short target_id = target[target_pos.x][target_pos.y][target_pos.z];

                    if (target_id != -1)
                    {
                        // Check all target neighbours
                        bool has_neighbour = false;
                        for (int i = 0; i < neighbour_offsets.size(); ++i)
                        {
                            const Position neighbour_pos = target_pos + neighbour_offsets[i];

                            if (neighbour_pos.x >= 0 && neighbour_pos.x < size.x &&
                                neighbour_pos.y >= 0 && neighbour_pos.y < size.y &&
                                neighbour_pos.z >= 0 && neighbour_pos.z < size.z &&
                                target[neighbour_pos.x][neighbour_pos.y][neighbour_pos.z] != -1)
                            {
                                has_neighbour = true;
                                break;
                            }
                        }

                        if (!has_neighbour)
                        {
                            flyings << start + target_pos << "\t" << palette[target_id] << "\n";
                        }
                    }
                }
            }
        }
        LOG_WARNING(flyings.rdbuf());
    }

    Blackboard& blackboard = c.GetBlackboard();

    blackboard.Set("Structure.start", start);
    blackboard.Set("Structure.end", end);
    blackboard.Set("Structure.target", target);
    blackboard.Set("Structure.palette", palette);
    blackboard.Set("Structure.loaded", true);

    return Status::Success;
}
