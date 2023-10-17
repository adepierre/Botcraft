#include "botcraft/Game/Physics/PhysicsManager.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
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
        const std::shared_ptr<EntityManager>& entity_manager_,
        const std::shared_ptr<World>& world_,
        const std::shared_ptr<NetworkManager>& network_manager_)
    {
#if USE_GUI
        rendering_manager = rendering_manager_;
#endif   
        entity_manager = entity_manager_;
        world = world_;
        network_manager = network_manager_;
    }

    PhysicsManager::~PhysicsManager()
    {
        StopPhysics();
    }

    void PhysicsManager::StartPhysics()
    {
        should_run = true;

        // Launch the physics thread (continuously sending the position to the server)
        thread_physics = std::thread(&PhysicsManager::RunSyncPos, this);
    }

    void PhysicsManager::StopPhysics()
    {
        should_run = false;
        if (thread_physics.joinable())
        {
            thread_physics.join();
        }
    }

    void PhysicsManager::SetHasGravity(const bool b)
    {
        has_gravity = b;
    }

    bool PhysicsManager::GetHasGravity() const
    {
        return has_gravity;
    }



    void PhysicsManager::RunSyncPos()
    {
        Logger::GetInstance().RegisterThread("RunSyncPos");

        // Wait for 500 milliseconds before starting to send position continuously
        // TODO: wait for something better?
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        auto last_send = std::chrono::steady_clock::now();
        std::shared_ptr<ServerboundMovePlayerPacketPosRot> msg_position = std::make_shared<ServerboundMovePlayerPacketPosRot>();
        bool has_moved = false;

        while (should_run)
        {
            // End of the current tick
            auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);

            if (network_manager->GetConnectionState() == ProtocolCraft::ConnectionState::Play)
            {
                std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
                if (local_player != nullptr && local_player->GetY() < 1000.0)
                {
                    // As PhysicsManager is a friend of LocalPlayer, we can lock the whole entity
                    // while physics is processed. This also means we can't use public interface
                    // as it's thread-safe by design and would deadlock because of this global lock
                    std::scoped_lock<std::shared_mutex> lock(local_player->entity_mutex);

                    const Position player_position = Position(
                        static_cast<int>(std::floor(local_player->position.x)),
                        static_cast<int>(std::floor(local_player->position.y)),
                        static_cast<int>(std::floor(local_player->position.z))
                    );

                    const bool is_loaded = world->IsLoaded(player_position);

                    if (is_loaded)
                    {
                        //Check that we did not go through a block
                        Physics();

                        if (local_player->has_moved ||
                            std::abs(local_player->speed.x) > 1e-3 ||
                            std::abs(local_player->speed.y) > 1e-3 ||
                            std::abs(local_player->speed.z) > 1e-3)
                        {
                            has_moved = true;
                            // Reset the player move state until next tick
                            local_player->has_moved = false;
                        }
                        else
                        {
                            has_moved = false;
                        }

                        //Avoid forever falling if position is in the void
                        if (!has_gravity && local_player->position.y <= world->GetMinY())
                        {
                            local_player->position.y = world->GetMinY();
                            local_player->speed.y = 0.0;
                            local_player->on_ground = true;
                        }

                        UpdatePlayerSpeed();
                    }

#if USE_GUI
                    if (rendering_manager && has_moved)
                    {
                        rendering_manager->SetPosOrientation(local_player->position.x, local_player->position.y + 1.62, local_player->position.z, local_player->yaw, local_player->pitch);
                    }
#endif
                    if (has_moved || std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_send).count() >= 1000)
                    {
                        msg_position->SetX(local_player->position.x);
                        msg_position->SetY(local_player->position.y);
                        msg_position->SetZ(local_player->position.z);
                        msg_position->SetYRot(local_player->yaw);
                        msg_position->SetXRot(local_player->pitch);
                        msg_position->SetOnGround(local_player->on_ground);

                        network_manager->Send(msg_position);
                        last_send = std::chrono::steady_clock::now();
                    }
                }
            }
            Utilities::SleepUntil(end);
        }
    }

    void PhysicsManager::Physics()
    {
        if (!entity_manager)
        {
            return;
        }

        // Player mutex is already locked by calling function
        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

        // Copy speed
        Vector3<double> player_movement_speed = local_player->speed;
        // Add negative epsilon speed to still trigger collisions and get on_ground correctly
        if (player_movement_speed.y == 0.0)
        {
            player_movement_speed.y -= 1e-7;
        }
        // Copy player inputs
        Vector3<double> player_movement_inputs = local_player->player_inputs;

        const AABB player_collider = AABB(
            Vector3<double>(local_player->position.x, local_player->position.y + local_player->GetHeight() / 2, local_player->position.z),
            Vector3<double>(local_player->GetWidth() / 2, local_player->GetHeight() / 2, local_player->GetWidth() / 2)
        );

        // If gravity applies, you can't decide to go up with player inputs
        // (jump is applied to speed not inputs)
        bool has_pass_through;
        if (!local_player->is_climbing)
        {
            player_movement_inputs.y = std::min(player_movement_inputs.y, 0.0);
            has_pass_through = false;
        }
        else
        {
            has_pass_through = true;
        }

        Vector3<double> min_player_collider, max_player_collider;
        for (int i = 0; i < 3; ++i)
        {
            min_player_collider[i] = std::min(player_collider.GetMin()[i], player_collider.GetMin()[i] + player_movement_speed[i] + player_movement_inputs[i]);
            max_player_collider[i] = std::max(player_collider.GetMax()[i], player_collider.GetMax()[i] + player_movement_speed[i] + player_movement_inputs[i]);
        }

        AABB broadphase_collider = AABB((min_player_collider + max_player_collider) / 2.0, (max_player_collider - min_player_collider) / 2.0);

        bool has_hit_down = false;
        bool has_hit_up = false;

        Position cube_pos;
        for (int x = static_cast<int>(std::floor(min_player_collider.x)); x < static_cast<int>(std::ceil(max_player_collider.x)); ++x)
        {
            cube_pos.x = x;
            for (int y = static_cast<int>(std::floor(min_player_collider.y)); y < static_cast<int>(std::ceil(max_player_collider.y)); ++y)
            {
                cube_pos.y = y;
                for (int z = static_cast<int>(std::floor(min_player_collider.z)); z < static_cast<int>(std::ceil(max_player_collider.z)); ++z)
                {
                    cube_pos.z = z;

                    const Blockstate* block= world->GetBlock(cube_pos);

                    if (block == nullptr)
                    {
                        continue;
                    }

                    // If the block is not solid and it's not a climbable block below us,
                    // it doesn't collide so ignore it
                    if (!block->IsSolid()
                        && (!block->IsClimbable() || cube_pos.y >= std::floor(local_player->position.y)))
                    {
                        continue;
                    }

                    const std::set<AABB>& block_colliders = block->GetModel(block->GetModelId(cube_pos)).GetColliders();

                    for (const auto& collider : block_colliders)
                    {
                        const AABB shifted_collider = collider + Vector3<double>(cube_pos.x, cube_pos.y, cube_pos.z);
                        if (!broadphase_collider.Collide(shifted_collider))
                        {
                            continue;
                        }

                        Vector3<double> normal;
                        const double speed_fraction = player_collider.SweptCollide(player_movement_speed + player_movement_inputs, shifted_collider, normal);

                        // If we collide with the bottom block with go down user input
                        // and it's a climbable block, then we should pass through
                        const bool pass_through = normal.y == 1.0
                            && block->IsClimbable()
                            && local_player->player_inputs.y < 0;

                        // If we collide with the bottom block and we shouldn't pass through
                        if (speed_fraction < 1.0 && !pass_through) 
                        {
                            const Vector3<double> remaining_speed = player_movement_speed * (1.0 - speed_fraction);
                            const Vector3<double> remaining_inputs = player_movement_inputs * (1.0 - speed_fraction);

                            // We remove epsilon to be sure we do not go
                            // through the face due to numerical imprecision
                            player_movement_speed = player_movement_speed * (speed_fraction - 1e-6) + // Base speed truncated
                                (remaining_speed - normal * remaining_speed.dot(normal)); // Remaining speed projected on the plane
                            player_movement_inputs = player_movement_inputs * (speed_fraction - 1e-6) + // Base speed truncated
                                (remaining_inputs - normal * remaining_inputs.dot(normal)); // Remaining speed projected on the plane

                        }
                        // If we collide with the bottom block and should pass through,
                        // only remove the y component of the speed that makes going
                        // through the block
                        else if (speed_fraction < 1.0 && pass_through)
                        {
                            const double block_top_y = shifted_collider.GetMax().y;
                            player_movement_speed.y = std::max(player_movement_speed.y, block_top_y - local_player->position.y);
                        }

                        if (pass_through)
                        {
                            has_pass_through = true;
                        }
                        if (normal.y == 1.0 && !pass_through)
                        {
                            has_hit_down = true;
                        }
                        else if (normal.y == -1.0)
                        {
                            has_hit_up = true;
                        }
                    }
                }
            }
        }

        // if we didn't went through a block, ignore down player input
        if (!has_pass_through)
        {
            player_movement_inputs.y = std::max(0.0, player_movement_inputs.y);
        }

        local_player->position += player_movement_speed + player_movement_inputs;
        local_player->on_ground = has_hit_down;
        // Update climbing state
        const Blockstate* block = world->GetBlock(Position(
            static_cast<int>(std::floor(local_player->position.x)),
            static_cast<int>(std::floor(local_player->position.y)),
            static_cast<int>(std::floor(local_player->position.z)))
        );
        local_player->is_climbing = block != nullptr && block->IsClimbable();

        if (has_hit_up)
        {
            local_player->speed.y = 0.0;
        }
    }

    void PhysicsManager::UpdatePlayerSpeed() const
    {
        // Player mutex is already locked by calling function
        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

        // If currently climbing, then no gravity and just remove Y speed
        local_player->speed = Vector3<double>(
            local_player->speed.x * 0.91,
            (local_player->is_climbing || !has_gravity) ? 0.0 : (local_player->speed.y - 0.08) * 0.98,
            local_player->speed.z * 0.91
        );

        if (local_player->on_ground)
        {
            const Vector3<double> ground_drag(0.6, 0.0, 0.6);
            // TODO: adapt drag depending on blocks (slime, ice)
            local_player->speed *= ground_drag;
        }

        if (std::abs(local_player->speed.x) < 0.003)
        {
            local_player->speed.x = 0.0;
        }
        if (std::abs(local_player->speed.z) < 0.003)
        {
            local_player->speed.z = 0.0;
        }

        // Reset player inputs
        local_player->player_inputs = Vector3<double>(0.0);
    }

} //Botcraft
