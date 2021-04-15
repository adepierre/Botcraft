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

#include "MapCreatorBot.hpp"

using namespace Botcraft;
using namespace ProtocolCraft;

MapCreatorBot::MapCreatorBot(const std::string& map_file_, const bool use_renderer_, const bool is_afk_) : InterfaceClient(use_renderer_, is_afk_)
{
    map_file = map_file_;
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

    // Wait while player hotbar first slot is not the asked food
    auto start = std::chrono::system_clock::now();
    std::shared_ptr<Window> container = nullptr;
    while (AssetsManager::getInstance().Items().at(inventory_manager->GetPlayerInventory()->GetSlot(/*Window::INVENTORY_HOTBAR_START*/36).GetItemID())->GetName() != item_name)
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
        {
            std::cerr << "Something went wrong trying to get food from chest (Timeout)." << std::endl;
            return false;
        }
    }

    return true;
}

void MapCreatorBot::CreateMap()
{
    const std::string food_name = "minecraft:golden_carrot"; // Yeah hardcoding is bad and all

    std::cout << "I am hungry: " << entity_manager->GetLocalPlayer()->GetFood() << std::endl;
    while (true)
    {
        // Check if we have golden carrots,
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
        // a carrot
        if (entity_manager->GetLocalPlayer()->GetFood() < 20.0f &&
            !Eat(food_name, true))
        {
            std::cerr << "Error, can't eat!" << std::endl;
            break;
        }
        std::cout << "I have eaten, food: " << entity_manager->GetLocalPlayer()->GetFood() << std::endl;
        break;
        // List all blocks available in
        // the inventory

        // If empty, go fill the inventory
        // with many blocks

        // List all blocks available in the inventory

        // search for the closest block to place
        // and present in the inventory

        // If no block in the inventory fits
        // Remove all the blocks in the inventory into
        // chests

    }
    /*std::vector<Position> chests = GetAllChestsAround(Position(128, 50, 128));
    for (int i = 0; i < chests.size(); ++i)
    {
        if (GoTo(chests[i], true))
        {
            break;
        }
    }*/

}
