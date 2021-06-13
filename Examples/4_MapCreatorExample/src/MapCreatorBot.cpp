#include <sstream>
#include <fstream>
#include <algorithm>

#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/World/Chunk.hpp>
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
    started = false;
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
    
    if (splitted.size() > 0 && splitted[0] == "start")
    {
        LaunchMapCreation();
    }
    else if (splitted.size() > 1 
        && splitted[0] == network_manager->GetMyName()
        && splitted[1] == "check")
    {
        const bool details = splitted.size() > 2 && splitted[2] == "details";

        std::thread check_thread(&MapCreatorBot::CheckCompletion, this, true, true, details);
        check_thread.detach();
    }
    else
    {
        return;
    }
}

const bool MapCreatorBot::LoadNBTFile(const std::string& path, const Position& offset_, const std::string& temp_block, const bool print_info)
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
    try
    {
        loaded_file.Read(it, length);
    }
    catch (const std::exception&)
    {
        std::cout << "Error loading NBT file. Make sure the file is uncompressed (you can change the extension to .zip and simply unzip it)" << std::endl;
        return false;
    }

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

    size = max - min + Position(1, 1, 1);
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

        if (print_info)
        {
            std::cout << "Removed the bottom " << removed_layers << " layer" << (removed_layers > 1 ? "s" : "") << std::endl;
        }
    }

    if (print_info)
    {
        std::cout << "Total size: " << size << std::endl;

        std::cout << "Block needed:" << std::endl;
        for (auto it = num_blocks_used.begin(); it != num_blocks_used.end(); ++it)
        {
            std::cout << "\t" << palette[it->first] << "\t\t" << it->second << std::endl;
        }

        // Check if some block can't be placed (flying blocks)
        std::cout << "Flying blocks, you might have to place them yourself: " << std::endl;

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
                            std::cout << start + target_pos << "\t" << palette[target_id] << std::endl;
                        }
                    }
                }
            }
        }
    }

    return true;
}

void MapCreatorBot::LaunchMapCreation()
{
    std::thread map_creation_thread(&MapCreatorBot::CreateMap, this);
    map_creation_thread.detach();
}

const std::vector<Position> MapCreatorBot::GetAllChestsAround() const
{
    std::vector<Position> output;

    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
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
                            output.push_back(checked_position);
                        }
                    }
                }
            }
        }
    }

    return output;
}

const bool MapCreatorBot::GetSomeFood(const std::string& item_name)
{
    std::vector<Position> chests = GetAllChestsAround();
    std::shuffle(chests.begin(), chests.end(), random_engine);

    short container_id;

    for (int i = 0; i < chests.size(); ++i)
    {
        // If we can't open this chest for a reason
        if (!OpenContainer(chests[i]))
        {
            continue;
        }

        bool has_taken = false;
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
                        && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() == item_name
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
                if (SwapItemsInContainer(container_id, slots_src[src_index], player_dst))
                {
                    has_taken = true;
                    break;
                }
            }
            // This means the chest doesn't have any food
            else
            {
                break;
            }
        }

        CloseContainer(container_id);

        if (!has_taken)
        {
            continue;
        }

        // Wait until player inventory is updated after the container is closed
        auto start = std::chrono::system_clock::now();
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

        // No need to continue loooking in the other chests
        break;
    }

    return true;
}

const bool MapCreatorBot::SwapChestsInventory(const std::string& food_name, const bool take)
{
    std::vector<Position> chests = GetAllChestsAround();

    while (true)
    {
        if (chests.size() == 0)
        {
            return false;
        }

        // Select a chest
        int chest_index = chests.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, chests.size() - 1)(random_engine);

        // If we can't open this chest for a reason
        if (!OpenContainer(chests[chest_index]))
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

            first_player_index = ((int)container->GetType() + 1) * 9;

            const std::map<short, Slot>& slots = container->GetSlots();

            slots_src.reserve(slots.size());
            slots_dst.reserve(slots.size());

            for (auto it = slots.begin(); it != slots.end(); ++it)
            {
                // If take, chest is src
                if (it->first >= 0
                    && it->first < first_player_index
                    && take
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
                    && take
                    && it->second.IsEmptySlot())
                {
                    slots_dst.push_back(it->first);
                }
                // If !take, chest is dst
                else if (it->first >= 0
                    && it->first < first_player_index
                    && !take
                    && it->second.IsEmptySlot())
                {
                    slots_dst.push_back(it->first);
                }
                // If !take, player is src
                else if (it->first >= first_player_index
                    && !take
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

        bool swap_success = false;
        int dst_index = -1;
        int src_index = -1;
        if (slots_src.size() > 0 &&
            slots_dst.size() > 0)
        {
            // Select a random slot in both src and dst
            dst_index = slots_dst.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, slots_dst.size() - 1)(random_engine);
            src_index = slots_src.size() == 1 ? 0 : std::uniform_int_distribution<int>(0, slots_src.size() - 1)(random_engine);

            // Try to swap the items
            swap_success = SwapItemsInContainer(container_id, slots_src[src_index], slots_dst[dst_index]);
        }
        
        // Close the chest
        CloseContainer(container_id);

        // The chest was empty/full, remove it from the list
        if ((take && slots_src.size() == 0) ||
            (!take && slots_dst.size() == 0))
        {
            chests.erase(chests.begin() + chest_index);
            continue;
        }
        // The player inventory was full/empty, end the function
        else if ((take && slots_dst.size() == 0) ||
                 (!take && slots_src.size() == 0))
        {
            return true;
        }

        if (!swap_success)
        {
            continue;
        }
        
        // Wait for the confirmation from the server
        auto start = std::chrono::system_clock::now();
        const short checked_slot_index = (take ? slots_dst[dst_index] : slots_src[src_index]) - first_player_index + 9; /*Window::INVENTORY_STORAGE_START*/
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to get items from chest (Timeout)." << std::endl;
                return false;
            }
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                const Slot& slot = inventory_manager->GetPlayerInventory()->GetSlot(checked_slot_index);
                if ((take && !slot.IsEmptySlot()) ||
                    (!take && slot.IsEmptySlot()))
                {
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

const bool MapCreatorBot::FindNextTask(const std::set<std::string>& available, Position& out_pos, std::string& out_item, PlayerDiggingFace& out_face)
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
            const std::string& target_name = palette[target_palette];
            std::shared_ptr<Blockstate> blockstate;
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                const Block* block = world->GetBlock(pos);

                if (!block)
                {
#if PROTOCOL_VERSION < 347
                    blockstate = AssetsManager::getInstance().Blockstates().at(0).at(0);
#else
                    blockstate = AssetsManager::getInstance().Blockstates().at(0);
#endif
                }
                else
                {
                    blockstate = block->GetBlockstate();
                }
            }

            // Empty space requiring block placement
            if (target_palette != -1
                && blockstate->IsAir()
                && available.find(target_name) != available.end())
            {
                for (int i = 0; i < neighbour_offsets.size(); ++i)
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());
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
            // Wrong block requiring digging
            else if ((target_palette != -1 && !blockstate->IsAir() && target_name != blockstate->GetName())
                || (target_palette == -1 && !blockstate->IsAir()))
            {
                for (int i = 0; i < neighbour_offsets.size(); ++i)
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());
                    const Block* neighbour_block = world->GetBlock(pos + neighbour_offsets[i]);

                    if (neighbour_block && !neighbour_block->GetBlockstate()->IsAir())
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

const bool MapCreatorBot::CheckCompletion(const bool full, const bool print_errors, const bool print_details) const
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

void MapCreatorBot::CreateMap()
{
    if (started)
    {
        return;
    }

    try
    {
        started = true;
        const std::string food_name = "minecraft:golden_carrot"; // Yeah hardcoding is bad, don't do this at home

        int task_fail = 0;
        while (true)
        {
            // Check if we have food,
            // and if not, go get some in a chest
            if (!SetItemInHand(food_name, Hand::Left))
            {
                if (!GetSomeFood(food_name))
                {
                    std::cout << "[" << network_manager->GetMyName() << "]: Can't find food anywhere" << std::endl;
                    break;
                }

                if (!SetItemInHand(food_name, Hand::Left))
                {
                    std::cout << "[" << network_manager->GetMyName() << "]: Can't set food in my off-hand" << std::endl;
                    break;
                }
            }

            // Check if food is not at max, if yes, eat
            if (entity_manager->GetLocalPlayer()->GetFood() < 20.0f &&
                !Eat(food_name, true))
            {
                std::cout << "[" << network_manager->GetMyName() << "]: Can't eat!" << std::endl;
                break;
            }

            // List all blocks available in
            // the inventory
            std::set<std::string> blocks_in_inventory = GetBlocksAvailableInInventory();

            // If empty, go fill the inventory
            // with many blocks
            if (blocks_in_inventory.empty())
            {
                SwapChestsInventory(food_name, true);

                blocks_in_inventory = GetBlocksAvailableInInventory();

                if (blocks_in_inventory.empty())
                {
                    std::cout << "[" << network_manager->GetMyName() <<  "]: No more block in chests, I will stop here. You can restart me by saying start in the chat." << std::endl;
                    break;
                }
            }

            // search for a task to perform
            Position block_position;
            std::string item;
            PlayerDiggingFace face;
            if (!FindNextTask(blocks_in_inventory, block_position, item, face))
            {
                if (CheckCompletion(false, false, false))
                {
                    std::cout << "Done!" << std::endl;
                    break;
                }
                // If no block in the inventory fits
                // Put all the blocks in the inventory into
                // chests
                SwapChestsInventory(food_name, false);
            }
            else
            {
                bool action_success;
                if (item.empty())
                {
                    action_success = DigAt(block_position, face);
                }
                else
                {
                    action_success = PlaceBlock(item, block_position, face, true);
                }
                if (!action_success)
                {
                    task_fail++;
                    if (task_fail > 5)
                    {
                        task_fail = 0;
                        SwapChestsInventory(food_name, false);
                    }
                    else
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(3));
                    }
                }
                else
                {
                    task_fail = 0;
                }
            }
        }
        started = false;
    }
    catch (...)
    {
        std::cout << "Catched" << std::endl;
        started = false;
        should_be_closed = true;
        return;
    }
}
