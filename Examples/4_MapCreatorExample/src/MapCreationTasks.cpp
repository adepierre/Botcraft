#include "MapCreationTasks.hpp"

#include <botcraft/Network/NetworkManager.hpp>
#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>
#include <botcraft/Game/Inventory/Window.hpp>
#include <botcraft/AI/Tasks/InventoryTasks.hpp>
#include <botcraft/AI/Tasks/DigTask.hpp>

#include <iostream>

using namespace Botcraft;
using namespace Botcraft::AI;
using namespace ProtocolCraft;

Status GetAllChestsAround(BehaviourClient& c)
{
    std::vector<Position> chests_pos;

    std::shared_ptr<LocalPlayer> local_player = c.GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<World> world = c.GetWorld();

    const Position player_position(local_player->GetX(), local_player->GetY(), local_player->GetZ());

    Position checked_position;
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        const Block* block;
        const std::map<std::pair<int, int>, std::shared_ptr<Chunk> >& all_chunks = world->GetAllChunks();

        for (auto it = all_chunks.begin(); it != all_chunks.end(); ++it)
        {
            for (int x = 0; x < CHUNK_WIDTH; ++x)
            {
                checked_position.x = it->first.first * CHUNK_WIDTH + x;
                for (int y = 0; y < CHUNK_HEIGHT; ++y)
                {
                    checked_position.y = y;
                    for (int z = 0; z < CHUNK_WIDTH; ++z)
                    {
                        checked_position.z = it->first.second * CHUNK_WIDTH + z;
                        block = world->GetBlock(checked_position);
                        if (block && block->GetBlockstate()->GetName() == "minecraft:chest")
                        {
                            chests_pos.push_back(checked_position);
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

    std::mt19937 random_engine = std::mt19937(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

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
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                container_id = inventory_manager->GetFirstOpenedWindowId();
                if (container_id == -1)
                {
                    continue;
                }
                const std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);

                const short first_player_index = container->GetFirstPlayerInventorySlot();
                player_dst = first_player_index + 9 * 3;

                const std::map<short, Slot>& slots = container->GetSlots();

                slots_src.reserve(slots.size());

                for (auto it = slots.begin(); it != slots.end(); ++it)
                {
                    // Chest is src
                    if (it->first >= 0
                        && it->first < first_player_index
                        && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                        && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName() == item_name
#else
                        && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() == food_name
#endif
                        )
                    {
                        slots_src.push_back(it->first);
                    }
                }
            }

            if (slots_src.size() > 0)
            {
                // Select a random slot in both src and dst
                int src_index = slots_src.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, slots_src.size() - 1)(random_engine);

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
        auto start = std::chrono::system_clock::now();
        while (
#if PROTOCOL_VERSION < 347
            AssetsManager::getInstance().Items().at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetBlockID()).at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetItemDamage())->GetName() != item_name
#else
            AssetsManager::getInstance().Items().at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetItemID())->GetName() != food_name
#endif
            )
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to get food from chest (Timeout)." << std::endl;
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
    std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
    const std::map<short, Slot>& slots = inventory_manager->GetPlayerInventory()->GetSlots();
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
        if (it->first >= 9/*Window::INVENTORY_STORAGE_START*/ &&
            it->first < 45 /*Window::INVENTORY_OFFHAND_INDEX*/ &&
            !it->second.IsEmptySlot())
        {
#if PROTOCOL_VERSION < 347
            blocks_in_inventory.insert(AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName());
#else
            blocks_in_inventory.insert(AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName());
#endif
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

    std::mt19937 random_engine = std::mt19937(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

    while (true)
    {
        if (chests.size() == 0)
        {
            return Status::Failure;
        }

        // Select a chest
        size_t chest_index_index = chest_indices.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, chest_indices.size() - 1)(random_engine);
        size_t chest_index = chest_indices[chest_index_index];

        // If we can't open this chest for a reason
        if (OpenContainer(c, chests[chest_index]) == Status::Failure)
        {
            continue;
        }

        std::vector<short> slots_src;
        std::vector<short> slots_dst;
        short container_id;
        short first_player_index;
        // Find possible swaps
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            container_id = inventory_manager->GetFirstOpenedWindowId();

            if (container_id == -1)
            {
                continue;
            }

            const std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);

            first_player_index = (static_cast<int>(container->GetType()) + 1) * 9;

            const std::map<short, Slot>& slots = container->GetSlots();

            slots_src.reserve(slots.size());
            slots_dst.reserve(slots.size());

            for (auto it = slots.begin(); it != slots.end(); ++it)
            {
                // If take, chest is src
                if (it->first >= 0
                    && it->first < first_player_index
                    && take_from_chest
                    && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                    && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName() != food_name
#else
                    && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() != food_name
#endif
                    )
                {
                    slots_src.push_back(it->first);
                }
                // If take, player is dst
                else if (it->first >= first_player_index
                    && take_from_chest
                    && it->second.IsEmptySlot())
                {
                    slots_dst.push_back(it->first);
                }
                // If !take, chest is dst
                else if (it->first >= 0
                    && it->first < first_player_index
                    && !take_from_chest
                    && it->second.IsEmptySlot())
                {
                    slots_dst.push_back(it->first);
                }
                // If !take, player is src
                else if (it->first >= first_player_index
                    && !take_from_chest
                    && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                    && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName() != food_name
#else
                    && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() != food_name
#endif
                    )
                {
                    slots_src.push_back(it->first);
                }
            }
        }

        Status swap_success = Status::Failure;
        int dst_index = -1;
        int src_index = -1;
        if (slots_src.size() > 0 &&
            slots_dst.size() > 0)
        {
            // Select a random slot in both src and dst
            dst_index = slots_dst.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, slots_dst.size() - 1)(random_engine);
            src_index = slots_src.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, slots_src.size() - 1)(random_engine);

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
        auto start = std::chrono::system_clock::now();
        const short checked_slot_index = (take_from_chest ? slots_dst[dst_index] : slots_src[src_index]) - first_player_index + 9; /*Window::INVENTORY_STORAGE_START*/
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to get items from chest (Timeout)." << std::endl;
                return Status::Failure;
            }
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                const Slot& slot = inventory_manager->GetPlayerInventory()->GetSlot(checked_slot_index);
                if ((take_from_chest && !slot.IsEmptySlot()) ||
                    (!take_from_chest && slot.IsEmptySlot()))
                {
                    break;
                }
            }
            c.Yield();
        }
    }

    return Status::Success;
}

Status FindNextTask(BehaviourClient& c)
{

}

Status ExecuteNextTask(BehaviourClient& c)
{
    Blackboard& b = c.GetBlackboard();

    const std::string& action = b.Get<std::string>("NextTask.action");
    const Position& block_position = b.Get<Position>("NextTask.block_position");
    const PlayerDiggingFace face = b.Get<PlayerDiggingFace>("NextTask.face");
    if (action == "Dig")
    {
        return Dig(c, block_position, face);
    }
    else if (action == "Place")
    {
        const std::string& item_name = b.Get<std::string>("NextTask.item");
        return PlaceBlock(c, item_name, block_position, face, true);
    }

    std::cerr << "Warning, unknown task in ExecuteNextTask" << std::endl;
    return Status::Failure;
}

Status CheckCompletion(BehaviourClient& c)
{
    Position world_pos;
    Position target_pos;

    int additional_blocks = 0;
    int wrong_blocks = 0;
    int missing_blocks = 0;

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
                std::shared_ptr<Blockstate> blockstate;
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());
                    const Block* block = world->GetBlock(world_pos);

                    if (!block)
                    {
                        if (target_id != -1)
                        {
                            if (!full)
                            {
                                return false;
                            }
                            missing_blocks++;
                            if (print_details)
                            {
                                std::cout << "Missing " << palette.at(target_id) << " in " << world_pos << std::endl;
                            }
                        }
                        continue;
                    }
                    blockstate = block->GetBlockstate();
                }

                if (target_id == -1)
                {
                    if (!blockstate->IsAir())
                    {
                        if (!full)
                        {
                            return false;
                        }
                        additional_blocks++;
                        if (print_details)
                        {
                            std::cout << "Additional " << blockstate->GetName() << " in " << world_pos << std::endl;
                        }
                    }
                }
                else
                {
                    if (blockstate->IsAir())
                    {
                        if (!full)
                        {
                            return false;
                        }
                        missing_blocks++;
                        if (print_details)
                        {
                            std::cout << "Missing " << palette.at(target_id) << " in " << world_pos << std::endl;
                        }
                    }
                    else
                    {
                        const std::string& target_name = palette.at(target_id);
                        if (blockstate->GetName() != target_name)
                        {
                            if (!full)
                            {
                                return false;
                            }
                            wrong_blocks++;
                            if (print_details)
                            {
                                std::cout << "Wrong " << blockstate->GetName() << " instead of " << target_name << " in " << world_pos << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

    if (print_errors)
    {
        std::cout << "Wrong blocks: " << wrong_blocks << std::endl;
        std::cout << "Missing blocks: " << missing_blocks << std::endl;
        std::cout << "Additional blocks: " << additional_blocks << std::endl;
    }

    return missing_blocks + additional_blocks + wrong_blocks == 0;
}

Status WarnCantFindFood(BehaviourClient& c)
{
    std::cout << "[" << c.GetNetworkManager()->GetMyName() << "]: Can't find food anywhere" << std::endl;
    return Status::Success;
}

Status WarnCantEat(BehaviourClient& c)
{
    std::cout << "[" << c.GetNetworkManager()->GetMyName() << "]: Can't eat!" << std::endl;
    return Status::Success;
}

Status WarnNoBlockInChest(BehaviourClient& c)
{
    std::cout << "[" << c.GetNetworkManager()->GetMyName() << "]: No more block in chests, I will stop here." << std::endl;
    return Status::Success;
}

Status WarnCompleted(BehaviourClient& c)
{
    std::cout << "[" << c.GetNetworkManager()->GetMyName() << "]: Task fully completed!" << std::endl;
    return Status::Success;
}