#include "botcraft/AI/InterfaceClient.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

#include "protocolCraft/enums.hpp"

#include <queue>
#include <unordered_map>
#include <array>
#include <iostream>

using namespace ProtocolCraft;

namespace Botcraft
{    
    InterfaceClient::InterfaceClient(const bool use_renderer_, const bool afk_only_) : BaseClient(use_renderer_, afk_only_),
        pathfinding_task(*this)
    {
        digging_state = DiggingState::Waiting;
    }

    InterfaceClient::~InterfaceClient()
    {

    }

    const DiggingState InterfaceClient::GetDiggingState() const
    {
        return digging_state;
    }

    void InterfaceClient::DigPointedBlock()
    {
        if (!network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
        {
            return;
        }

        if (digging_state != DiggingState::Waiting)
        {
            return;
        }

        digging_state = DiggingState::Digging;

        std::shared_ptr<Blockstate> blockstate;
        Position block_position;
        Position block_normal;
        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            blockstate = world->Raycast(local_player->GetPosition() + Vector3<double>(0.0, 1.65, 0.0), local_player->GetFrontVector(), 6.5f, block_position, block_normal);
        
            if (!blockstate ||
                blockstate->IsFluid() ||
                blockstate->GetHardness() == -1.0f)
            {
                digging_state = DiggingState::Waiting;
                
                return;
            }

            const double distance_x = local_player->GetPosition().x - block_position.x - 0.5;
            const double distance_y = local_player->GetPosition().y + 1.5 - block_position.y - 0.5;
            const double distance_z = local_player->GetPosition().z - block_position.z - 0.5;

            if (std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z) > 6.0)
            {
                digging_state = DiggingState::Waiting;

                return;
            }
        }

        std::shared_ptr<ServerboundPlayerActionPacket> msg_digging(new ServerboundPlayerActionPacket);
        msg_digging->SetAction((int)PlayerDiggingStatus::StartDigging);
        msg_digging->SetPos(block_position.ToNetworkPosition());
        
        // TODO : maybe one magic and clever math formula can be used for this
        PlayerDiggingFace face;
        if (block_normal.x == -1)
        {
            face = PlayerDiggingFace::West;
        }
        else if (block_normal.x == 1)
        {
            face = PlayerDiggingFace::East;
        }
        else if (block_normal.y == -1)
        {
            face = PlayerDiggingFace::Bottom;
        }
        else if (block_normal.y == 1)
        {
            face = PlayerDiggingFace::Top;
        }
        else if (block_normal.z == -1)
        {
            face = PlayerDiggingFace::North;
        }
        else if (block_normal.z == 1)
        {
            face = PlayerDiggingFace::South;
        }
        msg_digging->SetDirection((int)face);

        network_manager->Send(msg_digging);
        
        if (creative_mode)
        {
            std::shared_ptr<ServerboundPlayerActionPacket> end_digging(new ServerboundPlayerActionPacket);
            end_digging->SetPos(block_position.ToNetworkPosition());
            end_digging->SetAction((int)PlayerDiggingStatus::FinishDigging);
            end_digging->SetDirection((int)face);

            network_manager->Send(msg_digging);
            digging_state = DiggingState::Waiting;
        }
        else
        {
            auto start = std::chrono::system_clock::now();

            // We assume we are using bare hands with no bonus/malus
            // TODO : check tool used and bonus/malus
            while (blockstate->GetHardness() == -2.0f ||
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0f < 5.0f * blockstate->GetHardness())
            {
                if (digging_state == DiggingState::Stop)
                {
                    std::shared_ptr<ServerboundPlayerActionPacket> stop_digging(new ServerboundPlayerActionPacket);
                    stop_digging->SetPos(block_position.ToNetworkPosition());
                    stop_digging->SetAction((int)PlayerDiggingStatus::CancelDigging);
                    stop_digging->SetDirection((int)face);

                    network_manager->Send(stop_digging);

                    digging_state = DiggingState::Waiting;

                    return;
                }

                std::shared_ptr<Blockstate> current_blockstate;
                Position current_position;
                Position current_normal;
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());
                    current_blockstate = world->Raycast(local_player->GetPosition() + Vector3<double>(0.0, 1.65, 0.0), local_player->GetFrontVector(), 6.5f, current_position, current_normal);
                }

                // The block has changed or the player looks at another block
                if (blockstate != current_blockstate ||
                    block_position != current_position)
                {
                    std::shared_ptr<ServerboundPlayerActionPacket> stop_digging(new ServerboundPlayerActionPacket);
                    stop_digging->SetPos(block_position.ToNetworkPosition());
                    stop_digging->SetAction((int)PlayerDiggingStatus::CancelDigging);
                    stop_digging->SetDirection((int)face);

                    network_manager->Send(stop_digging);

                    digging_state = DiggingState::Waiting;

                    return;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }

            // If we are here it means the digging is supposed to be finished
            std::shared_ptr<ServerboundPlayerActionPacket> stop_digging(new ServerboundPlayerActionPacket);
            stop_digging->SetPos(block_position.ToNetworkPosition());
            stop_digging->SetAction((int)PlayerDiggingStatus::FinishDigging);
            stop_digging->SetDirection((int)face);

            network_manager->Send(stop_digging);

            digging_state = DiggingState::Waiting;
        }
    }

    const bool InterfaceClient::DigAt(const Botcraft::Position& location, const PlayerDiggingFace face)
    {
        if (!network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
        {
            return false;
        }

        if (!GoTo(location, true, 0))
        {
            return false;
        }

        std::shared_ptr<Blockstate> blockstate;
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            const Block* block = world->GetBlock(location);

            if (!block || block->GetBlockstate()->IsAir())
            {
                return true;
            }
            blockstate = block->GetBlockstate();
        }

        if (blockstate->IsFluid() ||
            blockstate->GetHardness() == -1.0f)
        {
            return false;
        }

        std::shared_ptr<ServerboundPlayerActionPacket> msg_digging(new ServerboundPlayerActionPacket);
        msg_digging->SetAction((int)PlayerDiggingStatus::StartDigging);
        msg_digging->SetPos(location.ToNetworkPosition());
        msg_digging->SetDirection((int)face);
        network_manager->Send(msg_digging);

        const long long int expected_mining_time = 1000.0f * (creative_mode ? 0.0f : 5.0f * blockstate->GetHardness());

        if (expected_mining_time > 60000)
        {
            std::cout << "Starting an expected " << expected_mining_time / 1000.0f << " seconds long mining at " << location << ". A little help?" << std::endl;
        }

        auto start = std::chrono::system_clock::now();
        bool finished_sent = false;
        while (true)
        {
            long long int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
            if (elapsed > 5000 + expected_mining_time)
            {
                std::cerr << "Something went wrong waiting block breaking confirmation (Timeout)." << std::endl;
                return false;
            }
            if (elapsed >= expected_mining_time
                && !finished_sent)
            {
                std::shared_ptr<ServerboundPlayerActionPacket> msg_finish(new ServerboundPlayerActionPacket);
                msg_finish->SetAction((int)PlayerDiggingStatus::FinishDigging);
                msg_finish->SetPos(location.ToNetworkPosition());
                msg_finish->SetDirection((int)face);
                network_manager->Send(msg_finish);

                finished_sent = true;
            }
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                const Block* block = world->GetBlock(location);

                if (!block || block->GetBlockstate()->IsAir())
                {
                    return true;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return true;
    }

    void InterfaceClient::StopDigging()
    {
        if (digging_state == DiggingState::Digging)
        {
            digging_state = DiggingState::Stop;
        }
    }

    const bool InterfaceClient::GoTo(const Position &goal, const bool in_range, const int min_end_dist, const float speed)
    {
        if (!network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
        {
            return false;
        }

        blackboard.Set("pathfinding.target", goal);

        blackboard.Set("pathfinding.dist_tolerance", in_range ? 4 : 0);
        blackboard.Set("pathfinding.min_end_dist", min_end_dist);
        blackboard.Set("pathfinding.travel_speed", speed);
        blackboard.Set("pathfinding.allow_jump", true);

        return true;
    }

    void InterfaceClient::StopPathFinding()
    {
        pathfinding_task.Stop();
    }

    const bool InterfaceClient::PlaceBlock(const std::string& item, const Position& location, const PlayerDiggingFace placed_face, const bool wait_confirmation)
    {
        if (!network_manager
            || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play
            || !inventory_manager
            || !inventory_manager->GetPlayerInventory()
            || !entity_manager)
        {
            return false;
        }

        if (!GoTo(location, true, 1))
        {
            return false;
        }

        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            const Block* block = world->GetBlock(location);

            if (block && !block->GetBlockstate()->IsAir())
            {
                return false;
            }
        }

        {
            const AABB this_box_collider = AABB(Vector3<double>(location.x + 0.5, location.y + 0.5, location.z + 0.5), Vector3<double>(0.5, 0.5, 0.5));
            std::lock_guard<std::mutex> entity_manager_guard(entity_manager->GetMutex());
            const std::unordered_map<int, std::shared_ptr<Entity> >& entities = entity_manager->GetEntities();
            for (auto it = entities.begin(); it != entities.end(); ++it)
            {
                if (this_box_collider.Collide(it->second->GetCollider()))
                {
                    return false;
                }
            }
        }

        std::shared_ptr<ServerboundUseItemOnPacket> place_block_msg(new ServerboundUseItemOnPacket);
        place_block_msg->SetLocation(location.ToNetworkPosition());
        place_block_msg->SetDirection((int)placed_face);
        switch (placed_face)
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

        // Left click case, main hand
        place_block_msg->SetHand((int)Hand::Right);

        if (!SetItemInHand(item, Hand::Right))
        {
            std::cout << "Error, can't place block if I don't have it in my inventory" << std::endl;
            return false;
        }
        int num_item_in_hand;
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            num_item_in_hand = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HOTBAR_START + inventory_manager->GetIndexHotbarSelected()).GetItemCount();
        }

        // Place the block
        network_manager->Send(place_block_msg);
        
        if (!wait_confirmation)
        {
            return true;
        }

        bool is_block_ok = false;
        bool is_slot_ok = false;
        auto start = std::chrono::system_clock::now();
        while (!is_block_ok || !is_slot_ok)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "[" << network_manager->GetMyName() << "] Something went wrong waiting block placement confirmation at " << location << " (Timeout)." << std::endl;
                return false;
            }
            if (!is_block_ok)
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                const Block* block = world->GetBlock(location);

                if (block && block->GetBlockstate()->GetName() == item)
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
                return true;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return true;
    }

    const bool InterfaceClient::InteractWithBlock(const Position& location, const PlayerDiggingFace interact_face, const bool animation)
    {
        if (!network_manager
            || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play
            || !entity_manager)
        {
            return false;
        }

        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
        const Vector3<double> dist(std::floor(local_player->GetPosition().x) - location.x, std::floor(local_player->GetPosition().y) - location.y, std::floor(local_player->GetPosition().z) - location.z);
        double distance = std::sqrt(dist.dot(dist));
        if (distance > 5.0f)
        {
            std::cout << "I am asked to interact at " << location << " but I'm affraid that's out of my range (" << distance << "m)." << std::endl;
            return false;
        }

        std::shared_ptr<ServerboundUseItemOnPacket> place_block_msg(new ServerboundUseItemOnPacket);
        place_block_msg->SetLocation(location.ToNetworkPosition());
        place_block_msg->SetDirection((int)interact_face);
        switch (interact_face)
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
        network_manager->Send(place_block_msg);

        if (animation)
        {
            std::shared_ptr<ServerboundSwingPacket> animation_msg(new ServerboundSwingPacket);
            animation_msg->SetHand((int)Hand::Right);
            network_manager->Send(animation_msg);
        }

        return true;
    }

    void InterfaceClient::Handle(ClientboundSetHealthPacket& msg)
    {
        BaseClient::Handle(msg);

        if (msg.GetHealth() <= 0.0f)
        {
            StopPathFinding();
            Say("I don't feel so good");
        }
    }

#if PROTOCOL_VERSION > 493
    void InterfaceClient::Handle(ClientboundBlockBreakAckPacket &msg)
    {
        BaseClient::Handle(msg);

        if (digging_state == DiggingState::Digging && !msg.GetAllGood())
        {
            StopDigging();
        }
    }
#endif

    const bool InterfaceClient::SwapItemsInContainer(const short container_id, const short first_slot, const short second_slot)
    {
        std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);
        if (!container)
        {
            return false;
        }

        Slot copied_slot;
        std::shared_ptr<ServerboundContainerClickPacket> click_window_msg;
        int transaction_id;
        //Click on the first slot, transferring the slot to the cursor
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            copied_slot = container->GetSlots().at(first_slot);
        }

        click_window_msg = std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);

        click_window_msg->SetContainerId(container_id);
        click_window_msg->SetSlotNum(first_slot);
        click_window_msg->SetButtonNum(0); // Left click to select the stack
        click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
        click_window_msg->SetItemStack(copied_slot);
#else
        click_window_msg->SetCarriedItem(copied_slot);
#endif

        transaction_id = SendInventoryTransaction(click_window_msg);

        // Wait for the click confirmation (versions < 1.17)
#if PROTOCOL_VERSION < 755
        auto start = std::chrono::system_clock::now();
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to select first slot during swap inventory (Timeout)." << std::endl;
                return false;
            }
            TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
            if (transaction_state == TransactionState::Accepted)
            {
                break;
            }
            // The transaction has been refused by the server, don't bother with other clicks
            else if (transaction_state == TransactionState::Refused)
            {
                return false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
#endif

        //Click on the second slot, transferring the cursor to the slot
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            copied_slot = container->GetSlots().at(second_slot);
        }
        click_window_msg = std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);

        click_window_msg->SetContainerId(container_id);
        click_window_msg->SetSlotNum(second_slot);
        click_window_msg->SetButtonNum(0); // Left click to select the stack
        click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
        click_window_msg->SetItemStack(copied_slot);
#else
        click_window_msg->SetCarriedItem(copied_slot);
#endif

        transaction_id = SendInventoryTransaction(click_window_msg);

        // Wait for confirmation in version < 1.17
#if PROTOCOL_VERSION < 755
        start = std::chrono::system_clock::now();
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to select second slot during swap inventory (Timeout)." << std::endl;
                return false;
            }
            
            TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
            if (transaction_state == TransactionState::Accepted)
            {
                break;
            }
            // The transaction has been refused by the server, don't bother with other clicks
            else if (transaction_state == TransactionState::Refused)
            {
                return false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
#endif
            
        //Click once again on the first slot, transferring the cursor to the slot
        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());
            copied_slot = container->GetSlots().at(first_slot);
        }
        click_window_msg = std::shared_ptr<ServerboundContainerClickPacket>(new ServerboundContainerClickPacket);

        click_window_msg->SetContainerId(container_id);
        click_window_msg->SetSlotNum(first_slot);
        click_window_msg->SetButtonNum(0); // Left click to select the stack
        click_window_msg->SetClickType(0); // Regular click
#if PROTOCOL_VERSION < 755
        click_window_msg->SetItemStack(copied_slot);
#else
        click_window_msg->SetCarriedItem(copied_slot);
#endif

        transaction_id = SendInventoryTransaction(click_window_msg);
        
        // Wait for confirmation in version < 1.17
#if PROTOCOL_VERSION < 755
        start = std::chrono::system_clock::now();
        while (true)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to select third slot during swap inventory (Timeout)." << std::endl;
                return false;
            }

            TransactionState transaction_state = inventory_manager->GetTransactionState(container_id, transaction_id);
            if (transaction_state == TransactionState::Accepted)
            {
                break;
            }
            // The transaction has been refused by the server, don't bother with other clicks
            else if (transaction_state == TransactionState::Refused)
            {
                return false;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
#endif

        return true;
    }

    const bool InterfaceClient::SetItemInHand(const std::string& item_name, const Hand hand)
    {
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
                return true;
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
                return false;
            }
        }

        if (!SwapItemsInContainer(Window::PLAYER_INVENTORY_INDEX, inventory_correct_slot_index, inventory_destination_slot_index))
        {
            return false;
        }
        return true;
    }

    const bool InterfaceClient::Eat(const std::string& food_name, const bool wait_confirmation)
    {
        if (!SetItemInHand(food_name, Hand::Left))
        {
            return false;
        }

        const char current_stack_size = inventory_manager->GetOffHand().GetItemCount();
        std::shared_ptr<ServerboundUseItemPacket> use_item_msg(new ServerboundUseItemPacket);
        use_item_msg->SetHand((int)Hand::Left);
        network_manager->Send(use_item_msg);

        if (!wait_confirmation)
        {
            return true;
        }

        auto start = std::chrono::system_clock::now();
        while (inventory_manager->GetOffHand().GetItemCount() == current_stack_size)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to eat (Timeout)." << std::endl;
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return true;
    }

    const bool InterfaceClient::OpenContainer(const Position& pos)
    {
        // Can't reach the container
        if (!GoTo(pos, true))
        {
            return false;
        }

        // Open the container
        if (!InteractWithBlock(pos, PlayerDiggingFace::Top))
        {
            return false;
        }

        // Wait for a window to be opened
        auto start = std::chrono::system_clock::now();
        while(inventory_manager->GetFirstOpenedWindowId() == -1)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to open container (Timeout)." << std::endl;
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return true;
    }

    const bool InterfaceClient::CloseContainer(const short container_id)
    {
        std::shared_ptr<ServerboundContainerClosePacket> close_container_msg = std::shared_ptr<ServerboundContainerClosePacket>(new ServerboundContainerClosePacket);
        close_container_msg->SetContainerId(container_id);
        network_manager->Send(close_container_msg);

        // There is no confirmation from the server, so we
        // can simply close the window here
        inventory_manager->EraseInventory(container_id);

        return true;
    }

    void InterfaceClient::Jump()
    {
        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
        local_player->SetSpeedY(0.4196141); // Not sure about this. I tried to calculate it in order to get a 1.25 block height jump (reached in 6 ticks)
    }
}
