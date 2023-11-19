#include "botcraft/Game/Physics/PhysicsManager.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/World/World.hpp"
#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

using namespace ProtocolCraft;

namespace Botcraft
{
    PhysicsManager::PhysicsManager(
#if USE_GUI
        const std::shared_ptr<Renderer::RenderingManager>& rendering_manager_,
#endif   
        const std::shared_ptr<InventoryManager>& inventory_manager_,
        const std::shared_ptr<LocalPlayer>& local_player_,
        const std::shared_ptr<NetworkManager>& network_manager_,
        const std::shared_ptr<World>& world_)
    {
#if USE_GUI
        rendering_manager = rendering_manager_;
#endif   
        inventory_manager = inventory_manager_;
        local_player = local_player_;
        network_manager = network_manager_;
        world = world_;

        should_run = false;
        allow_flying = false;
        game_mode = GameType::None;
        ticks_since_last_position_sent = 0;
    }

    PhysicsManager::~PhysicsManager()
    {
        StopPhysics();
    }

    void PhysicsManager::StartPhysics()
    {
        should_run = true;

        // Launch the physics thread (continuously sending the position to the server)
        thread_physics = std::thread(&PhysicsManager::Physics, this);
    }

    void PhysicsManager::StopPhysics()
    {
        should_run = false;
        if (thread_physics.joinable())
        {
            thread_physics.join();
        }
    }

    void PhysicsManager::Handle(ClientboundLoginPacket& msg)
    {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        game_mode = static_cast<GameType>(msg.GetGameType() & 0x03);
#else
        game_mode = static_cast<GameType>(msg.GetCommonPlayerSpawnInfo().GetGameType());
#endif
    }

    void PhysicsManager::Handle(ClientboundPlayerAbilitiesPacket& msg)
    {
        allow_flying = msg.GetFlags() & 0x04;
    }

    void PhysicsManager::Handle(ClientboundRespawnPacket& msg)
    {
#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        game_mode = static_cast<GameType>(msg.GetPlayerGameType());
#else
        game_mode = static_cast<GameType>(msg.GetCommonPlayerSpanwInfo().GetGameType());
#endif
    }


    void PhysicsManager::Physics()
    {
        Logger::GetInstance().RegisterThread("Physics");

        // Wait for 500 milliseconds before starting to send position continuously
        // TODO: wait for something better?
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        while (should_run)
        {
            // End of the current tick
            auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);

            if (network_manager->GetConnectionState() == ConnectionState::Play)
            {
                if (local_player != nullptr && !std::isnan(local_player->GetY()))
                {
                    const Vector3<double> player_position = local_player->GetPosition();
                    const Position player_int_position = Position(
                        static_cast<int>(std::floor(player_position.x)),
                        static_cast<int>(std::floor(player_position.y)),
                        static_cast<int>(std::floor(player_position.z))
                    );
                    const bool is_loaded = world->IsLoaded(player_int_position);

                    if (is_loaded)
                    {
                        {
                            // As PhysicsManager is a friend of LocalPlayer, we can lock the whole entity
                            // while physics is processed. This also means we can't use public interface
                            // as it's thread-safe by design and would deadlock because of this global lock
                            std::scoped_lock<std::shared_mutex> lock(local_player->entity_mutex);
                            // Do physics
                        }
                        // Send position
                        SendPosition();

                        // Copy current state in previous state
                        previous_state = current_state;
                    }
                }
            }
            // Wait for end of tick
            Utilities::SleepUntil(end);
        }
    }

    void PhysicsManager::SendPosition()
    {
        ticks_since_last_position_sent += 1;

        if (current_state.sprinting != previous_state.sprinting)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_msg = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_msg->SetAction(static_cast<int>(current_state.sprinting ? PlayerCommandAction::StartSprinting : PlayerCommandAction::StopSprinting));
            player_command_msg->SetId_(local_player->GetEntityID());
            network_manager->Send(player_command_msg);
        }

        if (current_state.inputs_sneak != previous_state.inputs_sneak)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_msg = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_msg->SetAction(static_cast<int>(current_state.inputs_sneak ? PlayerCommandAction::PressShiftKey : PlayerCommandAction::ReleaseShifKey));
            player_command_msg->SetId_(local_player->GetEntityID());
            network_manager->Send(player_command_msg);
        }

        // We should measure diff between last *sent* position and current one instead of previous tick one
        // but this leads to same results (unless movement at each tick is < 2e-4, but who cares)
        const Vector3<double> diff_pos = current_state.position - previous_state.position;
        const bool has_moved = diff_pos.SqrNorm() > 4e-8 || ticks_since_last_position_sent >= 20;
        const bool has_rotated = current_state.yaw != previous_state.yaw || current_state.pitch != previous_state.pitch;
        if (has_moved && has_rotated)
        {
            std::shared_ptr<ServerboundMovePlayerPacketPosRot> move_player_msg = std::make_shared<ServerboundMovePlayerPacketPosRot>();
            move_player_msg->SetX(current_state.position.x);
            move_player_msg->SetY(current_state.position.y);
            move_player_msg->SetZ(current_state.position.z);
            move_player_msg->SetXRot(current_state.pitch);
            move_player_msg->SetYRot(current_state.yaw);
            move_player_msg->SetOnGround(current_state.on_ground);
            network_manager->Send(move_player_msg);
        }
        else if (has_moved)
        {
            std::shared_ptr<ServerboundMovePlayerPacketPos> move_player_msg = std::make_shared<ServerboundMovePlayerPacketPos>();
            move_player_msg->SetX(current_state.position.x);
            move_player_msg->SetY(current_state.position.y);
            move_player_msg->SetZ(current_state.position.z);
            move_player_msg->SetOnGround(current_state.on_ground);
            network_manager->Send(move_player_msg);
        }
        else if (has_rotated)
        {
            std::shared_ptr<ServerboundMovePlayerPacketRot> move_player_msg = std::make_shared<ServerboundMovePlayerPacketRot>();
            move_player_msg->SetXRot(current_state.pitch);
            move_player_msg->SetYRot(current_state.yaw);
            move_player_msg->SetOnGround(current_state.on_ground);
            network_manager->Send(move_player_msg);
        }
        else if (current_state.on_ground != previous_state.on_ground)
        {
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            std::shared_ptr<ServerboundMovePlayerPacketStatusOnly> move_player_msg = std::make_shared<ServerboundMovePlayerPacketStatusOnly>();
#else
            std::shared_ptr<ServerboundMovePlayerPacket> move_player_msg = std::make_shared<ServerboundMovePlayerPacket>();
#endif
            move_player_msg->SetOnGround(current_state.on_ground);
            network_manager->Send(move_player_msg);
        }

        if (has_moved)
        {
            ticks_since_last_position_sent = 0;
        }

#if USE_GUI
        if (rendering_manager != nullptr && (has_moved || has_rotated))
        {
            rendering_manager->SetPosOrientation(
                current_state.position.x,
                current_state.position.y + local_player->GetEyeHeight(),
                current_state.position.z,
                current_state.yaw,
                current_state.pitch
            );
        }
#endif
    }
} //Botcraft
