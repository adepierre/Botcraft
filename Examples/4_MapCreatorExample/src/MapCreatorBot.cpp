#include <sstream>
#include <fstream>
#include <algorithm>

#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/World/Block.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>
#include <botcraft/Game/Inventory/Window.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Network/NetworkManager.hpp>
#include <botcraft/Game/AssetsManager.hpp>

#include <protocolCraft/Types/NBT/NBT.hpp>
#include <protocolCraft/Types/NBT/TagList.hpp>

#include "MapCreatorBot.hpp"
#include <protocolCraft/Types/NBT/TagString.hpp>
#include <protocolCraft/Types/NBT/TagInt.hpp>

using namespace Botcraft;
using namespace ProtocolCraft;

MapCreatorBot::MapCreatorBot(const bool use_renderer_) : InterfaceClient(use_renderer_, false)
{
    random_engine = std::mt19937(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

MapCreatorBot::~MapCreatorBot()
{
    
}

void MapCreatorBot::Handle(ClientboundChatPacket &msg)
{
    BaseClient::Handle(msg);
    
    // Split the message 
    std::istringstream ss{ msg.GetMessage().GetText() };
    const std::vector<std::string> splitted({ std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{} });

    if (splitted.size() < 2 || splitted[0] != network_manager->GetMyName())
    {
        return;
    }

    if (splitted[1] == "start")
    {
        if (splitted.size() < 2)
        {
            Say("Usage: [BotName] [start]");
            return;
        }

        std::thread map_creation_thread(&MapCreatorBot::CreateMap, this);
        map_creation_thread.detach();
    }
    else
    {
        return;
    }
}

void MapCreatorBot::LoadNBTFile(const std::string& path, const Position& offset_, const std::string& temp_block)
{
    std::ifstream infile(path, std::ios_base::binary);
    infile.unsetf(std::ios::skipws);

    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    std::vector<unsigned char> file_content;
    file_content.reserve(length);

    file_content.insert(file_content.begin(),
        std::istream_iterator<unsigned char>(infile),
        std::istream_iterator<unsigned char>());

    infile.close();

    std::vector<unsigned char>::const_iterator it = file_content.begin();

    NBT loaded_file;
    loaded_file.Read(it, length);

    palette.clear();
    short id_temp_block = -1;
    std::map<short, int> num_blocks_used;

    std::shared_ptr<TagList> palette_tag = std::dynamic_pointer_cast<TagList>(loaded_file.GetTag("palette"));

    for (int i = 0; i < palette_tag->GetValues().size(); ++i)
    {
        std::shared_ptr<TagCompound> compound = std::dynamic_pointer_cast<TagCompound>(palette_tag->GetValues()[i]);
        const std::string& block_name = std::dynamic_pointer_cast<TagString>(compound->GetValues().at("Name"))->GetValue();
        palette[i] = block_name;
        num_blocks_used[i] = 0;
        if (block_name == temp_block)
        {
            id_temp_block = i;
        }
    }
    
    Position min(std::numeric_limits<int>().max(), std::numeric_limits<int>().max(), std::numeric_limits<int>().max());
    Position max(std::numeric_limits<int>().min(), std::numeric_limits<int>().min(), std::numeric_limits<int>().min());
    std::shared_ptr<TagList> blocks_tag = std::dynamic_pointer_cast<TagList>(loaded_file.GetTag("blocks"));
    for (int i = 0; i < blocks_tag->GetValues().size(); ++i)
    {
        std::shared_ptr<TagCompound> compound = std::dynamic_pointer_cast<TagCompound>(blocks_tag->GetValues()[i]);
        std::shared_ptr<TagList> pos_list = std::dynamic_pointer_cast<TagList>(compound->GetValues().at("pos"));
        const int x = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[0])->GetValue();
        const int y = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[1])->GetValue();
        const int z = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[2])->GetValue();

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
    start = offset_;
    end = offset_ + size - Position(1, 1, 1);

    // Fill the target area with air (-1)
    target = std::vector<std::vector<std::vector<short> > >(size.x, std::vector<std::vector<short> >(size.y, std::vector<short>(size.z, -1)));
    
    // Read all block to place
    for (int i = 0; i < blocks_tag->GetValues().size(); ++i)
    {
        std::shared_ptr<TagCompound> compound = std::dynamic_pointer_cast<TagCompound>(blocks_tag->GetValues()[i]);
        int state = std::dynamic_pointer_cast<TagInt>(compound->GetValues().at("state"))->GetValue();
        std::shared_ptr<TagList> pos_list = std::dynamic_pointer_cast<TagList>(compound->GetValues().at("pos"));
        const int x = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[0])->GetValue();
        const int y = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[1])->GetValue();
        const int z = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[2])->GetValue();

        target[x - min.x][y - min.y][z - min.z] = state;
        num_blocks_used[state] += 1;
    }

    if (id_temp_block == -1)
    {
        std::cerr << "Warning, can't find the given temp block " << temp_block << " in the palette" << std::endl;
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

        std::cout << "Removed the bottom " << removed_layers << " layer" << (removed_layers > 1 ? "s" : "") << std::endl;
    }

    std::cout << "Block needed:" << std::endl;
    for (auto it = num_blocks_used.begin(); it != num_blocks_used.end(); ++it)
    {
        std::cout << "\t" << palette[it->first] << "\t\t" << it->second << std::endl;
    }
}

const std::vector<Position> MapCreatorBot::GetAllChestsAround(const Position& max_search_dist) const
{
    std::vector<Position> output;

    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

    local_player->GetMutex().lock();
    const Position player_position(local_player->GetX(), local_player->GetY(), local_player->GetZ());
    local_player->GetMutex().unlock();

    Position checked_position;
    {
        std::lock_guard<std::mutex> world_guard(world->GetMutex());
        const Block* block;
        for (int x = -max_search_dist.x; x < max_search_dist.x; ++x)
        {
            checked_position.x = player_position.x + x;
            for (int y = -max_search_dist.y; y < max_search_dist.y; ++y)
            {
                checked_position.y = player_position.y + y;
                for (int z = -max_search_dist.z; z < max_search_dist.z; ++z)
                {
                    checked_position.z = player_position.z + z;
                    block = world->GetBlock(checked_position);
                    if (block && block->GetBlockstate()->GetName() == "minecraft:chest")
                    {
                        output.push_back(checked_position);
                    }
                }
            }
        }
    }

    return output;
}

const bool MapCreatorBot::GetSomeFood(const std::string& item_name)
{
    std::vector<Position> chests = GetAllChestsAround(Position(200, 100, 200));
    std::shuffle(chests.begin(), chests.end(), random_engine);

    short container_src_slot_index = -1;
    short container_dst_slot_index = -1;
    short container_id;

    for (int i = 0; i < chests.size(); ++i)
    {
            // If we can't open this chest for a reason
            if (!OpenContainer(chests[i]))
            {
                continue;
            }

            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                container_id = inventory_manager->GetFirstOpenedWindowId();
                if (container_id == -1)
                {
                    continue;
                }
                const std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);

                const short first_player_index = ((int)container->GetType() + 1) * 9;

                // We will put the food in the first slot of the hotbar
                container_dst_slot_index = first_player_index + 27;

                const std::map<short, Slot>& slots = container->GetSlots();
                for (auto it = slots.begin(); it != slots.end(); ++it)
                {
                    if (it->first >= 0
                        && it->first < first_player_index
                        && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                        && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName() == item_name)
#else
                        && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() == item_name)
#endif
                    {
                        container_src_slot_index = it->first;
                        break;
                    }
                }
            }

            // If we found the given item in the inventory
            if (container_src_slot_index != -1)
            {
                break;
            }

            CloseContainer(container_id);
    }

    if (container_src_slot_index == -1)
    {
        return false;
    }

    // Take the food and set it in the first hotbar slot
    if (!SwapItemsInContainer(container_id, container_src_slot_index, container_dst_slot_index))
    {
        CloseContainer(container_id);

        return false;
    }

    CloseContainer(container_id);

    // Wait until player inventory is updated after the container is closed
    auto start = std::chrono::system_clock::now();
    std::shared_ptr<Window> container = nullptr;
    while (
#if PROTOCOL_VERSION < 347
        AssetsManager::getInstance().Items().at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetBlockID()).at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetItemDamage())->GetName() != item_name
#else
        AssetsManager::getInstance().Items().at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetItemID())->GetName() != item_name
#endif
        )
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
        {
            std::cerr << "Something went wrong trying to get food from chest (Timeout)." << std::endl;
            return false;
        }
    }

    return true;
}

const bool MapCreatorBot::GetSomeBlocks(const std::string& food_name)
{
    std::vector<Position> chests = GetAllChestsAround(Position(200, 100, 200));
    std::shuffle(chests.begin(), chests.end(), random_engine);

    short container_id;

    for (int i = 0; i < chests.size(); ++i)
    {
        int inventory_empty_slots = 0;
        int filled_slots = 0;
        // Count the number of empty slots in the player inventory
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            const std::map<short, Slot>& slots = inventory_manager->GetPlayerInventory()->GetSlots();
            for (auto it = slots.begin(); it != slots.end(); ++it)
            {
                if (it->first >= 9/*Window::INVENTORY_STORAGE_START*/ &&
                    it->first < 45 /*Window::INVENTORY_OFFHAND_INDEX*/ &&
                    it->second.IsEmptySlot())
                {
                    inventory_empty_slots++;
                }
            }
        }

        // If we can't open this chest for a reason
        if (!OpenContainer(chests[i]))
        {
            continue;
        }

        while(true)
        {
            short container_src_slot_index = -1;
            short container_dst_slot_index = -1;
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                container_id = inventory_manager->GetFirstOpenedWindowId();
                if (container_id == -1)
                {
                    continue;
                }
                const std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);

                const short first_player_index = ((int)container->GetType() + 1) * 9;

                const std::map<short, Slot>& slots = container->GetSlots();

                // Find a non-empty slot to pickup
                for (auto it = slots.begin(); it != slots.end(); ++it)
                {
                    if (it->first >= 0
                        && it->first < first_player_index
                        && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                        && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second..GetItemDamage())->GetName() != food_name
#else
                        && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() != food_name
#endif
                        )
                    {
                        container_src_slot_index = it->first;
                        break;
                    }
                }

                // Find an empty inventory slot to get the items
                for (auto it = slots.begin(); it != slots.end(); ++it)
                {
                    if (it->first >= first_player_index
                        && it->second.IsEmptySlot())
                    {
                        container_dst_slot_index = it->first;
                        break;
                    }
                }
            }

            if (container_src_slot_index != -1 &&
                container_dst_slot_index != -1)
            {
                // Try to take the items and set them in the first free slot
                if (SwapItemsInContainer(container_id, container_src_slot_index, container_dst_slot_index))
                {
                    filled_slots++;
                }
            }
            // This means either the chest is empty
            // or the inventory is full
            else
            {
                break;
            }
        }

        CloseContainer(container_id);

        // Wait until player inventory is updated after the container is closed
        auto start = std::chrono::system_clock::now();
        int inventory_empty_slots_after = 0;
        while (inventory_empty_slots_after != inventory_empty_slots - filled_slots)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to get items from chest (Timeout)." << std::endl;
                return false;
            }

            inventory_empty_slots_after = 0;
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                const std::map<short, Slot>& slots = inventory_manager->GetPlayerInventory()->GetSlots();
                for (auto it = slots.begin(); it != slots.end(); ++it)
                {
                    if (it->first >= 9/*Window::INVENTORY_STORAGE_START*/ &&
                        it->first < 45 /*Window::INVENTORY_OFFHAND_INDEX*/ &&
                        it->second.IsEmptySlot())
                    {
                        inventory_empty_slots_after++;
                    }
                }
            }
        
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        // We filled up the inventory, no need to check
        // other chests for more items
        if (inventory_empty_slots - filled_slots == 0)
        {
            break;
        }
    }

    return true;
}

const std::set<std::string> MapCreatorBot::GetBlocksAvailableInInventory() const
{
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
    return blocks_in_inventory;
}

const bool MapCreatorBot::FindNextPositionToPlaceBlock(const std::set<std::string>& available, Position& out_pos, std::string& out_item, PlayerDiggingFace& out_face)
{
    Position start_pos;

    start_pos.x = std::min(end.x, std::max(start.x, (int)std::floor(entity_manager->GetLocalPlayer()->GetX())));
    start_pos.y = std::min(end.y, std::max(start.y, (int)std::floor(entity_manager->GetLocalPlayer()->GetY())));
    start_pos.z = std::min(end.z, std::max(start.z, (int)std::floor(entity_manager->GetLocalPlayer()->GetZ())));

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
        // 3) it does not already match the desired build
        // 4) it has a block under or next to it so we can put the new block
        for (auto it = to_explore.begin(); it != to_explore.end(); ++it)
        {
            const Position pos = *it;
            
            const int target_palette = target[pos.x - start.x][pos.y - start.y][pos.z - start.z];
            const std::string& target_name = palette[target_palette];
                
            if (target_palette == -1)
            {
                continue;
            }

            if (available.find(target_name) == available.end())
            {
                continue;
            }

            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                const Block* block = world->GetBlock(pos);

                if (!block)
                {
                    continue;
                }

                if (block->GetBlockstate()->GetName() == target_name)
                {
                    continue;
                }

                for (int i = 0; i < neighbour_offsets.size(); ++i)
                {
                    const Block* neighbour_block = world->GetBlock(pos + neighbour_offsets[i]);

                    if (neighbour_block && !neighbour_block->GetBlockstate()->IsAir())
                    {
                        pos_candidates.push_back(pos);
                        item_candidates.push_back(target_name);
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
                std::lock_guard<std::mutex> entity_manager_lock(entity_manager->GetMutex());
                for (auto it = entity_manager->GetEntities().begin(); it != entity_manager->GetEntities().end(); ++it)
                {
                    if (it->second->GetType() == EntityType::Player)
                    {
                        other_player_pos.push_back(it->second->GetPosition());
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
            int selected_index = max_dist_indices.size() == 1 ? 0 : max_dist_indices[std::uniform_int_distribution<int>(0, max_dist_indices.size() - 1)(random_engine)];
            
            out_pos = pos_candidates[selected_index];
            out_item = item_candidates[selected_index];
            out_face = face_candidates[selected_index];

            return true;
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

    return false;
}

void MapCreatorBot::CreateMap()
{
    const std::string food_name = "minecraft:golden_carrot"; // Yeah hardcoding is bad, don't do this at home

    int block_placing_fail = 0;
    while (true)
    {
        // Check if we have food,
        // and if not, go get some in a chest
        if (!SetItemInHand(food_name, Hand::Left))
        {
            if (!GetSomeFood(food_name))
            {
                std::cerr << "Error, can't find food anywhere" << std::endl;
                break;
            }
            
            if (!SetItemInHand(food_name, Hand::Left))
            {
                std::cerr << "Error, can't set food in my off-hand" << std::endl;
                break;
            }
        }

        // Check if food is not at max, if yes, eat
        if (entity_manager->GetLocalPlayer()->GetFood() < 20.0f &&
            !Eat(food_name, true))
        {
            std::cerr << "Error, can't eat!" << std::endl;
            break;
        }

        // List all blocks available in
        // the inventory
        std::set<std::string> blocks_in_inventory = GetBlocksAvailableInInventory();

        // If empty, go fill the inventory
        // with many blocks
        if (blocks_in_inventory.empty())
        {
            if (!GetSomeBlocks(food_name))
            {
                std::cerr << "Warning, error trying to get blocks from chests" << std::endl;
            }
            
            blocks_in_inventory = GetBlocksAvailableInInventory();

            if (blocks_in_inventory.empty())
            {
                std::cout << "No more block in chests, I will stop here" << std::endl;
                break;
            }
        }

        // search for a block to place
        // and present in the inventory
        Position block_to_place;
        std::string item_to_place;
        PlayerDiggingFace face_to_place;
        if (!FindNextPositionToPlaceBlock(blocks_in_inventory, block_to_place, item_to_place, face_to_place))
        {
            // If no block in the inventory fits
            // Remove all the blocks in the inventory into
            // chests
            std::cerr << "No more suitable locations, give up" << std::endl;
            break;
            //EmptyInventoryInChests();
        }
        else
        {
            if (!PlaceBlock(item_to_place, block_to_place, face_to_place, true))
            {
                block_placing_fail++;
                if (block_placing_fail > 5)
                {
                    std::cerr << "No more suitable locations where I can go, give up" << std::endl;
                    break;
                    //EmptyInventoryInChests();
                }
            }
            else
            {
                block_placing_fail = 0;
            }
        }
    }
}
