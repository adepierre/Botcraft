#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

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
            inventories[window_id] = std::shared_ptr<Window>(new Window);
            inventories[window_id]->SetSlot(index, slot);
        }
        else
        {
            it->second->SetSlot(index, slot);
        }
    }

    std::shared_ptr<Window> InventoryManager::GetWindow(const short window_id)
    {
        auto it = inventories.find(window_id);
        if (it == inventories.end())
        {
            return nullptr;
        }
        return it->second;
    }
    
    std::shared_ptr<Window> InventoryManager::GetPlayerInventory()
    {
        return GetWindow(Window::PLAYER_INVENTORY_INDEX);
    }

    const short InventoryManager::GetIndexHotbarSelected() const
    {
        return index_hotbar_selected;
    }
    
    const std::shared_ptr<Window> InventoryManager::GetWindow(const short window_id) const
    {
        auto it = inventories.find(window_id);
        if (it == inventories.end())
        {
            return nullptr;
        }
        return it->second;
    }

    const std::shared_ptr<Window> InventoryManager::GetPlayerInventory() const
    {
        return GetWindow(Window::PLAYER_INVENTORY_INDEX);
    }
    
    const Slot& InventoryManager::GetHotbarSelected() const
    {
        const std::shared_ptr<Window> inventory = GetPlayerInventory();

        if (!inventory)
        {
            return Window::EMPTY_SLOT;
        }

        return inventory->GetSlot(Window::INVENTORY_HOTBAR_START + index_hotbar_selected);
    }

    void InventoryManager::EraseInventory(const short window_id)
    {
        inventories.erase(window_id);
    }

    void InventoryManager::AddInventory(const short window_id)
    {
        inventories[window_id] = std::shared_ptr<Window>(new Window);
    }

    void InventoryManager::SetHotbarSelected(const short index)
    {
        index_hotbar_selected = index;
    }

    const Slot& InventoryManager::GetCursor() const
    {
        return cursor;
    }

    void InventoryManager::AddPendingTransaction(const std::shared_ptr<ClickWindow> transaction)
    {
        if (!transaction)
        {
            return;
        }
        pending_transactions.push_back(*transaction);
    }

    void InventoryManager::SetCursor(const Slot& c)
    {
        cursor = c;
    }

    void InventoryManager::Handle(ProtocolCraft::Message& msg)
    {

    }

    void InventoryManager::Handle(ProtocolCraft::SetSlot& msg)
    {
        std::lock_guard<std::mutex> inventories_locker(inventory_manager_mutex);

        if (msg.GetWindowId() == -1 && msg.GetSlot() == -1)
        {
            SetCursor(msg.GetSlotData());
        }
        else if (msg.GetWindowId() == -2)
        {
            SetSlot(Window::PLAYER_INVENTORY_INDEX, msg.GetSlot(), msg.GetSlotData());
        }
        else if (msg.GetWindowId() >= 0)
        {
            SetSlot(msg.GetWindowId(), msg.GetSlot(), msg.GetSlotData());
        }
        else
        {
            std::cerr << "Warning, unknown window called in SetSlot: " << msg.GetWindowId() << ", " << msg.GetSlot() << std::endl;
        }
    }

    void InventoryManager::Handle(ProtocolCraft::WindowItems& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        for (int i = 0; i < msg.GetCount(); ++i)
        {
            SetSlot(msg.GetWindowId(), i, msg.GetSlotData()[i]);
        }
    }

    void InventoryManager::Handle(ProtocolCraft::OpenWindow& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        AddInventory(msg.GetWindowId());
    }

    void InventoryManager::Handle(ProtocolCraft::HeldItemChangeClientbound& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        SetHotbarSelected(msg.GetSlot());
    }

    void InventoryManager::Handle(ProtocolCraft::ConfirmTransactionClientbound& msg)
    {
        // BaseClient is in charge of the apologize in this case
        if (!msg.GetAccepted())
        {
            return;
        }

        auto transaction = pending_transactions.end();

        for (auto it = pending_transactions.begin(); it != pending_transactions.end(); ++it)
        {
            if (it->GetWindowId() == msg.GetWindowId()
                && it->GetActionNumber() == msg.GetActionNumber())
            {
                transaction = it;
                break;
            }
        }

        // Get the corresponding transaction
        if (transaction == pending_transactions.end())
        {
            std::cerr << "Warning, server accepted an unknown transaction" << std::endl;
            return;
        }

        // Check the window exists
        std::shared_ptr<Window> window = GetWindow(transaction->GetWindowId());
        if (!window)
        {
            std::cerr << "Warning, server accepted a transaction for an unknown window" << std::endl;
            pending_transactions.erase(transaction);
            return;
        }


        // Process the transaction
        switch (transaction->GetMode())
        {
        case 0:
            // "Left click"
            if (transaction->GetButton() == 0)
            {
                const Slot& switched_slot = window->GetSlot(transaction->GetSlot());
                window->SetSlot(transaction->GetSlot(), cursor);
                cursor = switched_slot;
            }
            break;
        default:
            break;
        }

        pending_transactions.erase(transaction);
    }


} //Botcraft