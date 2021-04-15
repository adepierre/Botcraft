#include "botcraft/Game/InterfaceClient.hpp"
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
            std::shared_ptr<ServerboundChatPacket> chat_message(new ServerboundChatPacket);
            chat_message->SetMessage(msg);
            network_manager->Send(chat_message);
        }
    }

    void InterfaceClient::Respawn()
    {
        if (network_manager && network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
        {
            std::shared_ptr<ServerboundClientCommandPacket> status_message(new ServerboundClientCommandPacket);
            status_message->SetAction(0);
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

            // We assume we are using the right tool with no bonus/malus
            // TODO : check tool used and bonus/malus
            while (blockstate->GetHardness() == -2.0f ||
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0f < 1.5f * blockstate->GetHardness())
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

    const bool InterfaceClient::GoTo(const Position &goal, const bool in_range, const float speed)
    {
        if (!network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
        {
            return false;
        }

        if (pathfinding_state != PathFindingState::Waiting)
        {
            std::cout << "I am asked to go to " << goal.x << " " << goal.y << " "
                << goal.z << " but I'm affraid I can't do that" << std::endl;
            return false;
        }
        
        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
        Position current_position;
        do
        {
            // Wait until we are on the ground
            while (!local_player->GetOnGround())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            // Get the position
            current_position = Position(std::floor(local_player->GetPosition().x), std::floor(local_player->GetPosition().y), std::floor(local_player->GetPosition().z));

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
                Position dist = goal - current_position;
                if (in_range && dist.dot(dist) <= 16.0f)
                {
                    pathfinding_state = PathFindingState::Waiting;
                    return true;
                }
                path = FindPath(current_position, goal);
            }

            if (pathfinding_state == PathFindingState::Stop)
            {
                pathfinding_state = PathFindingState::Waiting;
                return false;
            }

            if (path.size() == 0 || path[path.size() - 1] == current_position)
            {
                pathfinding_state = PathFindingState::Waiting;
                if (!in_range)
                {
                    std::cout << "Warning, path finding cannot find a better position than " << current_position << ". Staying there." << std::endl;
                    return false;
                }
                else
                {
                    Position dist = goal - current_position;
                    return dist.dot(dist) <= 16.0f;
                }
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
                while (!local_player->GetOnGround())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                current_position = Position(std::floor(local_player->GetPosition().x), std::floor(local_player->GetPosition().y), std::floor(local_player->GetPosition().z));

                auto start = std::chrono::system_clock::now();
                const Vector3<double> initial_position(current_position.x + 0.5, current_position.y, current_position.z + 0.5);
                const Vector3<double> motion_vector(path[i].x - current_position.x, path[i].y + 0.001 - current_position.y, path[i].z - current_position.z);
                local_player->LookAt(initial_position + motion_vector);

                // This indicates that we got stucked and
                // are in fact not where we think we are
                // Replanning the path is a good idea
                if (std::abs(motion_vector.x) > 1.0 || std::abs(motion_vector.z) > 1.0)
                {
                    std::cout << "Recalculating path..." << std::endl;
                    break;
                }

                // If we have to jump to climb on the next position
                if (path[i].y > current_position.y)
                {
                    Jump();

                    auto now = std::chrono::system_clock::now();
                    bool has_timeout = false;
                    while (local_player->GetY() < path[i].y)
                    {
                        // This indicates that a jump we wanted to make is not possible anymore
                        // recalculating the path
                        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - now).count() >= 3000)
                        {
                            has_timeout = true;
                            break;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    if (has_timeout)
                    {
                        std::cout << "Recalculating path..." << std::endl;
                        break;
                    }
                }

                while (true)
                {
                    auto now = std::chrono::system_clock::now();
                    long long int time_count = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
                    // If we are over the time due to travel one block at the given speed
                    if (time_count > 1000 / speed)
                    {
                        {
                            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                            local_player->SetX((initial_position + motion_vector).x);
                            local_player->SetZ((initial_position + motion_vector).z);
                        }

                        // Update current position
                        current_position = path[i];
                        break;
                    }
                    // Otherwise just move partially toward the goal
                    else
                    {
                        Vector3<double> pos = initial_position + motion_vector * time_count / 1000.0 * speed;
                        {
                            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                            pos.y = local_player->GetPosition().y + 0.0001;
                            local_player->SetPosition(pos);
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
        } while (current_position != goal);

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

        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
        const Vector3<double> dist(std::floor(local_player->GetPosition().x) - location.x, std::floor(local_player->GetPosition().y) - location.y, std::floor(local_player->GetPosition().z) - location.z);
        double distance = std::sqrt(dist.dot(dist));
        if (distance > 5.0f)
        {
            std::cout << "I am asked to place a " << item << " at " << location << " but I'm affraid that's out of my range (" << distance << "m)." << std::endl;
            return false;
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

        // Place the block
        network_manager->Send(place_block_msg);
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        local_player->LookAt(Vector3<double>(location) + Vector3<double>(0.5, 0.5, 0.5), true);

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

    const bool InterfaceClient::SwapItemsInContainer(const short container_id, const short first_slot, const short second_slot)
    {
        Slot initial_second_slot_copy; 
        std::shared_ptr<Window> container = inventory_manager->GetWindow(container_id);
        if (!container)
        {
            return false;
        }

        {
            std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());

            

            const std::map<short, Slot>& slots = container->GetSlots();

            initial_second_slot_copy = slots.at(second_slot);

            // We need to swap the currently held item
            // with the desired one
            std::shared_ptr<ServerboundContainerClickPacket> click_window_msg(new ServerboundContainerClickPacket);

            // Click on the desired item
            click_window_msg->SetContainerId(container_id);
            click_window_msg->SetSlotNum(first_slot);
            click_window_msg->SetButtonNum(0); // Left click to select the stack
            click_window_msg->SetClickType(0); // Regular click
            click_window_msg->SetItemStack(slots.at(first_slot));

            SendInventoryTransaction(click_window_msg);

            // Click in the destination
            click_window_msg->SetSlotNum(second_slot);
            click_window_msg->SetItemStack(slots.at(second_slot));

            SendInventoryTransaction(click_window_msg);

            // Click back on the slot where the desired item was
            click_window_msg->SetSlotNum(first_slot);
            click_window_msg->SetItemStack(slots.at(first_slot));

            SendInventoryTransaction(click_window_msg);
        }

        // Wait for the server confirmation so
        // the hold item is the one we need
        auto start = std::chrono::system_clock::now();
        while (
#if PROTOCOL_VERSION < 347
            container->GetSlot(first_slot).GetBlockID() != initial_second_slot_copy.GetBlockID() ||
            container->GetSlot(first_slot).GetItemDamage() != initial_second_slot_copy.GetItemDamage() ||
#else
            container->GetSlot(first_slot).GetItemID() != initial_second_slot_copy.GetItemID() ||
#endif
            container->GetSlot(first_slot).GetItemCount() != initial_second_slot_copy.GetItemCount())
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 10000)
            {
                std::cerr << "Something went wrong trying to swap inventory slots (Timeout)." << std::endl;
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        // Small delay to be sure the server set our new hotbar item as the current item
        // TODO : why doesn't the server registers it before the client has the confirmation?
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

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
        std::lock_guard<std::mutex> inventory_lock(inventory_manager->GetMutex());

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
