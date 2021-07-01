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
#include <array>

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

    void InterfaceClient::SetAutoRespawn(const bool b)
    {
        auto_respawn = b;
    }
	
	const void InterfaceClient::KillAuraBlock(const Position pos, const int delay)
	{
		if (!network_manager || network_manager->GetConnectionState() != ProtocolCraft::ConnectionState::Play)
        {
            return;
        }
		if (killaura_state == KillAuraState::Killing)
		{
			std::cout << "Launching multiple threads of killaura is not a geed practice" << std::endl;
		}
		
		std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
		auto ent = entity_manager->GetEntities();
		
		while (killaura_state != KillAuraState::Stop)
		{
			std::cout << "Checking entities" << std::endl;
			for(auto& ee : ent) {
				int id = ee.first;
				std::shared_ptr<Entity> e = ee.second;
				std::cout << e->GetEID() << " \tX: " << e->GetX() << " Y: " << e->GetY() << " Z: " << e->GetZ() << std::endl;
				if(std::floor(e->GetX()) == pos.x && std::floor(e->GetY()) == pos.y && std::floor(e->GetZ()) == pos.z) {
					std::shared_ptr<ServerboundInteractPacket> attack(new ServerboundInteractPacket);
					attack->SetEntityId(e->GetEID());
					attack->SetAction(1);
					attack->SetUsingSecondaryAction(false);
					network_manager->Send(attack);
					std::cout << "Attacked entity " << e->GetEID() << std::endl;
					continue;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}

    void InterfaceClient::StopKillAura()
    {
        if (killaura_state != KillAuraState::Waiting)
        {
            killaura_state = KillAuraState::Stop;
        }
    }

    const bool InterfaceClient::GoTo(const Position &goal, const bool in_range, const int min_end_dist, const float speed)
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

            bool is_goal_loaded;
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                is_goal_loaded = world->IsLoaded(goal);
            }

            if (!is_goal_loaded)
            {
                std::cout << "[" << network_manager->GetMyName() << "] Current goal position " << goal << " is either air or not loaded, trying to get closer to load the chunk" << std::endl;
                Vector3<double> goal_direction(goal.x - current_position.x, goal.y - current_position.y, goal.z - current_position.z);
                goal_direction.Normalize();
                path = FindPath(current_position, current_position + Position(goal_direction.x * 32, goal_direction.y * 32, goal_direction.z * 32), 0, true);
            }
            else
            {
                Position diff = goal - current_position;
                if (in_range && diff.dot(diff) <= 16.0f && std::abs(diff.x) + std::abs(diff.z) >= min_end_dist)
                {
                    pathfinding_state = PathFindingState::Waiting;
                    return true;
                }
                path = FindPath(current_position, goal, min_end_dist, true);
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
                    Position diff = goal - current_position;
                    return diff.dot(diff) <= 16.0f;
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

                const Vector3<double> initial_position = local_player->GetPosition();
                const Vector3<double> target_position(path[i].x + 0.5, path[i].y, path[i].z + 0.5);
                const Vector3<double> motion_vector = target_position - initial_position;
                local_player->LookAt(target_position);

                // If we have to jump to get to the next position
                if (path[i].y > current_position.y ||
                    std::abs(motion_vector.x) > 1.5 ||
                    std::abs(motion_vector.z) > 1.5)
                {
                    Jump();

                    if (std::abs(motion_vector.x) < 1.5 &&
                        std::abs(motion_vector.z) < 1.5)
                    {
                        auto now = std::chrono::system_clock::now();
                        bool has_timeout = false;
                        while (local_player->GetY() - initial_position.y < 1.0f)
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
                            break;
                        }
                    }
                }

                auto start = std::chrono::system_clock::now();
                auto previous_step = start;
                const double motion_norm_xz = std::abs(motion_vector.x) + std::abs(motion_vector.z);
                while (true)
                {
                    auto now = std::chrono::system_clock::now();
                    long long int time_count = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
                    // If we are over the time we have at speed to travel one block
                    if (time_count > 1000 * motion_norm_xz / speed)
                    {
                        {
                            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                            local_player->SetSpeedX(target_position.x - local_player->GetX());
                            local_player->SetY(local_player->GetY() + 0.001);
                            local_player->SetSpeedZ(target_position.z - local_player->GetZ());

                            // If the target motion requires going down
                            if (motion_vector.y < 0)
                            {
                                local_player->SetOnGround(false);
                            }
                        }
                        break;
                    }
                    // Otherwise just move partially toward the goal
                    else
                    {
                        long long int delta_t = std::chrono::duration_cast<std::chrono::milliseconds>(now - previous_step).count();
                        Vector3<double> delta_v = motion_vector * delta_t / (1000.0 * motion_norm_xz) * speed;
                        {
                            std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                            local_player->SetSpeedX(local_player->GetSpeed().x + delta_v.x);
                            local_player->SetY(local_player->GetY() + 0.001);
                            local_player->SetSpeedZ(local_player->GetSpeed().z + delta_v.z);
                        }
                        previous_step = now;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                // Wait for the confirmation that we arrived at the destination
                start = std::chrono::system_clock::now();
                bool has_timeout = false;
                while (true)
                {
                    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() >= 3000)
                    {
                        has_timeout = true;
                        break;
                    }

                    {
                        std::lock_guard<std::mutex> player_lock(local_player->GetMutex());
                        const Vector3<double> diff = local_player->GetPosition() - target_position;
                        if (std::abs(diff.x) + std::abs(diff.z) < 1e-2)
                        {
                            break;
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                // Wait until we are on the ground
                while (!local_player->GetOnGround())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                current_position = Position(std::floor(local_player->GetPosition().x), std::floor(local_player->GetPosition().y), std::floor(local_player->GetPosition().z));

                if (has_timeout)
                {
                    // Something went wrong during the movement,
                    // replanning the path is safer
                    break;
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

    const float Heuristic(const Position &a, const Position &b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
    }

    const std::vector<Position> InterfaceClient::FindPath(const Position &start, const Position &end, const int min_end_dist, const bool can_jump)
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

            if (count_visit > 10000 || 
                (std::abs(end.x - start.x) + std::abs(end.z - start.z) >= min_end_dist && current_node.pos == end) ||
                (std::abs(end.x - start.x) + std::abs(end.z - start.z) < min_end_dist) && (std::abs(end.x - current_node.pos.x) + std::abs(end.z - current_node.pos.z) >= min_end_dist))
            {
                break;
            }

            // For each neighbour, check if it's reachable
            // and add it to the search list if it is
            for (int i = 0; i < neighbour_offsets.size(); ++i)
            {
                const Position next_location = current_node.pos + neighbour_offsets[i];
                const Position next_next_location = next_location + neighbour_offsets[i];
                // Get the state around the player in the given location
                // True = solid, False = go through
                std::array<bool, 13> surroundings = { false, false, false, false, false, false,
                    false, false, false, false, false, false, false };
                // 0  1  7
                // x  2  8
                // x  3  9
                //--- 4  10
                //    5  11
                //    6  12
                bool is_in_fluid;
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());

                    const Block* block = world->GetBlock(current_node.pos);
                    is_in_fluid = block && block->GetBlockstate()->IsFluid();

                    // Start with 2 because if 2 is solid, no pathfinding is possible
                    block = world->GetBlock(next_location + Position(0, 1, 0));
                    surroundings[2] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    if (surroundings[2])
                    {
                        continue;
                    }

                    block = world->GetBlock(current_node.pos + Position(0, 2, 0));
                    surroundings[0] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));

                    block = world->GetBlock(next_location + Position(0, 2, 0));
                    surroundings[1] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location);
                    surroundings[3] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location + Position(0, -1, 0));
                    surroundings[4] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location + Position(0, -2, 0));
                    surroundings[5] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));
                    block = world->GetBlock(next_location + Position(0, -3, 0));
                    surroundings[6] = block && (block->GetBlockstate()->IsSolid() || (is_in_fluid && block->GetBlockstate()->IsFluid()));

                    // You can't make large jumps if your feet are in fluid
                    if (can_jump && !is_in_fluid)
                    {
                        block = world->GetBlock(next_next_location + Position(0, 2, 0));
                        surroundings[7] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, 1, 0));
                        surroundings[8] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location);
                        surroundings[9] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, -1, 0));
                        surroundings[10] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, -2, 0));
                        surroundings[11] = block && block->GetBlockstate()->IsSolid();
                        block = world->GetBlock(next_next_location + Position(0, -3, 0));
                        surroundings[12] = block && block->GetBlockstate()->IsSolid();
                    }
                }

                // We can check all cases that could allow the bot to pass
                //       ?
                // x     ?
                // x  o  ?
                //--- ?  ?
                //    ?  ?
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && surroundings[3])
                {
                    const float new_cost = cost[current_node.pos] + 2.0f;
                    const Position new_pos = next_location + Position(0, 1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ?
                // x     ?
                //--- o  ?
                //    ?  ?
                //    ?  ?
                if (!surroundings[2] && !surroundings[3]
                    && surroundings[4])
                {
                    const float new_cost = cost[current_node.pos] + 1.0f;
                    auto it = cost.find(next_location);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[next_location] = new_cost;
                        nodes_to_explore.emplace(PathNode(next_location, new_cost + Heuristic(next_location, end)));
                        came_from[next_location] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ? 
                // x     ?
                //---    ?
                //    o  ?
                //    ?  ?
                if (!surroundings[2] && !surroundings[3]
                    && !surroundings[4] && surroundings[5])
                {
                    const float new_cost = cost[current_node.pos] + 2.0f;
                    const Position new_pos = next_location + Position(0, -1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ?
                // x     ?
                //---    ?
                //       ?
                //    o  ?
                if (!surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && surroundings[6])
                {
                    const float new_cost = cost[current_node.pos] + 3.0f;
                    const Position new_pos = next_location + Position(0, -2, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                // ?  ?  ?
                // x     ?
                // x     ?
                //---    ?
                //       ?
                //       ?
                // Special case here, we can drop down
                // if there is some water at the bottom
                if (!surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[6])
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());

                    const Block* block;

                    for (int y = -4; next_location.y + y >= WORLD_START_Y; --y)
                    {
                        block = world->GetBlock(next_location + Position(0, y, 0));

                        if (block && block->GetBlockstate()->IsSolid())
                        {
                            break;
                        }

                        if (block && block->GetBlockstate()->IsFluid() 
                            && block->GetBlockstate()->GetName() == "minecraft:water")
                        {
                            const float new_cost = cost[current_node.pos] + std::abs(y);
                            const Position new_pos = next_location + Position(0, y + 1, 0);
                            auto it = cost.find(new_pos);
                            // If we don't already know this node with a better path, add it
                            if (it == cost.end() ||
                                new_cost < it->second)
                            {
                                cost[new_pos] = new_cost;
                                nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                                came_from[new_pos] = current_node.pos;
                            }

                            break;
                        }
                    }
                }

                if (!can_jump || is_in_fluid)
                {
                    continue;
                }

                //        
                // x      
                // x     o
                //---    ?
                //    ?  ?
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[7]
                    && !surroundings[8] && surroundings[9])
                {
                    const float new_cost = cost[current_node.pos] + 3.0f;
                    const Position new_pos = next_next_location + Position(0, 1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                //        
                // x      
                // x      
                //---    o
                //       ?
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[7] && !surroundings[8] 
                    && !surroundings[9] && surroundings[10])
                {
                    const float new_cost = cost[current_node.pos] + 3.0f;
                    auto it = cost.find(next_next_location);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[next_next_location] = new_cost;
                        nodes_to_explore.emplace(PathNode(next_next_location, new_cost + Heuristic(next_next_location, end)));
                        came_from[next_next_location] = current_node.pos;
                    }
                }

                //        
                // x      
                // x      
                //---     
                //       o
                //    ?  ?
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[7] && !surroundings[8]
                    && !surroundings[9] && !surroundings[10]
                    && surroundings[11])
                {
                    const float new_cost = cost[current_node.pos] + 4.0f;
                    const Position new_pos = next_next_location + Position(0, -1, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }

                //        
                // x      
                // x      
                //---     
                //        
                //    ?  o
                if (!surroundings[0] && !surroundings[1]
                    && !surroundings[2] && !surroundings[3]
                    && !surroundings[4] && !surroundings[5]
                    && !surroundings[7] && !surroundings[8] 
                    && !surroundings[9] && !surroundings[10]
                    && !surroundings[11] && surroundings[12])
                {
                    const float new_cost = cost[current_node.pos] + 5.0f;
                    const Position new_pos = next_next_location + Position(0, -2, 0);
                    auto it = cost.find(new_pos);
                    // If we don't already know this node with a better path, add it
                    if (it == cost.end() ||
                        new_cost < it->second)
                    {
                        cost[new_pos] = new_cost;
                        nodes_to_explore.emplace(PathNode(new_pos, new_cost + Heuristic(new_pos, end)));
                        came_from[new_pos] = current_node.pos;
                    }
                }
            } // neighbour loop
        }

        auto it_end_path = came_from.begin();

        // We search for the closest node
        // respecting the min_end_dist criterion
        float best_float_dist = std::numeric_limits<float>::max();
        for (auto it = came_from.begin(); it != came_from.end(); ++it)
        {
            const Position diff = it->first - end;
            const float distXZ = std::abs(diff.x) + std::abs(diff.z);
            const float d = std::abs(diff.y) + distXZ;
            if (d < best_float_dist && distXZ >= min_end_dist)
            {
                best_float_dist = d;
                it_end_path = it;
            }
        }

        std::deque<Position> output_deque;
        output_deque.push_front(it_end_path->first);
        while (it_end_path->second != start)
        {
            it_end_path = came_from.find(it_end_path->second);
            output_deque.push_front(it_end_path->first);
        }
        return std::vector<Position>(output_deque.begin(), output_deque.end());
    }

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
