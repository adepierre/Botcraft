#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    InventoryManager::InventoryManager()
    {
        index_hotbar_selected = 0;
        cursor = Slot();
        inventories[Window::PLAYER_INVENTORY_INDEX] = std::shared_ptr<Window>(new Window(InventoryType::Default));
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
            std::cerr << "Warning, trying to add item in an unknown window with id: " << window_id << std::endl;
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

    const short InventoryManager::GetFirstOpenedWindowId() const
    {
        for (auto it = inventories.begin(); it != inventories.end(); ++it)
        {
            if (it->first != Window::PLAYER_INVENTORY_INDEX &&
                it->second->GetSlots().size() > 0)
            {
                return it->first;
            }
        }

        return -1;
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

    const ProtocolCraft::Slot& InventoryManager::GetOffHand() const
    {
        const std::shared_ptr<Window> inventory = GetPlayerInventory();

        if (!inventory)
        {
            return Window::EMPTY_SLOT;
        }

        return inventory->GetSlot(Window::INVENTORY_OFFHAND_INDEX);
    }

    void InventoryManager::EraseInventory(const short window_id)
    {
        inventories.erase(window_id);
    }

    const bool InventoryManager::IsTransactionAccepted(const short window_id, const int transaction_id)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        auto transaction = pending_transactions.end();

        for (auto it = pending_transactions.begin(); it != pending_transactions.end(); ++it)
        {
            if (it->GetContainerId() == window_id
                && it->GetUid() == transaction_id)
            {
                return false;
            }
        }
        return true;
    }

    void InventoryManager::AddInventory(const short window_id, const InventoryType window_type)
    {
        inventories[window_id] = std::shared_ptr<Window>(new Window(window_type));
    }

    void InventoryManager::SetHotbarSelected(const short index)
    {
        index_hotbar_selected = index;
    }

    const Slot& InventoryManager::GetCursor() const
    {
        return cursor;
    }

    void InventoryManager::AddPendingTransaction(const std::shared_ptr<ServerboundContainerClickPacket> transaction)
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

    void InventoryManager::Handle(ProtocolCraft::ClientboundContainerSetSlotPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);

        if (msg.GetContainerId() == -1 && msg.GetSlot() == -1)
        {
            SetCursor(msg.GetItemStack());
        }
        else if (msg.GetContainerId() == -2)
        {
            SetSlot(Window::PLAYER_INVENTORY_INDEX, msg.GetSlot(), msg.GetItemStack());
        }
        else if (msg.GetContainerId() >= 0)
        {
            SetSlot(msg.GetContainerId(), msg.GetSlot(), msg.GetItemStack());
        }
        else
        {
            std::cerr << "Warning, unknown window called in SetSlot: " << msg.GetContainerId() << ", " << msg.GetSlot() << std::endl;
        }
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundContainerSetContentPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        int count = msg.GetSlotData().size();
        for (int i = 0; i < count; ++i)
        {
            SetSlot(msg.GetContainerId(), i, msg.GetSlotData()[i]);
        }
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundOpenScreenPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        AddInventory(msg.GetContainerId(), (InventoryType)msg.GetType());
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundSetCarriedItemPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        SetHotbarSelected(msg.GetSlot());
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundContainerAckPacket& msg)
    {
        // BaseClient is in charge of the apologize in this case
        if (!msg.GetAccepted())
        {
            return;
        }

        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        auto transaction = pending_transactions.end();

        for (auto it = pending_transactions.begin(); it != pending_transactions.end(); ++it)
        {
            if (it->GetContainerId() == msg.GetContainerId()
                && it->GetUid() == msg.GetUid())
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
        std::shared_ptr<Window> window = GetWindow(transaction->GetContainerId());
        if (!window)
        {
            std::cerr << "Warning, server accepted a transaction for an unknown window\n";
            std::cerr << msg.Serialize().serialize(false) << std::endl;
            pending_transactions.erase(transaction);
            return;
        }


        // Process the transaction
        switch (transaction->GetClickType())
        {
        case 0:
            // "Left click"
            if (transaction->GetButtonNum() == 0)
            {
                const Slot switched_slot = window->GetSlot(transaction->GetSlotNum());
                window->SetSlot(transaction->GetSlotNum(), cursor);
                cursor = switched_slot;
            }
            break;
        default:
            break;
        }

        pending_transactions.erase(transaction);
    }


} //Botcraft