#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Inventory.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    InventoryManager::InventoryManager()
    {
        index_hotbar_selected = 0;
        cursor = Slot();
    }

    std::mutex& InventoryManager::GetMutex()
    {
        return inventory_manager_mutex;
    }

    void InventoryManager::SetSlot(const short window_id, const short index, const Slot &slot)
    {
        auto it = inventories.find(window_id);

        if (it == inventories.end())
        {
            inventories[window_id] = std::shared_ptr<Inventory>(new Inventory);
            inventories[window_id]->GetSlots()[index] = slot;
        }
        else
        {
            it->second->GetSlots()[index] = slot;
        }
    }

    std::shared_ptr<Inventory> InventoryManager::GetInventory(const short window_id)
    {
        auto it = inventories.find(window_id);
        if (it == inventories.end())
        {
            return nullptr;
        }
        return it->second;
    }
    
    std::shared_ptr<Inventory> InventoryManager::GetPlayerInventory()
    {
        return GetInventory(Inventory::PLAYER_INVENTORY_INDEX);
    }
    
    const std::shared_ptr<Inventory> InventoryManager::GetInventory(const short window_id) const
    {
        auto it = inventories.find(window_id);
        if (it == inventories.end())
        {
            return nullptr;
        }
        return it->second;
    }

    const std::shared_ptr<Inventory> InventoryManager::GetPlayerInventory() const
    {
        return GetInventory(Inventory::PLAYER_INVENTORY_INDEX);
    }
    
    const Slot InventoryManager::GetHotbarSelected() const
    {
        const std::shared_ptr<Inventory> inventory = GetPlayerInventory();

        if (!inventory)
        {
            return Slot();
        }

        inventory->GetSlot(Inventory::HOTBAR_START_INDEX + index_hotbar_selected);
    }

    void InventoryManager::EraseInventory(const short window_id)
    {
        inventories.erase(window_id);
    }

    void InventoryManager::AddInventory(const short window_id)
    {
        inventories[window_id] = std::shared_ptr<Inventory>(new Inventory);
    }

    void InventoryManager::SetHotbarSelected(const short index)
    {
        index_hotbar_selected = index;
    }

    const Slot& InventoryManager::GetCursor() const
    {
        return cursor;
    }

    void InventoryManager::SetCursor(const Slot &c)
    {
        cursor = c;
    }
} //Botcraft