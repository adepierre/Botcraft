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
        pending_transactions.erase(window_id);
        transaction_states.erase(window_id);
    }

    const TransactionState InventoryManager::GetTransactionState(const short window_id, const int transaction_id)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        auto it = transaction_states.find(window_id);

        if (it == transaction_states.end())
        {
            std::cerr << "Error, asking state of a transaction for a closed window" << std::endl;
            return TransactionState::Refused;
        }

        auto it2 = it->second.find(transaction_id);

        if (it2 == it->second.end())
        {
            std::cerr << "Error, asking state of an unknown transaction" << std::endl;
            return TransactionState::Refused;
        }

        return it2->second;
    }

    void InventoryManager::AddInventory(const short window_id, const InventoryType window_type)
    {
        inventories[window_id] = std::shared_ptr<Window>(new Window(window_type));
        pending_transactions[window_id] = std::map<short, std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> >();
        transaction_states[window_id] = std::map<short, TransactionState>();
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
        pending_transactions[transaction->GetContainerId()].insert(std::make_pair(transaction->GetUid(), transaction));
        transaction_states[transaction->GetContainerId()].insert(std::make_pair(transaction->GetUid(), TransactionState::Waiting));
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
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);

        // Update the new state of the transaction
        auto it_container = transaction_states.find(msg.GetContainerId());
        if (it_container == transaction_states.end())
        {
            transaction_states[msg.GetContainerId()] = std::map<short, TransactionState>();
            it_container = transaction_states.find(msg.GetContainerId());
        }
        it_container->second[msg.GetUid()] = msg.GetAccepted() ? TransactionState::Accepted : TransactionState::Refused;

        auto container_transactions = pending_transactions.find(msg.GetContainerId());

        if (container_transactions == pending_transactions.end())
        {
            std::cerr << "Warning, the server accepted a transaction for an unknown container" << std::endl;
            return;
        }

        auto transaction = container_transactions->second.find(msg.GetUid());

        // Get the corresponding transaction
        if (transaction == container_transactions->second.end())
        {
            std::cerr << "Warning, server accepted an unknown transaction Uid" << std::endl;
            return;
        }

        if (msg.GetAccepted())
        {
            // Get the container
            std::shared_ptr<Window> window = GetWindow(transaction->second->GetContainerId());

            // Process the transaction
            switch (transaction->second->GetClickType())
            {
            case 0:
                // "Left click"
                if (transaction->second->GetButtonNum() == 0)
                {
                    const Slot switched_slot = window->GetSlot(transaction->second->GetSlotNum());
                    window->SetSlot(transaction->second->GetSlotNum(), cursor);
                    cursor = switched_slot;
                }
                break;
            default:
                break;
            }
        }

        // Remove the transaction from the waiting state
        container_transactions->second.erase(transaction);
    }


} //Botcraft