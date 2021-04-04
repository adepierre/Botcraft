#include "botcraft/Game/InterfaceClient.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/Player.hpp"
#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"

#include "protocolCraft/enums.hpp"

#include <queue>
#include <unordered_map>

using namespace ProtocolCraft;

namespace Botcraft
{
    struct PathNode
    {
        Position pos;
        float score; // distance from start + heuristic to goal
        PathNode(const Position &p, const float s)
        {
            pos = p;
            score = s;
        }
    };
    
    bool operator>(const PathNode &a, const PathNode &b)
    {
        return a.score > b.score;
    }
    
    InterfaceClient::InterfaceClient(const bool use_renderer_, const bool afk_only_) : BaseClient(use_renderer_, afk_only_)
    {
        pathfinding_state = PathFindingState::Waiting;
        digging_state = DiggingState::Waiting;
    }

    InterfaceClient::~InterfaceClient()
    {

    }

    void InterfaceClient::Say(const std::string &msg)
    {
        if (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            std::shared_ptr<ChatMessageServerbound> chat_message(new ChatMessageServerbound);
            chat_message->SetMessage(msg);
            network_manager->Send(chat_message);
        }
    }

    void InterfaceClient::Respawn()
    {
        if (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            std::shared_ptr<ClientStatus> status_message(new ClientStatus);
            status_message->SetActionID(0);
            network_manager->Send(status_message);
        }
    }

    const bool InterfaceClient::GetShouldBeClosed() const
    {
        return should_be_closed;
    }

    const DiggingState InterfaceClient::GetDiggingState() const
    {
        return digging_state;
    }

    void InterfaceClient::Dig()
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
        std::shared_ptr<Player> player = entity_manager->GetPlayer();
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            blockstate = world->Raycast(player->GetPosition() + Vector3<double>(0.0, 1.65, 0.0), player->GetFrontVector(), 6.5f, block_position, block_normal);
        
            if (!blockstate ||
                blockstate->IsFluid() ||
                blockstate->GetHardness() == -1.0f)
            {
                digging_state = DiggingState::Waiting;
                
                return;
            }

            const double distance_x = player->GetPosition().x - block_position.x - 0.5;
            const double distance_y = player->GetPosition().y + 1.5 - block_position.y - 0.5;
            const double distance_z = player->GetPosition().z - block_position.z - 0.5;

            if (std::sqrt(distance_x * distance_x + distance_y * distance_y + distance_z * distance_z) > 6.0)
            {
                digging_state = DiggingState::Waiting;

                return;
            }
        }

        std::shared_ptr<PlayerDigging> msg_digging(new PlayerDigging);
        msg_digging->SetStatus((int)PlayerDiggingStatus::StartDigging);
        msg_digging->SetLocation(block_position.ToNetworkPosition());
        
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
        msg_digging->SetFace((int)face);

        network_manager->Send(msg_digging);
        
        if (creative_mode)
        {
            std::shared_ptr<PlayerDigging> end_digging(new PlayerDigging);
            end_digging->SetLocation(block_position.ToNetworkPosition());
            end_digging->SetStatus((int)PlayerDiggingStatus::FinishDigging);
            end_digging->SetFace((int)face);

            network_manager->Send(msg_digging);
            digging_state = DiggingState::Waiting;
        }
        else
        {
            auto start = std::chrono::system_clock::now();

            // We assume we are using the right tool with no bonus/malus
            // TODO : check tool used and bonus/malus
            while (blockstate->GetHardness() == -2.0f ||
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0f < 1.5f * blockstate->GetHardness())
            {
                if (digging_state == DiggingState::Stop)
                {
                    std::shared_ptr<PlayerDigging> stop_digging(new PlayerDigging);
                    stop_digging->SetLocation(block_position.ToNetworkPosition());
                    stop_digging->SetStatus((int)PlayerDiggingStatus::CancelDigging);
                    stop_digging->SetFace((int)face);

                    network_manager->Send(stop_digging);

                    digging_state = DiggingState::Waiting;

                    return;
                }

                std::shared_ptr<Blockstate> current_blockstate;
                Position current_position;
                Position current_normal;
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());
                    current_blockstate = world->Raycast(player->GetPosition() + Vector3<double>(0.0, 1.65, 0.0), player->GetFrontVector(), 6.5f, current_position, current_normal);
                }

                // The block has changed or the player looks at another block
                if (blockstate != current_blockstate ||
                    block_position != current_position)
                {
                    std::shared_ptr<PlayerDigging> stop_digging(new PlayerDigging);
                    stop_digging->SetLocation(block_position.ToNetworkPosition());
                    stop_digging->SetStatus((int)PlayerDiggingStatus::CancelDigging);
                    stop_digging->SetFace((int)face);

                    network_manager->Send(stop_digging);

                    digging_state = DiggingState::Waiting;

                    return;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }

            // If we are here it means the digging is supposed to be finished
            std::shared_ptr<PlayerDigging> stop_digging(new PlayerDigging);
            stop_digging->SetLocation(block_position.ToNetworkPosition());
            stop_digging->SetStatus((int)PlayerDiggingStatus::FinishDigging);
            stop_digging->SetFace((int)face);

            network_manager->Send(stop_digging);

            digging_state = DiggingState::Waiting;
        }
    }

    void InterfaceClient::StopDigging()
    {
        if (digging_state == DiggingState::Digging)
        {
            digging_state = DiggingState::Stop;
        }
    }

    void InterfaceClient::SetAutoRespawn(const bool b)
    {
        auto_respawn = b;
    }

    const bool InterfaceClient::GoTo(const Position &goal, const float speed)
    {
        if (!network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
        {
            return false;
        }

        if (pathfinding_state != PathFindingState::Waiting)
        {
            const std::string answer = "I am asked to go to " + std::to_string(goal.x) + " " + std::to_string(goal.y) + " " + std::to_string(goal.z) + " but I'm affraid I can't do that";
            std::cout << answer << std::endl;
            return false;
        }
        
        std::shared_ptr<Player> player = entity_manager->GetPlayer();
        Position current_position;
        do
        {
            // Wait until we are on the ground
            while (!player->GetOnGround())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            // Get the position
            current_position = Position(std::floor(player->GetPosition().x), std::floor(player->GetPosition().y), std::floor(player->GetPosition().z));

            std::vector<Position> path;
            pathfinding_state = PathFindingState::Searching;

            if (!world->GetBlock(goal))
            {
                std::cout << "Current goal position is either air or not loaded, trying to get closer to load the chunk" << std::endl;
                Vector3<double> goal_direction(goal.x - current_position.x, goal.y - current_position.y, goal.z - current_position.z);
                goal_direction.Normalize();
                path = FindPath(current_position, current_position + Position(goal_direction.x * 32, goal_direction.y * 32, goal_direction.z * 32));
            }
            else
            {
                path = FindPath(current_position, goal);
            }

            if (pathfinding_state == PathFindingState::Stop)
            {
                pathfinding_state = PathFindingState::Waiting;
                return false;
            }

            if (path.size() == 0 || path[path.size() - 1] == current_position)
            {
                std::cout << "Warning, path finding cannot find a better position than " << current_position << ". Staying there." << std::endl;
                pathfinding_state = PathFindingState::Waiting;
                return false;
            }

            pathfinding_state = PathFindingState::Moving;
            for (int i = 0; i < path.size(); ++i)
            {
                if (pathfinding_state == PathFindingState::Stop)
                {
                    pathfinding_state = PathFindingState::Waiting;
                    return false;
                }

                // Wait until we are on the ground
                while (!player->GetOnGround())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                {
                    std::lock_guard<std::mutex> player_lock(player->GetMutex());
                    const Vector3<double> temp_dest(path[i].x + 0.5, path[i].y, path[i].z + 0.5);
                    player->LookAt(temp_dest);
                    player->SetPosition(temp_dest);

                    // Get the position
                    current_position = Position(std::floor(player->GetPosition().x), std::floor(player->GetPosition().y), std::floor(player->GetPosition().z));
                }
                std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000 / speed)));
            }

        } while (!(current_position == goal));

        pathfinding_state = PathFindingState::Waiting;
        return true;
    }

    void InterfaceClient::StopPathFinding()
    {
        if (pathfinding_state != PathFindingState::Waiting)
        {
            pathfinding_state = PathFindingState::Stop;
        }
    }

    const bool InterfaceClient::PlaceBlock(const std::string& item, const Position& location, const PlayerDiggingFace placed_face)
    {
        if (!network_manager
            || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play
            || !inventory_manager
            || !inventory_manager->GetPlayerInventory()
            || !entity_manager)
        {
            return false;
        }

        std::shared_ptr<Player> player = entity_manager->GetPlayer();
        const Vector3<double> dist(std::floor(player->GetPosition().x) - location.x, std::floor(player->GetPosition().y) - location.y, std::floor(player->GetPosition().z) - location.z);
        double distance = std::sqrt(dist.dot(dist));
        if (distance > 5.0f)
        {
            std::cout << "I am asked to place a " << item << " at " << location << " but I'm affraid that's out of my range (" << distance << "m)." << std::endl;
            return false;
        }

        std::shared_ptr<PlayerBlockPlacement> place_block_msg(new PlayerBlockPlacement);
        place_block_msg->SetLocation(location.ToNetworkPosition());
        place_block_msg->SetFace((int)placed_face);
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
        place_block_msg->SetInsideBlock(false);
#endif

        // Left click case
        place_block_msg->SetHand((int)Hand::Left);

        // We need to check the inventory
        // If the currently selected item is the right one, just go for it
        const Slot& current_selected = inventory_manager->GetHotbarSelected();
        if (!current_selected.IsEmptySlot()
#if PROTOCOL_VERSION < 347
            && AssetsManager::getInstance().Items().at(current_selected.GetBlockID()).at(current_selected.GetItemDamage())->GetName() == item)
#else
            && AssetsManager::getInstance().Items().at(current_selected.GetItemID())->GetName() == item)
#endif
        {
            network_manager->Send(place_block_msg);
            std::lock_guard<std::mutex> lock(player->GetMutex());
            player->LookAt(Vector3<double>(location) + Vector3<double>(0.5, 0.5, 0.5), true);
            return true;
        }

        // Otherwise we need to find a slot with the given item
        short inventory_correct_slot_index = -1;
        const std::map<short, Slot>& inventory_slots = inventory_manager->GetPlayerInventory()->GetSlots();

        for (auto it = inventory_slots.begin(); it != inventory_slots.end(); ++it)
        {
            if (it->first >= Window::INVENTORY_STORAGE_START
                && it->first < Window::INVENTORY_OFFHAND_INDEX
                && !it->second.IsEmptySlot()
#if PROTOCOL_VERSION < 347
                && AssetsManager::getInstance().Items().at(it->second.GetBlockID()).at(it->second.GetItemDamage())->GetName() == item)
#else
                && AssetsManager::getInstance().Items().at(it->second.GetItemID())->GetName() == item)
#endif
            {
                inventory_correct_slot_index = it->first;
                break;
            }
        }

        if (inventory_correct_slot_index == -1)
        {
            std::cout << "I am asked to place a " << item << " at " << location << " but I'm affraid I don't have that kind of item in my inventory." << std::endl;
            return false;
        }

        // We need to swap the currently selected slot in the
        // hotbar with the one with the correct item

        std::shared_ptr<ClickWindow> click_window_msg(new ClickWindow);

        // Click on the desired item
        click_window_msg->SetWindowId(Window::PLAYER_INVENTORY_INDEX);
        click_window_msg->SetSlot(inventory_correct_slot_index);
        click_window_msg->SetButton(0); // Left click to select the stack
        click_window_msg->SetMode(0); // Regular click
        click_window_msg->SetClickedItem(inventory_slots.at(inventory_correct_slot_index));

        SendInventoryTransaction(click_window_msg);

        // Click in the hotbar
        click_window_msg->SetSlot(Window::INVENTORY_HOTBAR_START + inventory_manager->GetIndexHotbarSelected());
        click_window_msg->SetClickedItem(inventory_manager->GetHotbarSelected());

        SendInventoryTransaction(click_window_msg);

        // Click back on the slot where the desired item was
        click_window_msg->SetSlot(inventory_correct_slot_index);
        click_window_msg->SetClickedItem(inventory_slots.at(inventory_correct_slot_index));

        SendInventoryTransaction(click_window_msg);

        // Wait for the server confirmation so
        // the hotbar selected slot is the item we need
        auto start = std::chrono::system_clock::now();
        while (
#if PROTOCOL_VERSION < 347
            AssetsManager::getInstance().Items().at(inventory_manager->GetHotbarSelected().GetBlockID()).at(inventory_manager->GetHotbarSelected().GetItemDamage())->GetName() != item)
#else
            AssetsManager::getInstance().Items().at(inventory_manager->GetHotbarSelected().GetItemID())->GetName() != item)
#endif
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to swap inventory slots for block placing (Timeout)." << std::endl;
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        // Small delay to be sure the server set our new hotbar item as the current item
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Place the block
        network_manager->Send(place_block_msg);
        std::lock_guard<std::mutex> lock(player->GetMutex());
        player->LookAt(Vector3<double>(location) + Vector3<double>(0.5, 0.5, 0.5), true);

        return true;
    }

    const bool InterfaceClient::InteractBlock(const Position& location, const PlayerDiggingFace interact_face, const bool animation)
    {
        if (!network_manager
            || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play
            || !entity_manager)
        {
            return false;
        }

        std::shared_ptr<Player> player = entity_manager->GetPlayer();
        const Vector3<double> dist(std::floor(player->GetPosition().x) - location.x, std::floor(player->GetPosition().y) - location.y, std::floor(player->GetPosition().z) - location.z);
        double distance = std::sqrt(dist.dot(dist));
        if (distance > 5.0f)
        {
            std::cout << "I am asked to interact at " << location << " but I'm affraid that's out of my range (" << distance << "m)." << std::endl;
            return false;
        }

        std::shared_ptr<PlayerBlockPlacement> place_block_msg(new PlayerBlockPlacement);
        place_block_msg->SetLocation(location.ToNetworkPosition());
        place_block_msg->SetFace((int)interact_face);
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
        place_block_msg->SetInsideBlock(false);
#endif
        place_block_msg->SetHand((int)Hand::Left);
        network_manager->Send(place_block_msg);

        if (animation)
        {
            std::shared_ptr<AnimationServerbound> animation_msg(new AnimationServerbound);
            animation_msg->SetHand((int)Hand::Left);
            network_manager->Send(animation_msg);
        }

        return true;
    }

    void InterfaceClient::Handle(UpdateHealth &msg)
    {
        BaseClient::Handle(msg);

        if (msg.GetHealth() <= 0.0f)
        {
            StopPathFinding();
            Say("I don't feel so good");
        }
    }

#if PROTOCOL_VERSION > 493
    void InterfaceClient::Handle(AcknowledgePlayerDigging &msg)
    {
        BaseClient::Handle(msg);

        if (digging_state == DiggingState::Digging && !msg.GetSuccessful())
        {
            StopDigging();
        }
    }
#endif

    const float Heuristic(const Position &a, const Position &b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
    }

    const std::vector<Position> InterfaceClient::FindPath(const Position &start, const Position &end)
    {
        const std::vector<Position> neighbour_offsets({ Position(1, 0, 0), Position(-1, 0, 0), Position(0, 0, 1), Position(0, 0, -1) });
        std::priority_queue<PathNode, std::vector<PathNode>, std::greater<PathNode> > nodes_to_explore;
        std::unordered_map<Position, Position> came_from;
        std::unordered_map<Position, float> cost;


        nodes_to_explore.emplace(PathNode(start, 0.0f));
        came_from[start] = start;
        cost[start] = 0.0f;

        int count_visit = 0;

        while (!nodes_to_explore.empty())
        {
            count_visit++;
            PathNode current_node = nodes_to_explore.top();
            nodes_to_explore.pop();

            if (current_node.pos == end || count_visit > 10000)
            {
                break;
            }

            // For each neighbour, check if it's reachable
            // and add it to the search list if it is
            for (int i = 0; i < neighbour_offsets.size(); ++i)
            {
                Position next_location = current_node.pos + neighbour_offsets[i];
                std::lock_guard<std::mutex> world_guard(world->GetMutex());

                // We want a solid block to walk on it
                // with two non solid blocks on top of it to walk through
                // we do not want to fall more than two blocks
                // ?  ?
                // x  ?
                // x  ?
                //--- ?
                //    ?
                //    ?
                const Block *block1 = world->GetBlock(next_location + Position(0, 1, 0));
                if (block1 && block1->GetBlockstate()->IsSolid())
                {
                    // ?  ?
                    // x  o
                    // x  ?
                    //--- ?
                    //    ?
                    //    ?
                    // This case means we cannot go in this direction
                    continue;
                }
                else
                {
                    const Block *block0 = world->GetBlock(next_location);
                    if (block0 && block0->GetBlockstate()->IsSolid())
                    {
                        // ?  ?
                        // x  
                        // x  o
                        //--- ?
                        //    ?
                        //    ?
                        const Block *block2 = world->GetBlock(next_location + Position(0, 2, 0));
                        if (!block2 || !block2->GetBlockstate()->IsSolid())
                        {
                            // ?  
                            // x   
                            // x  o
                            //--- ?
                            //    ?
                            //    ?
                            const Block *block3 = world->GetBlock(current_node.pos + Position(0, 2, 0));
                            if (!block3 || !block3->GetBlockstate()->IsSolid())
                            {
                                //    
                                // x   
                                // x  o
                                //--- ?
                                //    ?
                                //    ?
                                float new_cost = cost[current_node.pos] + 2.0f;
                                if (cost.find(next_location + Position(0, 1, 0)) == cost.end() ||
                                    new_cost < cost[next_location + Position(0, 1, 0)])
                                {
                                    cost[next_location + Position(0, 1, 0)] = new_cost;
                                    nodes_to_explore.emplace(PathNode(next_location + Position(0, 1, 0), new_cost + Heuristic(next_location + Position(0, 1, 0), end)));
                                    came_from[next_location + Position(0, 1, 0)] = current_node.pos;
                                    continue;
                                }
                                // If this neighbour is already known with a better path
                                else
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                // o  
                                // x   
                                // x  o
                                //--- ?
                                //    ?
                                //    ?
                                continue;
                            }
                        }
                        // This case means we cannot go in this direction
                        else
                        {
                            // ?  o
                            // x   
                            // x  o
                            //--- ?
                            //    ?
                            //    ?
                            continue;
                        }
                    }
                    else
                    {
                        const Block *blockm1 = world->GetBlock(next_location + Position(0, -1, 0));
                        if (blockm1 && blockm1->GetBlockstate()->IsSolid() || next_location.y == 0)
                        {
                            // ?  ?
                            // x  
                            // x  
                            //--- o
                            //    ?
                            //    ?
                            float new_cost = cost[current_node.pos] + 1.0f;
                            if (cost.find(next_location) == cost.end() ||
                                new_cost < cost[next_location])
                            {
                                cost[next_location] = new_cost;
                                nodes_to_explore.emplace(PathNode(next_location, new_cost + Heuristic(next_location, end)));
                                came_from[next_location] = current_node.pos;
                                continue;
                            }
                            // If this neighbour is already known with a better path
                            else
                            {
                                continue;
                            }
                        }
                        else
                        {
                            // ?  ?
                            // x   
                            // x   
                            //---  
                            //    ?
                            //    ?
                            const Block *blockm2 = world->GetBlock(next_location + Position(0, -2, 0));
                            if (blockm2 && blockm2->GetBlockstate()->IsSolid() || next_location.y == 1)
                            {
                                // ?  ?
                                // x   
                                // x   
                                //---  
                                //    o
                                //    ?
                                float new_cost = cost[current_node.pos] + 2.0f;
                                if (cost.find(next_location + Position(0, -1, 0)) == cost.end() ||
                                    new_cost < cost[next_location + Position(0, -1, 0)])
                                {
                                    cost[next_location + Position(0, -1, 0)] = new_cost;
                                    nodes_to_explore.emplace(PathNode(next_location + Position(0, -1, 0), new_cost + Heuristic(next_location + Position(0, -1, 0), end)));
                                    came_from[next_location + Position(0, -1, 0)] = current_node.pos;
                                    continue;
                                }
                                // If this neighbour is already known with a better path
                                else
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                // ?  ?
                                // x   
                                // x   
                                //---  
                                //    
                                //    ?
                                const Block *blockm3 = world->GetBlock(next_location + Position(0, -3, 0));
                                if (blockm3 && blockm3->GetBlockstate()->IsSolid() || next_location.y == 2)
                                {
                                    // ?  ?
                                    // x   
                                    // x   
                                    //---  
                                    //    
                                    //    o
                                    float new_cost = cost[current_node.pos] + 3.0f;
                                    if (cost.find(next_location + Position(0, -2, 0)) == cost.end() ||
                                        new_cost < cost[next_location + Position(0, -2, 0)])
                                    {
                                        cost[next_location + Position(0, -2, 0)] = new_cost;
                                        nodes_to_explore.emplace(PathNode(next_location + Position(0, -2, 0), new_cost + Heuristic(next_location + Position(0, -2, 0), end)));
                                        came_from[next_location + Position(0, -2, 0)] = current_node.pos;
                                        continue;
                                    }
                                    // If this neighbour is already known with a better path
                                    else
                                    {
                                        continue;
                                    }
                                }
                                else
                                {
                                    // ?  ?
                                    // x   
                                    // x   
                                    //---  
                                    //    
                                    //     
                                    continue;
                                }
                            }

                        }
                    }
                }
            } // neighbour loop
        }

        auto it_end_path = came_from.find(end);

        // This means the search stops without finding a path,
        // return path to the closest node found
        if (it_end_path == came_from.end())
        {
            float best_float_dist = std::numeric_limits<float>::max();

            for (auto it = came_from.begin(); it != came_from.end(); ++it)
            {
                const float d = Heuristic(it->first, end);
                if (d < best_float_dist)
                {
                    best_float_dist = d;
                    it_end_path = it;
                }
            }
        }

        std::deque<Position> output_deque;
        output_deque.push_front(it_end_path->first);
        while (!(it_end_path->second == start))
        {
            it_end_path = came_from.find(it_end_path->second);
            output_deque.push_front(it_end_path->first);
        }
        return std::vector<Position>(output_deque.begin(), output_deque.end());
    }
}