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

MapCreatorBot::MapCreatorBot(const std::string& map_file_, const Position& offset_, const bool use_renderer_) : InterfaceClient(use_renderer_, false)
{
    LoadNBTFile(map_file_);
    offset = offset_;

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

void MapCreatorBot::LoadNBTFile(const std::string& path)
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

    std::shared_ptr<TagList> palette_tag = std::dynamic_pointer_cast<TagList>(loaded_file.GetTag("palette"));

    for (int i = 0; i < palette_tag->GetValues().size(); ++i)
    {
        std::shared_ptr<TagCompound> compound = std::dynamic_pointer_cast<TagCompound>(palette_tag->GetValues()[i]);
        const std::string& block_name = std::dynamic_pointer_cast<TagString>(compound->GetValues().at("Name"))->GetValue();
        palette[i] = block_name;
    }

    Position size;
    std::shared_ptr<TagList> size_tag = std::dynamic_pointer_cast<TagList>(loaded_file.GetTag("size"));
    size.x = std::dynamic_pointer_cast<TagInt>(size_tag->GetValues()[0])->GetValue();
    size.y = std::dynamic_pointer_cast<TagInt>(size_tag->GetValues()[1])->GetValue();
    size.z = std::dynamic_pointer_cast<TagInt>(size_tag->GetValues()[2])->GetValue();

    // Fill the target area with air (-1)
    target = std::vector<std::vector<std::vector<int> > >(size.x, std::vector<std::vector<int> >(size.y, std::vector<int>(size.z, -1)));
    
    // Read all block to place
    std::shared_ptr<TagList> blocks_tag = std::dynamic_pointer_cast<TagList>(loaded_file.GetTag("blocks"));
    for (int i = 0; i < blocks_tag->GetValues().size(); ++i)
    {
        std::shared_ptr<TagCompound> compound = std::dynamic_pointer_cast<TagCompound>(blocks_tag->GetValues()[i]);
        int state = std::dynamic_pointer_cast<TagInt>(compound->GetValues().at("state"))->GetValue();
        std::shared_ptr<TagList> pos_list = std::dynamic_pointer_cast<TagList>(compound->GetValues().at("pos"));
        const int x = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[0])->GetValue();
        const int y = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[1])->GetValue();
        const int z = std::dynamic_pointer_cast<TagInt>(pos_list->GetValues()[2])->GetValue();

        target[x][y][z] = state;
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
    std::vector<Position> chests = GetAllChestsAround(Position(150, 100, 150));
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
    std::vector<Position> chests = GetAllChestsAround(Position(150, 100, 150));
    std::shuffle(chests.begin(), chests.end(), random_engine);

    int inventory_empty_slots = 0;
    int filled_slots = 0;
    short container_src_slot_index = -1;
    short container_dst_slot_index = -1;
    short container_id;

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

    for (int i = 0; i < chests.size(); ++i)
    {
        // If we can't open this chest for a reason
        if (!OpenContainer(chests[i]))
        {
            continue;
        }

        while(true)
        {
            container_src_slot_index = -1;
            container_dst_slot_index = -1;
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
                        && !it->second.IsEmptySlot())
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
                // Take the items and set them in the first free slot
                if (!SwapItemsInContainer(container_id, container_src_slot_index, container_dst_slot_index))
                {
                    CloseContainer(container_id);
                    return false;
                }
                else
                {
                    filled_slots++;
                }
            }
            else
            {
                break;
            }
        }

        CloseContainer(container_id);

        // There was no free slot to get the items,
        // we don't need to check other chests
        if (container_dst_slot_index == -1)
        {
            break;
        }
    }

    // Wait for the inventory to be fully updated
    // after closing the last chest
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
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

void MapCreatorBot::CreateMap()
{
    const std::string food_name = "minecraft:golden_carrot"; // Yeah hardcoding is bad and all

    std::cout << "I am hungry: " << entity_manager->GetLocalPlayer()->GetFood() << std::endl;
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

        // Check if we are hungry, if yes, eat
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
                std::cerr << "Error, can't find blocks anywhere" << std::endl;
                break;
            }
            
            blocks_in_inventory = GetBlocksAvailableInInventory();

            if (blocks_in_inventory.empty())
            {
                std::cout << "No more block in chests, I will stop here" << std::endl;
                break;
            }
        }

        break;
        // search for the closest block to place
        // and present in the inventory

        // If no block in the inventory fits
        // Remove all the blocks in the inventory into
        // chests

    }
}
