#pragma once

#include "TestManager.hpp"

#include <memory>
#include <stdexcept>

#include <botcraft/AI/TemplatedBehaviourClient.hpp>
#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/Game/ManagersClient.hpp>
#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>

template<class ClientType = Botcraft::ManagersClient>
std::unique_ptr<ClientType> SetupTestBot(const Botcraft::Vector3<double>& offset = { 0,0,0 }, const Botcraft::GameType gamemode = Botcraft::GameType::Survival)
{
    std::string botname;
    std::unique_ptr<ClientType> bot = TestManager::GetInstance().GetBot<ClientType>(botname, gamemode);

    const Botcraft::Vector3<double> pos = offset + TestManager::GetInstance().GetCurrentOffset();
    TestManager::GetInstance().Teleport(botname, pos);

    // Wait for bot to register teleportation
    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    if (!Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            return local_player->GetPosition().SqrDist(pos) < 1.0;
        }, 5000))
    {
        throw std::runtime_error("Timeout waiting " + botname + " to register teleportation");
    }

    // Wait for bot to load center and corner view_distance blocks
    std::shared_ptr<Botcraft::World> world = bot->GetWorld();
    const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(Botcraft::CHUNK_WIDTH)));
    const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(Botcraft::CHUNK_WIDTH)));
    // -1 because sometimes corner chunks are not sent, depending on where you are on the current chunk
    const int view_distance = MinecraftServer::options.view_distance - 1;
    std::vector<std::pair<int, int>> wait_loaded = {
        {chunk_x * Botcraft::CHUNK_WIDTH, chunk_z * Botcraft::CHUNK_WIDTH},
        {(chunk_x + view_distance) * Botcraft::CHUNK_WIDTH - 1, (chunk_z + view_distance) * Botcraft::CHUNK_WIDTH - 1},
        {(chunk_x - view_distance) * Botcraft::CHUNK_WIDTH, (chunk_z + view_distance) * Botcraft::CHUNK_WIDTH - 1},
        {(chunk_x + view_distance) * Botcraft::CHUNK_WIDTH - 1, (chunk_z - view_distance) * Botcraft::CHUNK_WIDTH},
        {(chunk_x - view_distance) * Botcraft::CHUNK_WIDTH, (chunk_z - view_distance) * Botcraft::CHUNK_WIDTH}
    };

    if (!Botcraft::Utilities::WaitForCondition([&]() {
            for (size_t i = 0; i < wait_loaded.size(); ++i)
            {
                if (!bot->GetWorld()->IsLoaded(Botcraft::Position(wait_loaded[i].first, 2, wait_loaded[i].second)))
                {
                    return false;
                }
            }
            return true;
        }, 15000))
    {
        throw std::runtime_error("Timeout waiting " + botname + " to load surroundings");
    }

    return bot;
}

#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>
#include <botcraft/Game/Inventory/Window.hpp>

template<class ClientType = Botcraft::SimpleBehaviourClient>
bool GiveItem(std::unique_ptr<ClientType>& bot, const std::string& item_name, const std::string& item_pretty_name, const int quantity = 1)
{
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const Botcraft::Item* item = Botcraft::AssetsManager::getInstance().GetItem(Botcraft::AssetsManager::getInstance().GetItemID(item_name));
    short receiving_slot = -1;
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        const std::map<short, ProtocolCraft::Slot>& slots = inventory_manager->GetPlayerInventory()->GetSlots();
        for (short i = Botcraft::Window::INVENTORY_HOTBAR_START; i < Botcraft::Window::INVENTORY_OFFHAND_INDEX; ++i)
        {
            if (slots.at(i).IsEmptySlot() ||
                (item->GetId() == slots.at(i).GetItemID() && item->GetStackSize() >= slots.at(i).GetItemCount() + quantity))
            {
                receiving_slot = i;
                break;
            }
        }
        // No slot available in the hotbar, check the main inventory
        if (receiving_slot == -1)
        {
            for (short i = Botcraft::Window::INVENTORY_STORAGE_START; i < Botcraft::Window::INVENTORY_HOTBAR_START; ++i)
            {
                if (slots.at(i).IsEmptySlot())
                {
                    receiving_slot = i;
                    break;
                }
            }
        }
        if (receiving_slot == -1)
        {
            return false;
        }
    }

    const std::string& botname = bot->GetNetworkManager()->GetMyName();
    MinecraftServer::GetInstance().SendLine("give " + botname + " " + item_name + " " + std::to_string(quantity));
    MinecraftServer::GetInstance().WaitLine(".*?: (?:Given|Gave " + std::to_string(quantity) + ") \\[" + item_pretty_name + "\\](?: \\* " + std::to_string(quantity) + ")? to " + botname + ".*", 5000);
    return Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(bot->GetInventoryManager()->GetMutex());
            return !bot->GetInventoryManager()->GetPlayerInventory()->GetSlot(receiving_slot).IsEmptySlot();
        }, 5000);
}
