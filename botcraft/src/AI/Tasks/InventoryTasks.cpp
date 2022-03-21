#include "botcraft/AI/Tasks/InventoryTasks.hpp"
#include "botcraft/AI/Tasks/BaseTasks.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    Status ClickSlotInContainer(BehaviourClient& client, const short container_id, const short slot_id, const int click_type, const char button_num)
    {
        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

        std::shared_ptr<ServerboundContainerClickPacket> click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

        click_window_msg->SetContainerId(container_id);
        click_window_msg->SetSlotNum(slot_id);
        click_window_msg->SetButtonNum(button_num);
        click_window_msg->SetClickType(click_type);

        // ItemStack/CarriedItem, StateId and ChangedSlots will be set in SendInventoryTransaction
        int transaction_id = client.SendInventoryTransaction(click_window_msg);

        // Wait for the click confirmation (versions < 1.17)
#if PROTOCOL_VERSION < 755
        auto start = std::chrono::steady_clock::now();
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 10000)
            {
                LOG_WARNING("Something went wrong trying to click slot (Timeout).");
                return Status::Failure;
            }
            TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
            if (transaction_state == TransactionState::Accepted)
            {
                break;
            }
            // The transaction has been refused by the server
            else if (transaction_state == TransactionState::Refused)
            {
                return Status::Failure;
            }

            client.Yield();
        }
#endif
        return Status::Success;
    }

    Status ClickSlotInContainerBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "ClickSlotInContainer.container_id",
               "ClickSlotInContainer.slot_id",
               "ClickSlotInContainer.click_type",
               "ClickSlotInContainer.button_num" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const short container_id = blackboard.Get<short>(variable_names[0]);
        const short slot_id = blackboard.Get<short>(variable_names[1]);
        const int click_type = blackboard.Get<int>(variable_names[2]);
        const char button_num = blackboard.Get<char>(variable_names[3]);

        return ClickSlotInContainer(client, container_id, slot_id, click_type, button_num);
    }

    Status SwapItemsInContainer(BehaviourClient& client, const short container_id, const short first_slot, const short second_slot)
    {
        // Left click on the first slot, transferring the slot to the cursor
        if (ClickSlotInContainer(client, container_id, first_slot, 0, 0) == Status::Failure)
        {
            LOG_WARNING("Failed to swap items (first click)");
            return Status::Failure;
        }

        // Left click on the second slot, transferring the cursor to the slot
        if (ClickSlotInContainer(client, container_id, second_slot, 0, 0) == Status::Failure)
        {
            LOG_WARNING("Failed to swap items (second click)");
            return Status::Failure;
        }

        // Left click on the first slot, transferring back the cursor to the slot
        if (ClickSlotInContainer(client, container_id, first_slot, 0, 0) == Status::Failure)
        {
            LOG_WARNING("Failed to swap items (third click)");
            return Status::Failure;
        }

        return Status::Success;
    }

    Status SwapItemsInContainerBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "SwapItemsInContainer.container_id",
               "SwapItemsInContainer.first_slot",
               "SwapItemsInContainer.second_slot" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const short container_id = blackboard.Get<short>(variable_names[0]);
        const short first_slot = blackboard.Get<short>(variable_names[1]);
        const short second_slot = blackboard.Get<short>(variable_names[2]);

        return SwapItemsInContainer(client, container_id, first_slot, second_slot);
    }

    Status DropItemsFromContainer(BehaviourClient& client, const short container_id, const short slot_id, const short num_to_keep)
    {
        if (ClickSlotInContainer(client, container_id, slot_id, 0, 0) == Status::Failure)
        {
            return Status::Failure;
        }

        // Drop all
        if (num_to_keep == 0)
        {
            return ClickSlotInContainer(client, container_id, -999, 0, 0);
        }

        int item_count = 0;
        {
            std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            item_count = inventory_manager->GetCursor().GetItemCount();
        }

        // Drop the right amount of items
        while (item_count > num_to_keep)
        {
            if (ClickSlotInContainer(client, container_id, -999, 0, 1) == Status::Failure)
            {
                return Status::Failure;
            }
            item_count -= 1;
        }

        // Put back remaining items in the initial slot
        return ClickSlotInContainer(client, container_id, slot_id, 0, 0);
    }

    Status DropItemsFromContainerBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "DropItemsFromContainer.container_id",
               "DropItemsFromContainer.slot_id",
               "DropItemsFromContainer.num_to_keep" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const short container_id = blackboard.Get<short>(variable_names[0]);
        const short slot_id = blackboard.Get<short>(variable_names[1]);

        // Optional
        const short num_to_keep = blackboard.Get<short>(variable_names[2], 0);

        return DropItemsFromContainer(client, container_id, slot_id, num_to_keep);
    }

    Status PutOneItemInContainerSlot(BehaviourClient& client, const short container_id, const short source_slot, const short destination_slot)
    {

        // Left click on the first slot, transferring the slot to the cursor
        if (ClickSlotInContainer(client, container_id, source_slot, 0, 0) == Status::Failure)
        {
            LOG_WARNING("Failed to put one item in slot (first click)");
            return Status::Failure;
        }

        // Right click on the second slot, transferring one item of the cursor to the slot
        if (ClickSlotInContainer(client, container_id, destination_slot, 0, 1) == Status::Failure)
        {
            LOG_WARNING("Failed to put one item in slot (second click)");
            return Status::Failure;
        }

        // Left click on the first slot, transferring back the cursor to the slot
        if (ClickSlotInContainer(client, container_id, source_slot, 0, 0) == Status::Failure)
        {
            LOG_WARNING("Failed to put one item in slot (third click)");
            return Status::Failure;
        }

        return Status::Success;
    }

    Status PutOneItemInContainerSlotBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "PutOneItemInContainerSlot.container_id",
               "PutOneItemInContainerSlot.source_slot",
               "PutOneItemInContainerSlot.destination_slot" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const short container_id = blackboard.Get<short>(variable_names[0]);
        const short source_slot = blackboard.Get<short>(variable_names[1]);
        const short destination_slot = blackboard.Get<short>(variable_names[2]);

        return PutOneItemInContainerSlot(client, container_id, source_slot, destination_slot);
    }

    Status SetItemInHand(BehaviourClient& client, const std::string& item_name, const Hand hand)
    {
        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

        short inventory_correct_slot_index = -1;
        short inventory_destination_slot_index = -1;
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());

            inventory_destination_slot_index = hand == Hand::Left ? Window::INVENTORY_OFFHAND_INDEX : (Window::INVENTORY_HOTBAR_START + inventory_manager->GetIndexHotbarSelected());

            // We need to check the inventory
            // If the currently selected item is the right one, just go for it
            const Slot& current_selected = hand == Hand::Left ? inventory_manager->GetOffHand() : inventory_manager->GetHotbarSelected();
            if (!current_selected.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                && AssetsManager::getInstance().Items().at(current_selected.GetBlockID()).at(current_selected.GetItemDamage())->GetName() == item_name)
#else
                && AssetsManager::getInstance().Items().at(current_selected.GetItemID())->GetName() == item_name)
#endif
            {
                return Status::Success;
            }

            // Otherwise we need to find a slot with the given item
            const std::map<short, Slot>& slots = inventory_manager->GetPlayerInventory()->GetSlots();
            for (auto it = slots.begin(); it != slots.end(); ++it)
            {
                if (it->first >= Window::INVENTORY_STORAGE_START
                    && it->first < Window::INVENTORY_OFFHAND_INDEX
                    && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                    && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName() == item_name)
#else
                    && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() == item_name)
#endif
                {
                    inventory_correct_slot_index = it->first;
                    break;
                }
            }

            // If there is no stack with the given item in the inventory
            if (inventory_correct_slot_index == -1)
            {
                return Status::Failure;
            }
        }

        return SwapItemsInContainer(client, Window::PLAYER_INVENTORY_INDEX, inventory_correct_slot_index, inventory_destination_slot_index);
    }

    Status SetItemInHandBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
            "SetItemInHand.item_name", "SetItemInHand.hand" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& item_name = blackboard.Get<std::string>(variable_names[0]);
        const Hand hand = blackboard.Get<Hand>(variable_names[1], Hand::Right);

        return SetItemInHand(client, item_name, hand);
    }

    Status PlaceBlock(BehaviourClient& client, const std::string& item_name, const Position& pos, const PlayerDiggingFace face, const bool wait_confirmation)
    {
        std::shared_ptr<World> world = client.GetWorld();
        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
        std::shared_ptr<EntityManager> entity_manager = client.GetEntityManager();
        std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();

        if (GoTo(client, pos, 4, 1) == Status::Failure)
        {
            return Status::Failure;
        }

        // Check if block is air
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());

            const Block* block = world->GetBlock(pos);

            if (block && !block->GetBlockstate()->IsAir())
            {
                return Status::Failure;
            }
        }

        // Check if any entity is in the middle
        {
            const AABB this_box_collider = AABB(Vector3<double>(pos.x + 0.5, pos.y + 0.5, pos.z + 0.5), Vector3<double>(0.5, 0.5, 0.5));

            std::lock_guard<std::mutex> entity_manager_guard(entity_manager->GetMutex());
            const std::unordered_map<int, std::shared_ptr<Entity> >& entities = entity_manager->GetEntities();
            // TODO, check entity type, xp orbs and items don't collide
            for (auto it = entities.begin(); it != entities.end(); ++it)
            {
                if (this_box_collider.Collide(it->second->GetCollider()))
                {
                    return Status::Failure;
                }
            }
        }

        // Check if item in inventory
        if (SetItemInHand(client, item_name, Hand::Right) == Status::Failure)
        {
            return Status::Failure;
        }

        int num_item_in_hand;
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            num_item_in_hand = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HOTBAR_START + inventory_manager->GetIndexHotbarSelected()).GetItemCount();
        }

        std::shared_ptr<ServerboundUseItemOnPacket> place_block_msg(new ServerboundUseItemOnPacket);
        place_block_msg->SetLocation(pos.ToNetworkPosition());
        place_block_msg->SetDirection(static_cast<int>(face));
        switch (face)
        {
        case PlayerDiggingFace::Down:
            place_block_msg->SetCursorPositionX(0.5f);
            place_block_msg->SetCursorPositionY(0.0f);
            place_block_msg->SetCursorPositionZ(0.5f);
            break;
        case PlayerDiggingFace::Up:
            place_block_msg->SetCursorPositionX(0.5f);
            place_block_msg->SetCursorPositionY(1.0f);
            place_block_msg->SetCursorPositionZ(0.5f);
            break;
        case PlayerDiggingFace::North:
            place_block_msg->SetCursorPositionX(0.5f);
            place_block_msg->SetCursorPositionY(0.5f);
            place_block_msg->SetCursorPositionZ(0.0f);
            break;
        case PlayerDiggingFace::South:
            place_block_msg->SetCursorPositionX(0.5f);
            place_block_msg->SetCursorPositionY(0.5f);
            place_block_msg->SetCursorPositionZ(1.0f);
            break;
        case PlayerDiggingFace::East:
            place_block_msg->SetCursorPositionX(1.0f);
            place_block_msg->SetCursorPositionY(0.5f);
            place_block_msg->SetCursorPositionZ(0.5f);
            break;
        case PlayerDiggingFace::West:
            place_block_msg->SetCursorPositionX(0.0f);
            place_block_msg->SetCursorPositionY(0.5f);
            place_block_msg->SetCursorPositionZ(0.5f);
            break;
        default:
            break;
        }
#if PROTOCOL_VERSION > 452
        place_block_msg->SetInside(false);
#endif
        place_block_msg->SetHand((int)Hand::Right);


        // Place the block
        network_manager->Send(place_block_msg);

        if (!wait_confirmation)
        {
            return Status::Success;
        }

        bool is_block_ok = false;
        bool is_slot_ok = false;
        auto start = std::chrono::steady_clock::now();
        while (!is_block_ok || !is_slot_ok)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 3000)
            {
                LOG_WARNING('[' << network_manager->GetMyName() << "] Something went wrong waiting block placement confirmation at " << pos << " (Timeout).");
                return Status::Failure;
            }
            if (!is_block_ok)
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                const Block* block = world->GetBlock(pos);

                if (block && block->GetBlockstate()->GetName() == item_name)
                {
                    is_block_ok = true;
                }
            }
            if (!is_slot_ok)
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                int new_num_item_in_hand = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HOTBAR_START + inventory_manager->GetIndexHotbarSelected()).GetItemCount();
                is_slot_ok = new_num_item_in_hand == num_item_in_hand - 1;
            }

            if (is_block_ok && is_slot_ok)
            {
                return Status::Success;
            }

            client.Yield();
        }

        return Status::Success;
    }

    Status PlaceBlockBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "PlaceBlock.item_name", "PlaceBlock.pos", "PlaceBlock.face", "PlaceBlock.wait_confirmation" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& item_name = blackboard.Get<std::string>(variable_names[0]);
        const Position& pos = blackboard.Get<Position>(variable_names[1]);

        // Optional
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[2], PlayerDiggingFace::Up);
        const bool wait_confirmation = blackboard.Get<bool>(variable_names[3], false);


        return PlaceBlock(client, item_name, pos, face, wait_confirmation);
    }

    Status Eat(BehaviourClient& client, const std::string& food_name, const bool wait_confirmation)
    {
        if (SetItemInHand(client, food_name, Hand::Left) == Status::Failure)
        {
            return Status::Failure;
        }

        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
        std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();

        const char current_stack_size = inventory_manager->GetOffHand().GetItemCount();
        std::shared_ptr<ServerboundUseItemPacket> use_item_msg(new ServerboundUseItemPacket);
        use_item_msg->SetHand((int)Hand::Left);
        network_manager->Send(use_item_msg);

        if (!wait_confirmation)
        {
            return Status::Success;
        }

        auto start = std::chrono::steady_clock::now();
        while (inventory_manager->GetOffHand().GetItemCount() == current_stack_size)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 3000)
            {
                LOG_WARNING("Something went wrong trying to eat (Timeout).");
                return Status::Failure;
            }
            client.Yield();
        }

        return Status::Success;
    }

    Status EatBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "Eat.food_name", "Eat.wait_confirmation" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& food_name = blackboard.Get<std::string>(variable_names[0]);

        // Optional
        const bool wait_confirmation = blackboard.Get<bool>(variable_names[1], false);


        return Eat(client, food_name, wait_confirmation);
    }

    Status OpenContainer(BehaviourClient& client, const Position& pos)
    {
        // Open the container
        if (InteractWithBlock(client, pos, PlayerDiggingFace::Up) == Status::Failure)
        {
            return Status::Failure;
        }

        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

        // Wait for a window to be opened
        auto start = std::chrono::steady_clock::now();
        while (inventory_manager->GetFirstOpenedWindowId() == -1)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 3000)
            {
                LOG_WARNING("Something went wrong trying to open container (Timeout).");
                return Status::Failure;
            }
            client.Yield();
        }

        return Status::Success;
    }

    Status OpenContainerBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "OpenContainer.pos" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const Position& pos = blackboard.Get<Position>(variable_names[0]);


        return OpenContainer(client, pos);
    }

    Status CloseContainer(BehaviourClient& client, const short container_id)
    {
        std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();
        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

        std::shared_ptr<ServerboundContainerClosePacket> close_container_msg = std::make_shared<ServerboundContainerClosePacket>();
        close_container_msg->SetContainerId(container_id);
        network_manager->Send(close_container_msg);

        // There is no confirmation from the server, so we
        // can simply close the window here
        inventory_manager->EraseInventory(container_id);

        return Status::Success;
    }

    Status CloseContainerBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "CloseContainer.container_id" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const short container_id = blackboard.Get<short>(variable_names[0]);


        return CloseContainer(client, container_id);
    }

    Status LogInventoryContent(BehaviourClient& client, const LogLevel level)
    {
        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

        std::stringstream output;
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            for (const auto& s: inventory_manager->GetPlayerInventory()->GetSlots())
            {
                output << s.first << " --> " << s.second.Serialize().dump() << "\n";
            }
        }
        LOG(output.str(), level);
        return Status::Success;
    }

    Status LogInventoryContentBlackboard(BehaviourClient& client)
    {        
        const std::vector<std::string> variable_names = {
               "LogInventoryContent.level" };

        Blackboard& blackboard = client.GetBlackboard();

        //Optional
        const LogLevel level = blackboard.Get<LogLevel>(variable_names[0], LogLevel::Info);

        return LogInventoryContent(client, level);
    }

#if PROTOCOL_VERSION > 451
    Status Trade(BehaviourClient& client, const int item_id, const bool buy, const int trade_id)
    {
        std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

        // Make sure a trading window is opened and
        // possible trades are available
        auto start = std::chrono::steady_clock::now();
        size_t num_trades = 0;
        do
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() > 5000)
            {
                LOG_WARNING("Something went wrong waiting trade opening (Timeout).");
                return Status::Failure;
            }

            {
                std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
                num_trades = inventory_manager->GetAvailableTrades().size();
            }
            client.Yield();
        } while (num_trades <= 0 || inventory_manager->GetFirstOpenedWindowId() == -1);

        int trade_index = trade_id;
        bool has_trade_second_item = false;
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            const std::vector<ProtocolCraft::Trade>& trades = inventory_manager->GetAvailableTrades();

            // Find which trade we want in the list
            if (trade_id == -1)
            {
                for (int i = 0; i < trades.size(); ++i)
                {
                    if ((buy && trades[i].GetOutputItem().GetItemID() == item_id)
                        || (!buy && trades[i].GetInputItem1().GetItemID() == item_id))
                    {
                        trade_index = i;
                        has_trade_second_item = trades[i].GetHasSecondItem();
                        break;
                    }
                }
            }

            // Check that the trade is not locked
            if (trades[trade_index].GetNumberOfTradesUses() >= trades[trade_index].GetMaximumNumberOfTradeUses())
            {
                LOG_WARNING("Failed trading (trade locked)")
                return Status::Failure;
            }
        }

        std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();

        // Select the trade in the list
        std::shared_ptr<ServerboundSelectTradePacket> select_trade_msg = std::make_shared<ServerboundSelectTradePacket>();
        select_trade_msg->SetItem(trade_index);

        network_manager->Send(select_trade_msg);

        start = std::chrono::steady_clock::now();
        // Wait until the output/input is set with the correct item
        bool correct_items = false;
        do
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() > 5000)
            {
                LOG_WARNING("Something went wrong waiting trade selection (Timeout). Maybe an item was missing?");
                return Status::Failure;
            }

            {
                std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
                std::shared_ptr<Window> trading_container = inventory_manager->GetWindow(inventory_manager->GetFirstOpenedWindowId());
                if (!trading_container)
                {
                    LOG_WARNING("Trading container closed during trade");
                    return Status::Failure;
                }
                correct_items = (buy && trading_container->GetSlot(2).GetItemID() == item_id) ||
                    (!buy && (trading_container->GetSlot(0).GetItemID() == item_id || trading_container->GetSlot(1).GetItemID() == item_id));
            }
            client.Yield();
        } while (!correct_items);

        // Check we have at least one empty slot to get back input remainings + outputs
        std::vector<short> empty_slots(has_trade_second_item ? 3 : 2);
        int empty_slots_index = 0;
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            std::shared_ptr<Window> trading_container = inventory_manager->GetWindow(inventory_manager->GetFirstOpenedWindowId());
            if (!trading_container)
            {
                LOG_WARNING("Trading container closed during trade");
                return Status::Failure;
            }
            for (const auto& s: trading_container->GetSlots())
            {
                if (s.first < trading_container->GetFirstPlayerInventorySlot())
                {
                    continue;
                }

                if (s.second.IsEmptySlot())
                {
                    empty_slots[empty_slots_index] = s.first;
                    empty_slots_index++;
                    if (empty_slots_index == empty_slots.size())
                    {
                        break;
                    }
                }
            }
        }
        if (empty_slots_index == 0)
        {
            LOG_WARNING("No free space in inventory for trading to happen.");
            return Status::Failure;
        }
        else if (empty_slots_index < empty_slots.size())
        {
            LOG_WARNING("Not enough free space in inventory for trading. Input items may be lost");
        }

        // Get the output in the inventory
        if (SwapItemsInContainer(client, inventory_manager->GetFirstOpenedWindowId(), empty_slots[0], 2) == Status::Failure)
        {
            LOG_WARNING("Failed to swap output slot during trading attempt");
            return Status::Failure;
        }

        // Get back the input remainings in the inventory
        for (int i = 0; i < empty_slots_index - 1; ++i)
        {
            if (SwapItemsInContainer(client, inventory_manager->GetFirstOpenedWindowId(), empty_slots[i + 1], i) == Status::Failure)
            {
                LOG_WARNING("Failed to swap slots " << i << " after trading attempt");
                return Status::Failure;
            }
        }

        // If we are here, everything is fine (or should be),
        // remove 1 to the possible trade counter on the villager
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            ProtocolCraft::Trade& trade = inventory_manager->GetAvailableTrade(trade_index);
            trade.SetNumberOfTradesUses(trade.GetNumberOfTradesUses() + 1);
        }

        return Status::Success;
    }

    Status TradeBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "Trade.item_id", "Trade.buy", "Trade.trade_id"};

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const int item_id = blackboard.Get<int>(variable_names[0]);
        const bool buy = blackboard.Get<bool>(variable_names[1]);

        //Optional
        const int trade_id = blackboard.Get<int>(variable_names[2], -1);

        return Trade(client, item_id, buy, trade_id);
    }

    Status TradeName(BehaviourClient& client, const std::string& item_name, const bool buy, const int trade_id)
    {
        // Get item id corresponding to the name
        const int item_id = AssetsManager::getInstance().GetItemID(item_name);
        if (item_id < 0)
        {
            LOG_WARNING("Trying to trade an unknown item");
            return Status::Failure;
        }

        return Trade(client, item_id, buy, trade_id);
    }

    Status TradeNameBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
               "TradeName.item_name", "TradeName.buy", "TradeName.trade_id" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& item_name = blackboard.Get<std::string>(variable_names[0]);
        const bool buy = blackboard.Get<bool>(variable_names[1]);

        // Optional
        const int trade_id = blackboard.Get<int>(variable_names[2], -1);

        return TradeName(client, item_name, buy, trade_id);
    }
#endif
}
