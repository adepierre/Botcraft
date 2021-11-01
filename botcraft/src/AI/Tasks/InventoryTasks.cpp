#include <iostream>

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

using namespace ProtocolCraft;

namespace Botcraft
{
    namespace AI
    {
        Status SwapItemsInContainer(BehaviourClient& client, const short container_id, const short first_slot, const short second_slot)
        {
            std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();
            std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);

            if (!container)
            {
                return Status::Failure;
            }

            Slot copied_slot;
            std::shared_ptr<ServerboundContainerClickPacket> click_window_msg;
            int transaction_id;

            // Left click on the first slot, transferring the slot
            // to the cursor
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                copied_slot = container->GetSlots().at(first_slot);
            }

            click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(first_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
            click_window_msg->SetItemStack(copied_slot);
#else
            click_window_msg->SetCarriedItem(copied_slot);
#endif
#if PROTOCOL_VERSION > 755
            click_window_msg->SetStateId(container->GetStateId());
#endif

            transaction_id = client.SendInventoryTransaction(click_window_msg);

            // Wait for the click confirmation (versions < 1.17)
#if PROTOCOL_VERSION < 755
            auto start = std::chrono::system_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
                {
                    std::cerr << "Something went wrong trying to select first slot during swap inventory (Timeout)." << std::endl;
                    return Status::Failure;
                }
                TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
                if (transaction_state == TransactionState::Accepted)
                {
                    break;
                }
                // The transaction has been refused by the server, don't bother with other clicks
                else if (transaction_state == TransactionState::Refused)
                {
                    return Status::Failure;
                }

                client.Yield();
            }
#endif



            // left click on the second slot, transferring the cursor to the slot
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                copied_slot = container->GetSlots().at(second_slot);
            }
            click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(second_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
            click_window_msg->SetItemStack(copied_slot);
#else
            click_window_msg->SetCarriedItem(copied_slot);
#endif
#if PROTOCOL_VERSION > 755
            click_window_msg->SetStateId(container->GetStateId());
#endif

            transaction_id = client.SendInventoryTransaction(click_window_msg);

            // Wait for confirmation in version < 1.17
#if PROTOCOL_VERSION < 755
            start = std::chrono::system_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
                {
                    std::cerr << "Something went wrong trying to select second slot during swap inventory (Timeout)." << std::endl;
                    return Status::Failure;
                }

                TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
                if (transaction_state == TransactionState::Accepted)
                {
                    break;
                }
                // The transaction has been refused by the server, don't bother with other clicks
                else if (transaction_state == TransactionState::Refused)
                {
                    return Status::Failure;
                }

                client.Yield();
            }
#endif
            // Left click once again on the first slot, transferring the cursor to the slot
            {
                std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
                copied_slot = container->GetSlots().at(first_slot);
            }
            click_window_msg = std::make_shared<ServerboundContainerClickPacket>();

            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(first_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
            click_window_msg->SetItemStack(copied_slot);
#else
            click_window_msg->SetCarriedItem(copied_slot);
#endif
#if PROTOCOL_VERSION > 755
            click_window_msg->SetStateId(container->GetStateId());
#endif

            transaction_id = client.SendInventoryTransaction(click_window_msg);

            // Wait for confirmation in version < 1.17
#if PROTOCOL_VERSION < 755
            start = std::chrono::system_clock::now();
            while (true)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
                {
                    std::cerr << "Something went wrong trying to select third slot during swap inventory (Timeout)." << std::endl;
                    return Status::Failure;
                }

                TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
                if (transaction_state == TransactionState::Accepted)
                {
                    break;
                }
                // The transaction has been refused by the server, don't bother with other clicks
                else if (transaction_state == TransactionState::Refused)
                {
                    return Status::Failure;
                }

                client.Yield();
            }
#endif
            // If we're here, everything succeeded
            return Status::Success;
        }

        Status SwapItemsInContainerBlackboard(BehaviourClient& client)
        {
            const std::vector<std::string> variable_names = {
                   "SwapItemsInContainer.container_id",
                   "SwapItemsInContainer.first_slot",
                   "SwapItemsInContainer.second_slot"};

            Blackboard& blackboard = client.GetBlackboard();

            // Mandatory
            const short container_id = blackboard.Get<short>(variable_names[0]);
            const short first_slot = blackboard.Get<short>(variable_names[1]);
            const short second_slot = blackboard.Get<short>(variable_names[2]);

            return SwapItemsInContainer(client, container_id, first_slot, second_slot);
        }

        Status SetItemInHand(BehaviourClient& client, const std::string& item_name, const Hand hand)
        {
            std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

            short inventory_correct_slot_index = -1;
            short inventory_destination_slot_index = -1;
            {
                std::lock_guard<std::mutex>(inventory_manager->GetMutex());

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
            case PlayerDiggingFace::Bottom:
                place_block_msg->SetCursorPositionX(0.5f);
                place_block_msg->SetCursorPositionY(0.0f);
                place_block_msg->SetCursorPositionZ(0.5f);
                break;
            case PlayerDiggingFace::Top:
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
            auto start = std::chrono::system_clock::now();
            while (!is_block_ok || !is_slot_ok)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 3000)
                {
                    std::cerr << "[" << network_manager->GetMyName() << "] Something went wrong waiting block placement confirmation at " << pos << " (Timeout)." << std::endl;
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
            const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[2], PlayerDiggingFace::Top);
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

            auto start = std::chrono::system_clock::now();
            while (inventory_manager->GetOffHand().GetItemCount() == current_stack_size)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 3000)
                {
                    std::cerr << "Something went wrong trying to eat (Timeout)." << std::endl;
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
            if (InteractWithBlock(client, pos, PlayerDiggingFace::Top) == Status::Failure)
            {
                return Status::Failure;
            }

            std::shared_ptr<InventoryManager> inventory_manager = client.GetInventoryManager();

            // Wait for a window to be opened
            auto start = std::chrono::system_clock::now();
            while (inventory_manager->GetFirstOpenedWindowId() == -1)
            {
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 3000)
                {
                    std::cerr << "Something went wrong trying to open container (Timeout)." << std::endl;
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

    }
}