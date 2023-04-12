#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    InventoryManager::InventoryManager()
    {
        index_hotbar_selected = 0;
        cursor = Slot();
        inventories[Window::PLAYER_INVENTORY_INDEX] = std::make_shared<Window>(InventoryType::PlayerInventory);
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
            LOG_WARNING("Trying to add item in an unknown window with id : " << window_id);
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

#if PROTOCOL_VERSION > 451
        if (window_id == trading_container_id)
        {
            trading_container_id = -1;
            available_trades.clear();
        }
#endif
    }

#if PROTOCOL_VERSION < 755
    const TransactionState InventoryManager::GetTransactionState(const short window_id, const int transaction_id)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        auto it = transaction_states.find(window_id);

        if (it == transaction_states.end())
        {
            LOG_ERROR("Asking state of a transaction for a closed window");
            return TransactionState::Refused;
        }

        auto it2 = it->second.find(transaction_id);

        if (it2 == it->second.end())
        {
            LOG_ERROR("Asking state of an unknown transaction");
            return TransactionState::Refused;
        }

        return it2->second;
    }

    void InventoryManager::AddPendingTransaction(const InventoryTransaction& transaction)
    {
        pending_transactions[transaction.msg->GetContainerId()].insert(std::make_pair(transaction.msg->GetUid(), transaction));
        transaction_states[transaction.msg->GetContainerId()].insert(std::make_pair(transaction.msg->GetUid(), TransactionState::Waiting));

        // Clean oldest transaction to avoid infinite growing map
        for (auto it = transaction_states[transaction.msg->GetContainerId()].begin(); it != transaction_states[transaction.msg->GetContainerId()].end(); )
        {
            if (std::abs(it->first - transaction.msg->GetUid()) > 25)
            {
                it = transaction_states[transaction.msg->GetContainerId()].erase(it);
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
            LOG_WARNING("Trying to synchronize inventory with a non existing container");
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
        pending_transactions[window_id] = std::map<short, InventoryTransaction >();
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

    InventoryTransaction InventoryManager::PrepareTransaction(const std::shared_ptr<ProtocolCraft::ServerboundContainerClickPacket>& transaction)
    {
        // We need to lock because we access the container and the cursor
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);

        // Get the container
        std::shared_ptr<Window> window = GetWindow(transaction->GetContainerId());

        InventoryTransaction output{ transaction };
        std::map<short, Slot> changed_slots;
        Slot carried_item;

        // Process the transaction
        
        // Click on the output of a crafting container
        if ((window->GetType() == InventoryType::PlayerInventory || window->GetType() == InventoryType::Crafting) &&
            transaction->GetSlotNum() == 0)
        {
            if (transaction->GetClickType() != 0 && transaction->GetClickType() != 1)
            {
                LOG_ERROR("Transaction type '" << transaction->GetClickType() << "' not implemented.");
                throw std::runtime_error("Non supported transaction type created");
            }

            if (transaction->GetButtonNum() != 0 && transaction->GetButtonNum() != 1)
            {
                LOG_ERROR("Transaction button num '" << transaction->GetButtonNum() << "' not supported.");
                throw std::runtime_error("Non supported transaction button created");
            }

            const Slot& clicked_slot = window->GetSlot(transaction->GetSlotNum());
            // If cursor is not empty, we can't click if the items are not the same, 
            if (!cursor.IsEmptySlot() &&
#if PROTOCOL_VERSION < 347
                (cursor.GetBlockID() != clicked_slot.GetBlockID()
                    || cursor.GetItemDamage() != clicked_slot.GetItemDamage())
#else
                cursor.GetItemID() != clicked_slot.GetItemID()
#endif
                )
            {
                carried_item = cursor;
            }
            // We can't click if the crafted items don't fit in the stack
            else if (!cursor.IsEmptySlot() &&
                cursor.GetItemCount() + clicked_slot.GetItemCount() >
#if PROTOCOL_VERSION < 347
                AssetsManager::getInstance().Items().at(cursor.GetBlockID()).at(static_cast<unsigned char>(cursor.GetItemDamage()))->GetStackSize()
#else
                AssetsManager::getInstance().Items().at(cursor.GetItemID())->GetStackSize()
#endif
                )
            {
                carried_item = cursor;
            }
            else
            {
                carried_item = clicked_slot;
                carried_item.SetItemCount(cursor.GetItemCount() + clicked_slot.GetItemCount());
                changed_slots[0] = Window::EMPTY_SLOT;
                for (int i = 1; i < (window->GetType() == InventoryType::Crafting ? 10 : 5); ++i)
                {
                    Slot cloned_slot = window->GetSlot(i);
                    cloned_slot.SetItemCount(cloned_slot.GetItemCount() - 1);
                    changed_slots[i] = cloned_slot;
                }
            }
        }
        // Drop item
        else if (transaction->GetSlotNum() == -999)
        {
            switch (transaction->GetClickType())
            {
                case 0:
                {
                    switch (transaction->GetButtonNum())
                    {
                        case 0:
                        {
                            carried_item = Window::EMPTY_SLOT;
                            break;
                        }
                        case 1:
                        {
                            carried_item = cursor;
                            carried_item.SetItemCount(cursor.GetItemCount() - 1);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    LOG_ERROR("Transaction type '" << transaction->GetClickType() << "' not implemented.");
                    throw std::runtime_error("Non supported transaction type created");
                    break;
                }
            }
        }
        // Normal case
        else
        {
            switch (transaction->GetClickType())
            {
                case 0:
                {
                    const Slot& clicked_slot = window->GetSlot(transaction->GetSlotNum());
                    switch (transaction->GetButtonNum())
                    {

                        case 0: // "Left click"
                        {
                            // Special case: left click with same item
                            if (!cursor.IsEmptySlot() && !clicked_slot.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                                && cursor.GetBlockID() == clicked_slot.GetBlockID()
                                && cursor.GetItemDamage() == clicked_slot.GetItemDamage()
#else
                                && cursor.GetItemID() == clicked_slot.GetItemID()
#endif
                                )
                            {
                                const int sum_count = cursor.GetItemCount() + clicked_slot.GetItemCount();
#if PROTOCOL_VERSION < 347
                                const int max_stack_size = AssetsManager::getInstance().Items().at(cursor.GetBlockID()).at(static_cast<unsigned char>(cursor.GetItemDamage()))->GetStackSize();
#else
                                const int max_stack_size = AssetsManager::getInstance().Items().at(cursor.GetItemID())->GetStackSize();
#endif
                                // The cursor becomes the clicked slot
                                carried_item = clicked_slot;
                                carried_item.SetItemCount(std::max(0, sum_count - max_stack_size));
                                // The content of the clicked slot becomes the cursor
                                changed_slots = { {transaction->GetSlotNum(), cursor} };
                                changed_slots.at(transaction->GetSlotNum()).SetItemCount(std::min(max_stack_size, sum_count));
                            }
                            else
                            {
                                // The cursor becomes the clicked slot
                                carried_item = clicked_slot;
                                // The content of the clicked slot becomes the cursor
                                changed_slots = { {transaction->GetSlotNum(), cursor} };
                            }
                            break;
                        }
                        case 1: // "Right Click"
                        {
                            // If cursor is empty, take half the stack
                            if (cursor.IsEmptySlot())
                            {
                                const int new_quantity = clicked_slot.GetItemCount() / 2;
                                carried_item = clicked_slot;
                                carried_item.SetItemCount(clicked_slot.GetItemCount() - new_quantity);
                                changed_slots = { {transaction->GetSlotNum(), clicked_slot} };
                                changed_slots.at(transaction->GetSlotNum()).SetItemCount(new_quantity);
                            }
                            // If clicked is empty, put one item in the slot
                            else if (clicked_slot.IsEmptySlot())
                            {
                                // Cursor is the same, minus one item
                                carried_item = cursor;
                                carried_item.SetItemCount(cursor.GetItemCount() - 1);
                                // Dest slot it the same, plus one item
                                changed_slots = { {transaction->GetSlotNum(), cursor} };
                                changed_slots.at(transaction->GetSlotNum()).SetItemCount(1);
                            }
                            // If same items in both
#if PROTOCOL_VERSION < 347
                            else if (cursor.GetBlockID() == clicked_slot.GetBlockID()
                                && cursor.GetItemDamage() == clicked_slot.GetItemDamage())
#else
                            else if (cursor.GetItemID() == clicked_slot.GetItemID())
#endif
                            {
#if PROTOCOL_VERSION < 347
                                const int max_stack_size = AssetsManager::getInstance().Items().at(cursor.GetBlockID()).at(static_cast<unsigned char>(cursor.GetItemDamage()))->GetStackSize();
#else
                                const int max_stack_size = AssetsManager::getInstance().Items().at(cursor.GetItemID())->GetStackSize();
#endif
                                const bool transfer = clicked_slot.GetItemCount() < max_stack_size;
                                // The cursor loses 1 item if possible
                                carried_item = clicked_slot;
                                carried_item.SetItemCount(transfer ? cursor.GetItemCount() - 1 : cursor.GetItemCount());
                                // The content of the clicked slot gains one item if possible
                                changed_slots = { {transaction->GetSlotNum(), cursor} };
                                changed_slots.at(transaction->GetSlotNum()).SetItemCount(transfer ? clicked_slot.GetItemCount() + 1 : clicked_slot.GetItemCount());
                            }
                            // Else just switch like a left click
                            else
                            {
                                // The cursor becomes the clicked slot
                                carried_item = clicked_slot;
                                // The content of the clicked slot becomes the cursor
                                changed_slots = { {transaction->GetSlotNum(), cursor} };
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                }
                default:
                {
                    LOG_ERROR("Transaction type '" << transaction->GetClickType() << "' not implemented.");
                    throw std::runtime_error("Non supported transaction type created");
                    break;
                }
            }
        }

#if PROTOCOL_VERSION > 754
        transaction->SetCarriedItem(carried_item);
        transaction->SetChangedSlots(changed_slots);
#if PROTOCOL_VERSION > 755
        transaction->SetStateId(window->GetStateId());
#endif
#else
        transaction->SetItemStack(window->GetSlot(transaction->GetSlotNum()));
        output.changed_slots = changed_slots;
        output.carried_item = carried_item;

        const int transaction_id = window->GetNextTransactionId();
        transaction->SetUid(transaction_id);
        window->SetNextTransactionId(transaction_id + 1);
#endif
        return output;
    }

    void InventoryManager::ApplyTransactionInternal(const InventoryTransaction& transaction)
    {
#if PROTOCOL_VERSION > 754
        const std::map<short, Slot>& modified_slots = transaction.msg->GetChangeSlots();
        cursor = transaction.msg->GetCarriedItem();
#else
        const std::map<short, Slot>& modified_slots = transaction.changed_slots;
        cursor = transaction.carried_item;
#endif

        // Get the container
        std::shared_ptr<Window> window = GetWindow(transaction.msg->GetContainerId());
        for (const auto& p : modified_slots)
        {
            window->SetSlot(p.first, p.second);
        }
    }

    void InventoryManager::ApplyTransaction(const InventoryTransaction& transaction)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        ApplyTransactionInternal(transaction);
    }

#if PROTOCOL_VERSION > 451
    const std::vector<ProtocolCraft::Trade>& InventoryManager::GetAvailableTrades() const
    {
        return available_trades;
    }

    ProtocolCraft::Trade& InventoryManager::GetAvailableTrade(const int index)
    {
        return available_trades[index];
    }
#endif

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
        // Slot index is starting in the hotbar, THEN in the main storage in this case :)
        else if (msg.GetContainerId() == -2)
        {
            if (msg.GetSlot() < Window::INVENTORY_OFFHAND_INDEX - Window::INVENTORY_HOTBAR_START)
            {
                SetSlot(Window::PLAYER_INVENTORY_INDEX, Window::INVENTORY_HOTBAR_START + msg.GetSlot(), msg.GetItemStack());
            }
            else
            {
                SetSlot(Window::PLAYER_INVENTORY_INDEX, msg.GetSlot() + Window::INVENTORY_OFFHAND_INDEX - Window::INVENTORY_HOTBAR_START, msg.GetItemStack());
            }
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
            LOG_WARNING("Unknown window called during ClientboundContainerSetSlotPacket Handle : " << msg.GetContainerId() << ", " << msg.GetSlot());
        }
    }

    void InventoryManager::Handle(ProtocolCraft::ClientboundContainerSetContentPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        const size_t count = msg.GetSlotData().size();
        for (size_t i = 0; i < count; ++i)
        {
            SetSlot(msg.GetContainerId(), static_cast<short>(i), msg.GetSlotData()[i]);
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
            case 9*3:
                type = InventoryType::Generic9x3;
                break;
            case 9*6:
                type = InventoryType::Generic9x6;
                break;
            default:
                LOG_ERROR("Not implemented chest type : " << msg.GetType());
                break;
            }
        }
        else if (msg.GetType() == "minecraft:crafting_table")
        {
            type = InventoryType::Crafting;
        }
        else
        {
            LOG_ERROR("Not implemented container type : " << msg.GetType());
        }
        AddInventory(msg.GetContainerId(), type);
#else
        AddInventory(msg.GetContainerId(), static_cast<InventoryType>(msg.GetType()));
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
            LOG_WARNING("The server accepted a transaction for an unknown container");
            return;
        }

        auto transaction = container_transactions->second.find(msg.GetUid());

        // Get the corresponding transaction
        if (transaction == container_transactions->second.end())
        {
            LOG_WARNING("Server accepted an unknown transaction Uid");
            return;
        }

        if (msg.GetAccepted())
        {
            ApplyTransactionInternal(transaction->second);
        }

        // Remove the transaction from the waiting state
        container_transactions->second.erase(transaction);
    }
#endif

#if PROTOCOL_VERSION > 451
    void InventoryManager::Handle(ProtocolCraft::ClientboundMerchantOffersPacket& msg)
    {
        std::lock_guard<std::mutex> inventory_manager_locker(inventory_manager_mutex);
        trading_container_id = msg.GetContainerId();
        available_trades = msg.GetOffers();
    }
#endif

    void InventoryManager::Handle(ProtocolCraft::ClientboundContainerClosePacket& msg)
    {
        EraseInventory(msg.GetContainerId());
    }

} //Botcraft
