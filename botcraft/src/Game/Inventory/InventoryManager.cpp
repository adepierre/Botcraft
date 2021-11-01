#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

#include <iostream>

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
            // In 1.17+ we don't wait for any server confirmation, so this can potentially happen very often.
#if PROTOCOL_VERSION < 755
            std::cerr << "Warning, trying to add item in an unknown window with id: " << window_id << std::endl;
#endif
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
        std::lock_guard<std::mutex> inventory_lock(inventory_manager_mutex);
#if PROTOCOL_VERSION < 755
        pending_transactions.erase(window_id);
        transaction_states.erase(window_id);
#else
        // In versions > 1.17 we have to synchronize the player inventory
        // when a container is closed, as the server does not send info
        SynchronizeContainerPlayerInventory(window_id);
#endif
        inventories.erase(window_id);
    }

#if PROTOCOL_VERSION < 755
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

    void InventoryManager::AddPendingTransaction(const std::shared_ptr<ServerboundContainerClickPacket> transaction)
    {
        if (!transaction)
        {
            return;
        }
        pending_transactions[transaction->GetContainerId()].insert(std::make_pair(transaction->GetUid(), transaction));
        transaction_states[transaction->GetContainerId()].insert(std::make_pair(transaction->GetUid(), TransactionState::Waiting));

        // Clean oldest transaction to avoid infinite growing map
        for (auto it = transaction_states[transaction->GetContainerId()].begin(); it != transaction_states[transaction->GetContainerId()].end(); )
        {
            if (std::abs(it->first - transaction->GetUid()) > 25)
            {
                it = transaction_states[transaction->GetContainerId()].erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
#else
    void InventoryManager::SynchronizeContainerPlayerInventory(const short window_id)
    {
        if (window_id == Window::PLAYER_INVENTORY_INDEX)
        {
            return;
        }

        auto it = inventories.find(window_id);

        if (it == inventories.end())
        {
            std::cerr << "Warning, trying to synchronize inventory with a non existing container" << std::endl;
            return;
        }

        short player_inventory_first_slot = it->second->GetFirstPlayerInventorySlot();
        std::shared_ptr<Window> player_inventory = GetPlayerInventory();
        
        for (int i = 0; i < 36; ++i)
        {
            player_inventory->SetSlot(Window::INVENTORY_STORAGE_START + i, it->second->GetSlot(player_inventory_first_slot + i));
        }
    }
#endif

#if PROTOCOL_VERSION > 755
    void InventoryManager::SetStateId(const short window_id, const int state_id)
    {
        auto it = inventories.find(window_id);

        if (it != inventories.end())
        {
            it->second->SetStateId(state_id);
        }
    }
#endif

    void InventoryManager::AddInventory(const short window_id, const InventoryType window_type)
    {
        inventories[window_id] = std::shared_ptr<Window>(new Window(window_type));
#if PROTOCOL_VERSION < 755
        pending_transactions[window_id] = std::map<short, std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> >();
        transaction_states[window_id] = std::map<short, TransactionState>();
#endif
    }

    void InventoryManager::SetHotbarSelected(const short index)
    {
        index_hotbar_selected = index;
    }

    const Slot& InventoryManager::GetCursor() const
    {
        return cursor;
    }

    void InventoryManager::SetCursor(const Slot& c)
    {
        cursor = c;
    }

    const std::map<short, Slot> InventoryManager::ApplyTransaction(const std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket> transaction)
    {
        // Get the container
        std::shared_ptr<Window> window = GetWindow(transaction->GetContainerId());

        std::map<short, Slot> modified_slots;

        // Process the transaction
        switch (transaction->GetClickType())
        {
        case 0:
            // "Left click"
            if (transaction->GetButtonNum() == 0)
            {
                const Slot switched_slot = window->GetSlot(transaction->GetSlotNum());
                window->SetSlot(transaction->GetSlotNum(), cursor);
                modified_slots[transaction->GetSlotNum()] = cursor;
                cursor = switched_slot;
            }
            break;
        default:
            std::cerr << "Transaction type '" << transaction->GetClickType()
                << "' not implemented." << std::endl;
            break;
        }

        return modified_slots;
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
#if PROTOCOL_VERSION > 755
            SetStateId(msg.GetContainerId(), msg.GetStateId());
#endif
        }
        else
        {
            std::cerr << "Warning, unknown window called during ClientboundContainerSetSlotPacket Handle: " << msg.GetContainerId() << ", " << msg.GetSlot() << std::endl;
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
#if PROTOCOL_VERSION > 755
        if (msg.GetContainerId() >= 0)
        {
            SetStateId(msg.GetContainerId(), msg.GetStateId());
        }
#endif
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundOpenScreenPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
#if PROTOCOL_VERSION < 452
        InventoryType type = InventoryType::Default;
        if (msg.GetType() == "minecraft:chest")
        {
            switch (msg.GetNumberOfSlots())
            {
            case 62:
                type = InventoryType::Generic9x3;
                break;
            case 89:
                type = InventoryType::Generic9x6;
                break;
            default:
                std::cerr << "Warning, not implemented chest type: " << msg.GetType() << std::endl;
                break;
            }
        }
        else
        {
            std::cerr << "Warning, not implemented container type: " << msg.GetType() << std::endl;
        }
        AddInventory(msg.GetContainerId(), type);
#else
        AddInventory(msg.GetContainerId(), (InventoryType)msg.GetType());
#endif
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundSetCarriedItemPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        SetHotbarSelected(msg.GetSlot());
    }

#if PROTOCOL_VERSION < 755
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
            ApplyTransaction(transaction->second);
        }

        // Remove the transaction from the waiting state
        container_transactions->second.erase(transaction);
    }
#endif

} //Botcraft