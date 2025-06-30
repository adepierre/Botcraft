#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Physics/PhysicsManager.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"
#include "botcraft/Utilities/ItemUtilities.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/entities/projectile/FireworkRocketEntity.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Item.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
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
        const std::shared_ptr<EntityManager>& entity_manager_,
        const std::shared_ptr<NetworkManager>& network_manager_,
        const std::shared_ptr<World>& world_)
    {
#if USE_GUI
        rendering_manager = rendering_manager_;
#endif
        inventory_manager = inventory_manager_;
        entity_manager = entity_manager_;
        player = nullptr;
        network_manager = network_manager_;
        world = world_;

        should_run = false;
        teleport_id = std::nullopt;
        ticks_since_last_position_sent = 0;
        double_tap_cause_sprint = true;

        elytra_item = AssetsManager::getInstance().GetItem("minecraft:elytra");
        if (elytra_item == nullptr)
        {
            throw std::runtime_error("Unknown item minecraft:elytra");
        }
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

    void PhysicsManager::SetDoubleTapCauseSprint(const bool b)
    {
        double_tap_cause_sprint = b;
        // Reset sprint_double_tap_trigger_time to 0 if b is false
        if (player != nullptr)
        {
            std::scoped_lock<std::shared_mutex> lock(player->entity_mutex);
            player->sprint_double_tap_trigger_time *= b;
        }
    }

    double PhysicsManager::GetMsPerTick() const
    {
        return ms_per_tick;
    }


    void PhysicsManager::Handle(ClientboundLoginPacket& packet)
    {
        // Reset the player because *some* non vanilla servers
        // sends new login packets
        if (player != nullptr)
        {
            // If we already have a player, we need to make sure we're not in the middle
            // of a physics update while swapping the player with the new one
            std::scoped_lock<std::shared_mutex> lock(player->entity_mutex);
            player = entity_manager->GetLocalPlayer();
        }
        else
        {
            player = entity_manager->GetLocalPlayer();
        }
    }

    void PhysicsManager::Handle(ClientboundPlayerPositionPacket& packet)
    {
        if (player == nullptr)
        {
            LOG_WARNING("Received a PlayerPosition packet without a player");
            return;
        }

        std::scoped_lock<std::shared_mutex> lock(player->entity_mutex);
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        if (packet.GetRelativeArguments() & 0x01)
        {
            player->position.x = player->position.x + packet.GetX();
        }
        else
        {
            player->position.x = packet.GetX();
            player->speed.x = 0.0;
        }
        if (packet.GetRelativeArguments() & 0x02)
        {
            player->position.y = player->position.y + packet.GetY();
        }
        else
        {
            player->position.y = packet.GetY();
            player->speed.y = 0.0;
        }
        if (packet.GetRelativeArguments() & 0x04)
        {
            player->position.z = player->position.z + packet.GetZ();
        }
        else
        {
            player->position.z = packet.GetZ();
            player->speed.z = 0.0;
        }
        player->yaw = packet.GetRelativeArguments() & 0x08 ? player->yaw + packet.GetYRot() : packet.GetYRot();
        player->pitch = packet.GetRelativeArguments() & 0x10 ? player->pitch + packet.GetXRot() : packet.GetXRot();

        player->previous_position = player->position;
        player->previous_yaw = player->yaw;
        player->previous_pitch = player->pitch;
#else
        for (int i = 0; i < 3; ++i)
        {
            player->position[i] = packet.GetRelatives() & (1 << i) ? player->position[i] + packet.GetChange().GetPosition()[i] : packet.GetChange().GetPosition()[i];
        }
        const float new_yaw = packet.GetRelatives() & (1 << 3) ? player->yaw + packet.GetChange().GetYRot() : packet.GetChange().GetYRot();
        const float new_pitch = packet.GetRelatives() & (1 << 4) ? player->pitch + packet.GetChange().GetXRot() : packet.GetChange().GetXRot();
        Vector3<double> speed = player->speed;
        if (packet.GetRelatives() & (1 << 8)) // Rotate delta, not sure what it's for...
        {
            const float delta_yaw = player->yaw - new_yaw;
            const float delta_pitch = player->pitch - new_pitch;
            // xRot
            speed = Vector3<double>(
                speed.x,
                speed.y * static_cast<double>(std::cos(delta_pitch * 0.017453292f /* PI/180 */)) + speed.z * static_cast<double>(std::sin(delta_pitch * 0.017453292f /* PI/180 */)),
                speed.z * static_cast<double>(std::cos(delta_pitch * 0.017453292f /* PI/180 */)) - speed.y * static_cast<double>(std::sin(delta_pitch * 0.017453292f /* PI/180 */))
            );
            // yRot
            speed = Vector3<double>(
                speed.x * static_cast<double>(std::cos(delta_yaw * 0.017453292f /* PI/180 */)) + speed.z * static_cast<double>(std::sin(delta_yaw * 0.017453292f /* PI/180 */)),
                speed.y,
                speed.z * static_cast<double>(std::cos(delta_yaw * 0.017453292f /* PI/180 */)) - speed.x * static_cast<double>(std::sin(delta_yaw * 0.017453292f /* PI/180 */))
            );
        }
        player->yaw = new_yaw;
        player->pitch = new_pitch;
        for (int i = 0; i < 3; ++i)
        {
            player->speed[i] = packet.GetRelatives() & (1 << (5 + i)) ? speed[i] + packet.GetChange().GetDeltaMovement()[i] : packet.GetChange().GetDeltaMovement()[i];
        }
        for (int i = 0; i < 3; ++i)
        {
            player->previous_position[i] = packet.GetRelatives() & (1 << i) ? player->previous_position[i] + packet.GetChange().GetPosition()[i] : packet.GetChange().GetPosition()[i];
        }
        player->previous_yaw = packet.GetRelatives() & (1 << 3) ? player->yaw + packet.GetChange().GetYRot() : packet.GetChange().GetYRot();
        player->previous_pitch = packet.GetRelatives() & (1 << 4) ? player->pitch + packet.GetChange().GetXRot() : packet.GetChange().GetXRot();
#endif
        player->UpdateVectors();

        // Defer sending the position update to the next physics tick
        // Sending it now causes huge slow down of the tests (lag when
        // botcraft_0 is teleported to place structure block/signs).
        // I'm not sure what causes this behaviour (server side?)
        teleport_id = packet.GetId_();
    }

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
    void PhysicsManager::Handle(ClientboundTickingStatePacket& packet)
    {
        // If the game is frozen, physics run normally for players
        if (packet.GetIsFrozen())
        {
            ms_per_tick = 50.0;
            return;
        }

        // Vanilla behaviour: slowed down but never speed up, even if tick rate is > 20/s
        // TODO: add a parameter to allow non-vanilla client speed up for higher tick rates?
        ms_per_tick = std::max(50.0, 1000.0 / static_cast<double>(packet.GetTickRate()));
    }
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
    void PhysicsManager::Handle(ClientboundPlayerRotationPacket& packet)
    {
        if (player == nullptr)
        {
            LOG_WARNING("Received a PlayerRotation packet without a player");
            return;
        }

        std::scoped_lock<std::shared_mutex> lock(player->entity_mutex);
        player->yaw = packet.GetYRot();
        player->pitch = packet.GetXRot();
        player->previous_yaw = player->yaw;
        player->previous_pitch = player->pitch;
    }
#endif

    void PhysicsManager::Physics()
    {
        Logger::GetInstance().RegisterThread("Physics - " + network_manager->GetMyName());

        while (should_run)
        {
            auto end = std::chrono::steady_clock::now();
            // End of the current tick
            end += std::chrono::microseconds(static_cast<long long int>(1000.0 * ms_per_tick));

            if (network_manager->GetConnectionState() == ConnectionState::Play)
            {
                if (player != nullptr && !std::isnan(player->GetY()))
                {
                    // As PhysicsManager is a friend of LocalPlayer, we can lock the whole entity
                    // while physics is processed. This also means we can't use public interface
                    // as it's thread-safe by design and would deadlock because of this global lock
                    std::scoped_lock<std::shared_mutex> lock(player->entity_mutex);

                    // Send player updated position with onground set to false to mimic vanilla client behaviour
                    if (teleport_id.has_value())
                    {
                        std::shared_ptr<ServerboundMovePlayerPacketPosRot> updated_position_packet = std::make_shared<ServerboundMovePlayerPacketPosRot>();
                        updated_position_packet->SetX(player->position.x);
                        updated_position_packet->SetY(player->position.y);
                        updated_position_packet->SetZ(player->position.z);
                        updated_position_packet->SetYRot(player->yaw);
                        updated_position_packet->SetXRot(player->pitch);
                        updated_position_packet->SetOnGround(false);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
                        updated_position_packet->SetHorizontalCollision(false);
#endif

                        std::shared_ptr<ServerboundAcceptTeleportationPacket> accept_tp_packet = std::make_shared<ServerboundAcceptTeleportationPacket>();
                        accept_tp_packet->SetId_(teleport_id.value());

                        // Before 1.21.2 -> Accept TP then move player, 1.21.2+ -> move player then accept TP
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
                        network_manager->Send(accept_tp_packet);
                        network_manager->Send(updated_position_packet);
#else
                        network_manager->Send(updated_position_packet);
                        network_manager->Send(accept_tp_packet);
#endif
                        teleport_id = std::nullopt;
                    }
                    PhysicsTick();
                }
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
                std::shared_ptr<ServerboundClientTickEndPacket> tick_end_packet = std::make_shared<ServerboundClientTickEndPacket>();
                network_manager->Send(tick_end_packet);
#endif
            }
            // Wait for end of tick
            Utilities::SleepUntil(end);
        }
    }

    void PhysicsManager::PhysicsTick()
    {
        // Check for rocket boosting if currently in elytra flying mode
        if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying))
        {
            for (const auto& e : *entity_manager->GetEntities())
            {
                if (e.second->GetType() != EntityType::FireworkRocketEntity)
                {
                    continue;
                }

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
                const int attached_id = reinterpret_cast<const FireworkRocketEntity*>(e.second.get())->GetDataAttachedToTarget().value_or(0);
#else
                const int attached_id = reinterpret_cast<const FireworkRocketEntity*>(e.second.get())->GetDataAttachedToTarget();
#endif
                if (attached_id == player->entity_id)
                {
                    player->speed += player->front_vector * 0.1 + (player->front_vector * 1.5 - player->speed) * 0.5;
                }
            }
        }

        { // LocalPlayer::tick
            // The idea here is to follow the tick flow from LocalPlayer::tick
            // in Minecraft code
            // This is neither the most efficient way nor the simplest one.
            // But hopefully it will be easier to compare to original code
            // and update when changed on Minecraft side.
            if (world->IsLoaded(Position(
                static_cast<int>(std::floor(player->position.x)),
                static_cast<int>(std::floor(player->position.y)),
                static_cast<int>(std::floor(player->position.z))
            )))
            { // Player::tick
                if (player->game_mode == GameType::Spectator)
                {
                    player->on_ground = false;
                }

                { // Entity::baseTick
                    FluidPhysics(true);
                    FluidPhysics(false);

                    UpdateSwimming(); // Player::updateSwimming
                } // Entity::baseTick

                { // LocalPlayer::aiStep
                    player->sprint_double_tap_trigger_time = std::max(0, player->sprint_double_tap_trigger_time - 1);

                    InputsToCrouch();

                    // TODO: if game_mode != GameType::Spectator, move towards closest free space if inside block

                    InputsToSprint();

                    InputsToFly();

                    // If sneaking in water, add downward speed
                    if (player->in_water && player->inputs.sneak && !player->flying)
                    {
                        player->speed.y -= 0.03999999910593033;
                    }

                    // If flying in spectator/creative, go up/down if sneak/jump
                    if (player->flying)
                    {
                        player->speed.y += (-1 * player->inputs.sneak + player->inputs.jump) * player->flying_speed * 3.0f;
                    }

                    { // Player::aiStep
                        player->fly_jump_trigger_time = std::max(0, player->fly_jump_trigger_time - 1);
                    }

                    // Update previous values
                    player->previous_forward = player->inputs.forward_axis;
                    player->previous_jump = player->inputs.jump;
                    player->previous_sneak = player->inputs.sneak;

                    { // LivingEntity::aiStep
                        // Decrease jump delay if > 0
                        player->jump_delay = std::max(0, player->jump_delay - 1);

                        if (std::abs(player->speed.x) < 0.003)
                        {
                            player->speed.x = 0.0;
                        }
                        if (std::abs(player->speed.y) < 0.003)
                        {
                            player->speed.y = 0.0;
                        }
                        if (std::abs(player->speed.z) < 0.003)
                        {
                            player->speed.z = 0.0;
                        }

                        InputsToJump();

                        player->inputs.forward_axis *= 0.98f;
                        player->inputs.left_axis *= 0.98f;

                        // Compensate water downward speed depending on looking direction (?)
                        if (IsSwimmingAndNotFlying())
                        {
                            const double m_sin_pitch = player->front_vector.y;
                            bool condition = m_sin_pitch <= 0.0 || player->inputs.jump;
                            if (!condition)
                            {
                                const Blockstate* above_block = world->GetBlock(Position(
                                    static_cast<int>(std::floor(player->position.x)),
                                    static_cast<int>(std::floor(player->position.y + 1.0 - 0.1)),
                                    static_cast<int>(std::floor(player->position.z))
                                ));
                                condition = above_block != nullptr && above_block->IsFluid();
                            }
                            if (condition)
                            {
                                player->speed.y += (m_sin_pitch - player->speed.y) * (m_sin_pitch < -0.2 ? 0.085 : 0.06);
                            }
                        }

                        const double speed_y = player->speed.y;
                        MovePlayer();
                        if (player->flying)
                        {
                            player->speed.y = 0.6 * speed_y;
                            player->SetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying, false);
                        }

                        // Minecraft code doesn't store on_climbable and check everytime it's needed instead,
                        // but it's more convenient for pathfinding to have it stored
                        player->on_climbable = IsInClimbable();

                        // TODO: pushed by other entities

                    } // LivingEntity::aiStep

                    // Stop flying in creative when touching ground
                    if (player->on_ground && player->flying && player->game_mode != GameType::Spectator)
                    {
                        player->flying = false;
                        OnUpdateAbilities();
                    }
                } // LocalPlayer::aiStep

                player->position.x = std::clamp(player->position.x, -2.9999999E7, 2.9999999E7);
                player->position.z = std::clamp(player->position.z, -2.9999999E7, 2.9999999E7);

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
                if (world->IsFree(player->GetColliderImpl(Pose::Swimming).Inflate(-1e-7), false))
                { // Player::UpdatePlayerPose
                    Pose current_pose;
                    if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying))
                    {
                        current_pose = Pose::FallFlying;
                    }
                    else if (player->GetSleepingPosIdImpl())
                    {
                        current_pose = Pose::Sleeping;
                    }
                    else if (IsSwimmingAndNotFlying())
                    {
                        current_pose = Pose::Swimming;
                    }
                    else if (player->GetDataLivingEntityFlagsImpl() & 0x04)
                    {
                        current_pose = Pose::SpinAttack;
                    }
                    else if (player->inputs.sneak && !player->flying)
                    {
                        current_pose = Pose::Crouching;
                    }
                    else
                    {
                        current_pose = Pose::Standing;
                    }

                    if (player->game_mode == GameType::Spectator || world->IsFree(player->GetColliderImpl(current_pose).Inflate(-1e-7), false))
                    {
                        player->SetDataPoseImpl(current_pose);
                    }
                    else if (world->IsFree(player->GetColliderImpl(Pose::Crouching).Inflate(-1e-7), false))
                    {
                        player->SetDataPoseImpl(Pose::Crouching);
                    }
                    else
                    {
                        player->SetDataPoseImpl(Pose::Swimming);
                    }
                }
#endif
            } // Player::tick

            SendPosition();
        }  // LocalPlayer::tick

        player->ResetInputs();
    }

    void PhysicsManager::UpdateSwimming() const
    {
        if (player->flying)
        {
            player->SetDataSharedFlagsIdImpl(EntitySharedFlagsId::Swimming, false);
        }
        else if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Swimming))
        {
            player->SetDataSharedFlagsIdImpl(
                EntitySharedFlagsId::Swimming,
                player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) && player->in_water
            );
        }
        else
        {
            const Blockstate* block = world->GetBlock(Position(
                static_cast<int>(std::floor(player->position.x)),
                static_cast<int>(std::floor(player->position.y)),
                static_cast<int>(std::floor(player->position.z))
            ));
            player->SetDataSharedFlagsIdImpl(
                EntitySharedFlagsId::Swimming,
                player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) &&
                player->under_water &&
                block != nullptr &&
                block->IsWater()
            );
        }
    }

    void PhysicsManager::FluidPhysics(const bool water)
    { // Entity::updateFluidHeightAndDoFluidPushing
        const AABB aabb = player->GetColliderImpl().Inflate(-0.001);

        if (water)
        {
            player->in_water = false;
            player->under_water = false;
        }
        else
        {
            player->in_lava = false;
        }

        const Vector3<double> min_aabb = aabb.GetMin();
        const Vector3<double> max_aabb = aabb.GetMax();
        const double eye_height = player->position.y + player->GetEyeHeightImpl();

        Vector3<double> push(0.0, 0.0, 0.0);
        Position block_pos;
        double fluid_relative_height = 0.0;
        int num_push = 0;

        for (int x = static_cast<int>(std::floor(min_aabb.x)); x <= static_cast<int>(std::floor(max_aabb.x)); ++x)
        {
            block_pos.x = x;
            for (int y = static_cast<int>(std::floor(min_aabb.y)); y <= static_cast<int>(std::floor(max_aabb.y)); ++y)
            {
                block_pos.y = y;
                for (int z = static_cast<int>(std::floor(min_aabb.z)); z <= static_cast<int>(std::floor(max_aabb.z)); ++z)
                {
                    block_pos.z = z;
                    const Blockstate* block = world->GetBlock(block_pos);
                    if (block == nullptr || !block->IsFluid() ||
                        (block->IsLava() && water) || (block->IsWater() && !water))
                    {
                        continue;
                    }

                    double fluid_height = 0.0;
                    if (const Blockstate* block_above = world->GetBlock(block_pos + Position(0, 1, 0)); block_above != nullptr &&
                        ((block_above->IsLava() && block->IsLava()) || (block_above->IsWater() && block->IsWater())))
                    {
                        fluid_height = 1.0;
                    }
                    else
                    {
                        fluid_height = block->GetFluidHeight();
                    }

                    if (fluid_height + y < min_aabb.y)
                    {
                        continue;
                    }

                    if (water)
                    {
                        player->in_water = true;
                        if (fluid_height + y >= eye_height)
                        {
                            player->under_water = true;
                        }
                    }
                    else
                    {
                        player->in_lava = true;
                    }

                    fluid_relative_height = std::max(fluid_height - min_aabb.y, fluid_relative_height);

                    if (player->flying)
                    {
                        continue;
                    }

                    Vector3<double> current_push = world->GetFlow(block_pos);
                    if (fluid_relative_height < 0.4)
                    {
                        current_push *= fluid_relative_height;
                    }
                    push += current_push;
                    num_push += 1;
                }
            }
        }

        if (push.SqrNorm() > 0.0)
        {
            if (num_push > 0) // this should always be true but just in case
            {
                push /= static_cast<double>(num_push);
            }
            if (water)
            {
                push *= 0.014;
            }
            else
            {
                push *= world->IsInUltraWarmDimension() ? 0.007 : 0.0023333333333333335;
            }
            const double push_norm = std::sqrt(push.SqrNorm());
            if (std::abs(player->speed.x) < 0.003 && std::abs(player->speed.z) < 0.003 && push_norm < 0.0045000000000000005)
            {
                // Normalize and scale
                push /= push_norm;
                push *= 0.0045000000000000005;
            }
            player->speed += push;
        }
    }

    void PhysicsManager::InputsToCrouch() const
    {
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        player->crouching =
            !IsSwimmingAndNotFlying() &&
            world->IsFree(player->GetColliderImpl(Pose::Crouching).Inflate(-1e-7), false) &&
            (player->previous_sneak || !world->IsFree(player->GetColliderImpl(Pose::Standing).Inflate(-1e-7), false));
#else
        player->crouching = !IsSwimmingAndNotFlying() && player->previous_sneak;
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        const bool is_moving_slowly = player->crouching || (player->GetDataPoseImpl() == Pose::Swimming && !player->in_water);
#else
        const bool is_moving_slowly = player->crouching;
#endif

#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
        bool has_blindness = false;
        for (const auto& effect : player->effects)
        {
            if (effect.type == EntityEffectType::Blindness && effect.end > std::chrono::steady_clock::now())
            {
                has_blindness = true;
                break;
            }
        }

        // Stop sprinting when crouching fix in 1.21.4+
        if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying) ||
            has_blindness ||
            is_moving_slowly)
        {
            SetSprinting(false);
        }
#endif

        // If crouch, slow down player inputs
        if (is_moving_slowly)
        {
#if PROTOCOL_VERSION < 759 /* < 1.19 */
            constexpr float sneak_coefficient = 0.3f;
#elif PROTOCOL_VERSION < 767 /* < 1.21 */
            float sneak_coefficient = 0.3f;
            // Get SneakSpeed bonus from pants
            const Slot leggings_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_LEGS_ARMOR);
            sneak_coefficient += Utilities::GetEnchantmentLvl(leggings_armor, Enchantment::SwiftSneak) * 0.15f;
            sneak_coefficient = std::min(std::max(0.0f, sneak_coefficient), 1.0f);
#else
            const float sneak_coefficient = static_cast<float>(player->GetAttributePlayerSneakingSpeedValueImpl());
#endif
            player->inputs.forward_axis *= sneak_coefficient;
            player->inputs.left_axis *= sneak_coefficient;
        }
    }

    void PhysicsManager::InputsToSprint() const
    {
        const bool was_sneaking = player->previous_sneak;
        const bool had_enough_impulse_to_start_sprinting = player->previous_forward >= (player->under_water ? 1e-5f : 0.8f);
        const bool has_enough_impulse_to_start_sprinting = player->inputs.forward_axis >= (player->under_water ? 1e-5f : 0.8f);

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        const bool is_moving_slowly = player->crouching || (player->GetDataPoseImpl() == Pose::Swimming && !player->in_water);
#else
        const bool is_moving_slowly = player->crouching;
#endif

        if (was_sneaking)
        {
            player->sprint_double_tap_trigger_time = 0;
        }

        bool has_blindness = false;
        for (const auto& effect : player->effects)
        {
            if (effect.type == EntityEffectType::Blindness && effect.end > std::chrono::steady_clock::now())
            {
                has_blindness = true;
                break;
            }
        }

        const bool can_start_sprinting = !(
            player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) ||
            !has_enough_impulse_to_start_sprinting ||
            !(player->food > 6 || player->may_fly) ||
            has_blindness ||
            player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying) ||
            (is_moving_slowly && !player->under_water)
        );

        if ((player->on_ground || player->under_water) && !was_sneaking && !had_enough_impulse_to_start_sprinting && can_start_sprinting)
        {
            if (player->sprint_double_tap_trigger_time > 0 || player->inputs.sprint)
            {
                SetSprinting(true);
            }
            else
            {
                player->sprint_double_tap_trigger_time = 7 * double_tap_cause_sprint;
            }
        }

        if ((!player->in_water || player->under_water) && can_start_sprinting && player->inputs.sprint)
        {
            SetSprinting(true);
        }

        // Stop sprinting if necessary
        if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting))
        {
            const bool stop_sprint_condition = player->inputs.forward_axis <= 1e-5 || (player->food <= 6 && !player->may_fly);
            if (IsSwimmingAndNotFlying())
            {
                if ((!player->on_ground && !player->inputs.sneak && stop_sprint_condition) || !player->in_water)
                {
                    SetSprinting(false);
                }
            }
            else if (stop_sprint_condition ||
                player->horizontal_collision || // TODO: add minor horizontal collision
                (player->in_water && !player->under_water))
            {
                SetSprinting(false);
            }
        }
    }

    void PhysicsManager::SetSprinting(const bool b) const
    {
        player->SetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting, b);
        player->RemoveAttributeModifierImpl(EntityAttribute::Type::MovementSpeed, PlayerEntity::speed_modifier_sprinting_key);
        if (b)
        {
            player->SetAttributeModifierImpl(EntityAttribute::Type::MovementSpeed, PlayerEntity::speed_modifier_sprinting_key,
                EntityAttribute::Modifier{
                    0.3,                                                // amount
                    EntityAttribute::Modifier::Operation::MultiplyTotal // operation
                }
            );
        }
    }

    void PhysicsManager::InputsToFly() const
    {
        // Start flying in Creative/Spectator
        bool fly_changed = false;
        if (player->may_fly)
        {
            // Auto trigger flying if in spectator mode
            if (player->game_mode == GameType::Spectator && !player->flying)
            {
                player->flying = true;
                fly_changed = true;
                OnUpdateAbilities();
            }
            // If double jump in creative, swap flying mode
            else if (!player->previous_jump && player->inputs.jump)
            {
                if (player->fly_jump_trigger_time == 0)
                {
                    player->fly_jump_trigger_time = 7;
                }
                else if (!IsSwimmingAndNotFlying())
                {
                    player->flying = !player->flying;
                    fly_changed = true;
                    OnUpdateAbilities();
                    player->fly_jump_trigger_time = 0;
                }
            }
        }

        bool has_levitation_effect = false;
        for (const auto& effect : player->effects)
        {
            if (effect.type == EntityEffectType::Levitation && effect.end > std::chrono::steady_clock::now())
            {
                has_levitation_effect = true;
                break;
            }
        }

        // Start elytra flying
        if (player->inputs.jump &&
            !fly_changed &&
            !player->previous_jump &&
            !player->flying &&
            !player->on_climbable &&
            !player->on_ground &&
            !player->in_water &&
            !player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying) &&
            !has_levitation_effect)
        {
            const Slot chest_slot = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_CHEST_ARMOR);
            if (!chest_slot.IsEmptySlot() &&
                chest_slot.GetItemId() == elytra_item->GetId() &&
                Utilities::GetDamageCount(chest_slot) < elytra_item->GetMaxDurability() - 1)
            {
                player->SetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying, true);
                std::shared_ptr<ServerboundPlayerCommandPacket> player_command_packet = std::make_shared<ServerboundPlayerCommandPacket>();
                player_command_packet->SetAction(static_cast<int>(PlayerCommandAction::StartFallFlying));
                player_command_packet->SetId_(player->entity_id);
                network_manager->Send(player_command_packet);
            }
        }
    }

    void PhysicsManager::InputsToJump() const
    {
        // Perform jump
        if (player->inputs.jump && !player->flying)
        {
            // Jump from fluid
            if (player->in_lava || player->in_water)
            {
                player->speed.y += 0.03999999910593033;
            }
            // Jump from ground
            else if (player->on_ground && player->jump_delay == 0)
            {
                // Get jump boost
                float jump_boost = 0.0f;
                for (const auto& effect : player->effects)
                {
                    if (effect.type == EntityEffectType::JumpBoost && effect.end > std::chrono::steady_clock::now())
                    {
                        jump_boost = 0.1f * (effect.amplifier + 1); // amplifier is 0 for "Effect I"
                        break;
                    }
                }

                // Get block underneath
                float block_jump_factor = 1.0f;
                const Blockstate* feet_block = world->GetBlock(Position(
                    static_cast<int>(std::floor(player->position.x)),
                    static_cast<int>(std::floor(player->position.y)),
                    static_cast<int>(std::floor(player->position.z))
                ));
                if (feet_block == nullptr || !feet_block->IsHoney())
                {
                    const Blockstate* below_block = world->GetBlock(GetBlockBelowAffectingMovement());
                    if (below_block != nullptr && below_block->IsHoney())
                    {
                        block_jump_factor = 0.4f;
                    }
                }
                else
                {
                    block_jump_factor = 0.4f;
                }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
                player->speed.y = 0.42f * block_jump_factor + jump_boost;
                if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting))
                {
                    const float yaw_rad = player->yaw * 0.017453292f /* PI/180 */;
                    player->speed.x -= std::sin(yaw_rad) * 0.2f;
                    player->speed.z += std::cos(yaw_rad) * 0.2f;
                }
#else
                const float jump_power = static_cast<float>(player->GetAttributeJumpStrengthValueImpl()) * block_jump_factor + jump_boost;
                if (jump_power > 1e-5f)
                {
                    player->speed.y = jump_power;
                    if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting))
                    {
                        const float yaw_rad = player->yaw * 0.017453292f /* PI/180 */;
                        player->speed.x -= static_cast<double>(std::sin(yaw_rad)) * 0.2;
                        player->speed.z += static_cast<double>(std::cos(yaw_rad)) * 0.2;
                    }
                }
#endif
                player->jump_delay = 10;
            }
        }
        else
        {
            player->jump_delay = 0;
        }
    }

    void PhysicsManager::ApplyInputs(const float strength) const
    {
        Vector3<double> input_vector(player->inputs.left_axis, 0.0, player->inputs.forward_axis);
        const double sqr_norm = input_vector.SqrNorm();
        if (input_vector.SqrNorm() < 1e-7)
        {
            return;
        }
        if (sqr_norm > 1.0)
        {
            input_vector.Normalize();
        }
        input_vector *= strength;
        const double sin_yaw = std::sin(player->yaw * 0.017453292f /* PI/180 */);
        const double cos_yaw = std::cos(player->yaw * 0.017453292f /* PI/180 */);

        player->speed.x += input_vector.x * cos_yaw - input_vector.z * sin_yaw;
        player->speed.y += input_vector.y;
        player->speed.z += input_vector.x * sin_yaw + input_vector.z * cos_yaw;
    }

    void PhysicsManager::SendPosition()
    {
        ticks_since_last_position_sent += 1;

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        // Before 1.21.2, shift was sent after jump
        // After 1.21.5 the ServerboundPlayerCommandPacket is not sent anymore
#if PROTOCOL_VERSION < 771 /* < 1.21.6 */
        const bool shift_key_down = player->inputs.sneak;
        if (shift_key_down != player->previous_shift_key_down)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_packet = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_packet->SetAction(static_cast<int>(shift_key_down ? PlayerCommandAction::PressShiftKey : PlayerCommandAction::ReleaseShifKey));
            player_command_packet->SetId_(player->entity_id);
            network_manager->Send(player_command_packet);
            player->previous_shift_key_down = shift_key_down;
        }
#endif

        if (player->last_sent_inputs.sneak        != player->inputs.sneak ||
            player->last_sent_inputs.jump         != player->inputs.jump ||
            player->last_sent_inputs.sprint       != player->inputs.sprint ||
            player->last_sent_inputs.forward_axis != player->inputs.forward_axis ||
            player->last_sent_inputs.left_axis    != player->inputs.left_axis)
        {
            std::shared_ptr<ServerboundPlayerInputPacket> player_input_packet = std::make_shared<ServerboundPlayerInputPacket>();
            player_input_packet->SetForward(player->inputs.forward_axis > 0.0f);
            player_input_packet->SetBackward(player->inputs.forward_axis < 0.0f);
            player_input_packet->SetLeft(player->inputs.left_axis > 0.0f);
            player_input_packet->SetRight(player->inputs.left_axis < 0.0f);
            player_input_packet->SetJump(player->inputs.jump);
            player_input_packet->SetShift(player->inputs.sneak);
            player_input_packet->SetSprint(player->inputs.sprint);
            network_manager->Send(player_input_packet);
            player->last_sent_inputs = player->inputs;
        }
#endif

        const bool sprinting = player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting);
        if (sprinting != player->previous_sprinting)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_packet = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_packet->SetAction(static_cast<int>(sprinting ? PlayerCommandAction::StartSprinting : PlayerCommandAction::StopSprinting));
            player_command_packet->SetId_(player->entity_id);
            network_manager->Send(player_command_packet);
            player->previous_sprinting = sprinting;
        }

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        // Before 1.21.2, shift was sent after jump
        const bool shift_key_down = player->inputs.sneak;
        if (shift_key_down != player->previous_shift_key_down)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_packet = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_packet->SetAction(static_cast<int>(shift_key_down ? PlayerCommandAction::PressShiftKey : PlayerCommandAction::ReleaseShifKey));
            player_command_packet->SetId_(player->entity_id);
            network_manager->Send(player_command_packet);
            player->previous_shift_key_down = shift_key_down;
        }
#endif

        const bool has_moved = (player->position - player->previous_position).SqrNorm() > 4e-8 || ticks_since_last_position_sent >= 20;
        const bool has_rotated = player->yaw != player->previous_yaw || player->pitch != player->previous_pitch;
        if (has_moved && has_rotated)
        {
            std::shared_ptr<ServerboundMovePlayerPacketPosRot> move_player_packet = std::make_shared<ServerboundMovePlayerPacketPosRot>();
            move_player_packet->SetX(player->position.x);
            move_player_packet->SetY(player->position.y);
            move_player_packet->SetZ(player->position.z);
            move_player_packet->SetXRot(player->pitch);
            move_player_packet->SetYRot(player->yaw);
            move_player_packet->SetOnGround(player->on_ground);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            move_player_packet->SetHorizontalCollision(player->horizontal_collision);
#endif
            network_manager->Send(move_player_packet);
        }
        else if (has_moved)
        {
            std::shared_ptr<ServerboundMovePlayerPacketPos> move_player_packet = std::make_shared<ServerboundMovePlayerPacketPos>();
            move_player_packet->SetX(player->position.x);
            move_player_packet->SetY(player->position.y);
            move_player_packet->SetZ(player->position.z);
            move_player_packet->SetOnGround(player->on_ground);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            move_player_packet->SetHorizontalCollision(player->horizontal_collision);
#endif
            network_manager->Send(move_player_packet);
        }
        else if (has_rotated)
        {
            std::shared_ptr<ServerboundMovePlayerPacketRot> move_player_packet = std::make_shared<ServerboundMovePlayerPacketRot>();
            move_player_packet->SetXRot(player->pitch);
            move_player_packet->SetYRot(player->yaw);
            move_player_packet->SetOnGround(player->on_ground);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            move_player_packet->SetHorizontalCollision(player->horizontal_collision);
#endif
            network_manager->Send(move_player_packet);
        }
        else if (player->on_ground != player->previous_on_ground
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            || player->horizontal_collision != player->previous_horizontal_collision
#endif
            )
        {
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            std::shared_ptr<ServerboundMovePlayerPacketStatusOnly> move_player_packet = std::make_shared<ServerboundMovePlayerPacketStatusOnly>();
#else
            std::shared_ptr<ServerboundMovePlayerPacket> move_player_packet = std::make_shared<ServerboundMovePlayerPacket>();
#endif
            move_player_packet->SetOnGround(player->on_ground);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
            move_player_packet->SetHorizontalCollision(player->horizontal_collision);
#endif
            network_manager->Send(move_player_packet);
        }

        if (has_moved)
        {
            player->previous_position = player->position;
            ticks_since_last_position_sent = 0;
        }
        if (has_rotated)
        {
            player->previous_yaw = player->yaw;
            player->previous_pitch = player->pitch;
        }
        player->previous_on_ground = player->on_ground;
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        player->previous_horizontal_collision = player->horizontal_collision;
#endif

#if USE_GUI
        if (rendering_manager != nullptr && (has_moved || has_rotated))
        {
            rendering_manager->SetPosOrientation(
                player->position.x,
                player->position.y + player->GetEyeHeightImpl(),
                player->position.z,
                player->yaw,
                player->pitch
            );
        }
#endif
    }

    Vector3<double> PhysicsManager::CollideBoundingBox(const AABB& aabb, const Vector3<double>& movement) const
    {
        const std::vector<AABB> colliders = world->GetColliders(aabb, movement);
        // TODO: add world borders to colliders?
        if (colliders.size() == 0)
        {
            return movement;
        }

        Vector3<double> collided_movement = movement;

        AABB moved_aabb = aabb;
        // Collision on Y axis
        CollideOneAxis(moved_aabb, collided_movement, 1, colliders);

        // Collision on X before Z
        if (std::abs(collided_movement.x) > std::abs(collided_movement.z))
        {
            CollideOneAxis(moved_aabb, collided_movement, 0, colliders);
            CollideOneAxis(moved_aabb, collided_movement, 2, colliders);
        }
        // Collision on X after Z
        else
        {
            CollideOneAxis(moved_aabb, collided_movement, 2, colliders);
            CollideOneAxis(moved_aabb, collided_movement, 0, colliders);
        }

        return collided_movement;
    }

    void PhysicsManager::CollideOneAxis(AABB& aabb, Vector3<double>& movement, const unsigned int axis, const std::vector<AABB>& colliders) const
    {
        const Vector3<double> min_aabb = aabb.GetMin();
        const Vector3<double> max_aabb = aabb.GetMax();
        const int this_axis = axis % 3;
        const int axis_1 = (axis + 1) % 3;
        const int axis_2 = (axis + 2) % 3;

        for (const AABB& collider : colliders)
        {
            if (std::abs(movement[this_axis]) < 1.0e-7)
            {
                movement[this_axis] = 0.0;
                break;
            }
            const Vector3<double> min_collider = collider.GetMin();
            const Vector3<double> max_collider = collider.GetMax();
            if (max_aabb[axis_1] - 1e-7 > min_collider[axis_1] && min_aabb[axis_1] + 1e-7 < max_collider[axis_1] &&
                max_aabb[axis_2] - 1e-7 > min_collider[axis_2] && min_aabb[axis_2] + 1e-7 < max_collider[axis_2])
            {
                if (movement[this_axis] > 0.0 && max_aabb[this_axis] - 1e-7 <= min_collider[this_axis])
                {
                    movement[this_axis] = std::min(min_collider[this_axis] - max_aabb[this_axis], movement[this_axis]);
                }
                else if (movement[this_axis] < 0.0 && min_aabb[this_axis] + 1e-7 >= max_collider[this_axis])
                {
                    movement[this_axis] = std::max(max_collider[this_axis] - min_aabb[this_axis], movement[this_axis]);
                }
            }
        }
        Vector3<double> translation(0.0, 0.0, 0.0);
        translation[this_axis] = movement[this_axis];
        aabb.Translate(translation);
    }

    bool PhysicsManager::IsSwimmingAndNotFlying() const
    {
        return !player->flying &&
            player->game_mode != GameType::Spectator &&
            player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Swimming);
    }

    bool PhysicsManager::IsInClimbable() const
    {
        if (player->game_mode == GameType::Spectator)
        {
            return false;
        }

        const Blockstate* feet_block = world->GetBlock(Position(
            static_cast<int>(std::floor(player->position.x)),
            static_cast<int>(std::floor(player->position.y)),
            static_cast<int>(std::floor(player->position.z))
        ));

        // TODO: if trapdoor AND below block is a ladder with the same facing property
        // as the trapdoor then the trapdoor is a climbable block too
        return feet_block != nullptr && feet_block->IsClimbable();
    }

    void PhysicsManager::MovePlayer() const
    { // LivingEntity::travel
        const bool going_down = player->speed.y <= 0.0;
        bool has_slow_falling = false;
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        for (const auto& effect : player->effects)
        {
            if (effect.type == EntityEffectType::SlowFalling && effect.end > std::chrono::steady_clock::now())
            {
                has_slow_falling = true;
                break;
            }
        }
#endif

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const double drag = (going_down && has_slow_falling) ? 0.01 : 0.08;
#else
        const double drag = (going_down && has_slow_falling) ? std::min(0.01, player->GetAttributeGravityValueImpl()) : player->GetAttributeGravityValueImpl();
#endif

        // Move in water
        if (player->in_water && !player->flying)
        {
            const double init_y = player->position.y;
            float water_slow_down = player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) ? 0.9f : 0.8f;
            float inputs_strength = 0.02f;

#if PROTOCOL_VERSION < 767 /* < 1.21 */
            const Slot boots_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_FEET_ARMOR);
            float depth_strider_mult = std::min(static_cast<float>(Utilities::GetEnchantmentLvl(boots_armor, Enchantment::DepthStrider)), 3.0f) / 3.0f;
#else
            float depth_strider_mult = static_cast<float>(player->GetAttributeWaterMovementEfficiencyValueImpl());
#endif
            if (!player->on_ground)
            {
                depth_strider_mult *= 0.5f;
            }
            if (depth_strider_mult > 0.0)
            {
                water_slow_down += (0.54600006f - water_slow_down) * depth_strider_mult;
                inputs_strength += (static_cast<float>(player->GetAttributeMovementSpeedValueImpl()) - inputs_strength) * depth_strider_mult;
            }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
            for (const auto& effect : player->effects)
            {
                if (effect.type == EntityEffectType::DolphinsGrace && effect.end > std::chrono::steady_clock::now())
                {
                    water_slow_down = 0.96f;
                    break;
                }
            }
#endif
            ApplyInputs(inputs_strength);
            ApplyMovement();

            if (player->horizontal_collision && player->on_climbable)
            {
                player->speed.y = 0.2;
            }
            player->speed.x *= water_slow_down;
            player->speed.y *= 0.800000011920929;
            player->speed.z *= water_slow_down;

            if (!player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting))
            {
                if (going_down &&
                    std::abs(player->speed.y - 0.005) >= 0.003 &&
                    std::abs(player->speed.y - drag / 16.0) < 0.003)
                {
                    player->speed.y = -0.003;
                }
                else
                {
                    player->speed.y -= drag / 16.0;
                }
            }

            // Jump out of water
            if (player->horizontal_collision &&
                world->IsFree(player->GetColliderImpl().Inflate(-1e-7) + player->speed + Vector3<double>(0.0, 0.6000000238418579 - player->position.y + init_y, 0.0), true))
            {
                player->speed.y = 0.30000001192092896;
            }
        }
        // Move in lava
        else if (player->in_lava && !player->flying)
        {
            const double init_y = player->position.y;
            ApplyInputs(0.02f);
            ApplyMovement();
            player->speed *= 0.5;
            player->speed.y -= drag / 4.0;
            // Jump out of lava
            if (player->horizontal_collision &&
                world->IsFree(player->GetColliderImpl().Inflate(-1e-7) + player->speed + Vector3<double>(0.0, 0.6000000238418579 - player->position.y + init_y, 0.0), true))
            {
                player->speed.y = 0.30000001192092896;
            }
        }
        // Move with elytra
        else if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying))
        {
            // sqrt(front_vector.x² + front_vector.z²) to follow vanilla code
            // it's equal to cos(pitch) (as -90°<=pitch<=90°, cos(pitch) >= 0.0)
            const double cos_pitch_from_length = std::sqrt(player->front_vector.x * player->front_vector.x + player->front_vector.z * player->front_vector.z);
            const double cos_pitch = std::cos(static_cast<double>(player->pitch * 0.017453292f /* PI/180 */));
            const double cos_pitch_sqr = cos_pitch * cos_pitch;
            const double horizontal_speed = std::sqrt(player->speed.x * player->speed.x + player->speed.z * player->speed.z);

            player->speed.y += drag * (-1.0 + 0.75 * cos_pitch_sqr);

            if (player->speed.y < 0.0 && cos_pitch_from_length > 0.0) // cos condition to prevent dividing by 0
            {
                const double delta_speed = -player->speed.y * 0.1 * cos_pitch_sqr;
                player->speed.x += player->front_vector.x * delta_speed / cos_pitch_from_length;
                player->speed.y += delta_speed;
                player->speed.z += player->front_vector.z * delta_speed / cos_pitch_from_length;
            }
            if (player->pitch < 0.0 && cos_pitch_from_length > 0.0) // cos condition to prevent dividing by 0
            {
                // player->front_vector.y == -sin(pitch)
                const double delta_speed = horizontal_speed * player->front_vector.y * 0.04;
                player->speed.x -= player->front_vector.x * delta_speed / cos_pitch_from_length;
                player->speed.y += delta_speed * 3.2;
                player->speed.z -= player->front_vector.z * delta_speed / cos_pitch_from_length;
            }
            if (cos_pitch_from_length > 0.0) // cos condition to prevent dividing by 0
            {
                player->speed.x += (player->front_vector.x / cos_pitch_from_length * horizontal_speed - player->speed.x) * 0.1;
                player->speed.z += (player->front_vector.z / cos_pitch_from_length * horizontal_speed - player->speed.z) * 0.1;
            }
            player->speed *= Vector3<double>(0.9900000095367432, 0.9800000190734863, 0.9900000095367432);
            ApplyMovement();
            // Not sure this is required as the server should send an update
            // anyway in case it should be set to false
            if (player->on_ground)
            {
                player->SetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying, false);
            }
        }
        // Move generic case
        else
        {
            const Blockstate* below_block = world->GetBlock(GetBlockBelowAffectingMovement());
            const float friction = below_block == nullptr ? 0.6f : below_block->GetFriction();
            const float inertia = player->on_ground ? friction * 0.91f : 0.91f;

            ApplyInputs(player->on_ground ?
                (static_cast<float>(player->GetAttributeMovementSpeedValueImpl()) * (0.21600002f / (friction * friction * friction))) :
#if PROTOCOL_VERSION < 762 /* < 1.19.4 */
                player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) ? 0.02f + 0.006f : 0.02f // flying_speed updated during Player::aiStep call
#else
                player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) ? 0.025999999f : 0.02f // Player::getFlyingSpeed overload
#endif
            );
            if (player->on_climbable)
            { // LivingEntity::handleOnClimbable
                player->speed.x = std::clamp(player->speed.x, -0.15000000596046448, 0.15000000596046448);
                player->speed.y = std::max(player->speed.y, -0.15000000596046448);
                // Remove negative Y speed if feet are inside a scaffolding block and not pressing
                // sneak, or if not a scaffolding block and pressing sneak
                const Blockstate* feet_block = world->GetBlock(Position(
                    static_cast<int>(std::floor(player->position.x)),
                    static_cast<int>(std::floor(player->position.y)),
                    static_cast<int>(std::floor(player->position.z))
                ));
                if (feet_block != nullptr && feet_block->IsScaffolding() != player->inputs.sneak)
                {
                    player->speed.y = 0.0;
                }
                player->speed.z = std::clamp(player->speed.z, -0.15000000596046448, 0.15000000596046448);
            }
            ApplyMovement();
            // If colliding and in climbable, go up
            if ((player->horizontal_collision || player->inputs.jump) &&
                (player->on_climbable) // TODO: or in powder snow with leather boots
            )
            {
                player->speed.y = 0.2;
            }

            unsigned char levitation = 0;
            for (const auto& effect : player->effects)
            {
                if (effect.type == EntityEffectType::Levitation && effect.end > std::chrono::steady_clock::now())
                {
                    levitation = effect.amplifier + 1; // amplifier is 0 for "Effect I"
                    break;
                }
            }
            if (levitation > 0)
            {
                player->speed.y += (0.05 * levitation - player->speed.y) * 0.2;
            }
            else
            {
                player->speed.y -= drag;
            }
            player->speed.x *= inertia;
            player->speed.y *= 0.9800000190734863;
            player->speed.z *= inertia;
        }
    }

    void PhysicsManager::ApplyMovement() const
    { // Entity::move
        // If no physics, just add speed to position
        if (player->game_mode == GameType::Spectator)
        {
            player->position += player->speed;
            return;
        }

        Vector3<double> movement = player->speed;
        // If player is stuck, reset stuck multiplier and set speed to 0
        if (player->stuck_speed_multiplier.SqrNorm() > 1e-7)
        {
            movement *= player->stuck_speed_multiplier;
            player->stuck_speed_multiplier *= 0.0;
            player->speed *= 0.0;
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        constexpr double max_up_step = 0.6;
#else
        const double max_up_step = player->GetAttributeStepHeightValueImpl();
#endif
        const AABB player_aabb = player->GetColliderImpl();
        if (!player->flying
            && movement.y <= 0.0
            && player->inputs.sneak
            && player->on_ground
        )
        { // Player::maybeBackOffFromEdge
            const double step = 0.05;

            while (movement.x != 0.0 && world->IsFree((player_aabb + Vector3<double>(movement.x, -max_up_step, 0.0)).Inflate(-1e-7), false))
            {
                movement.x = (movement.x < step && movement.x >= -step) ? 0.0 : (movement.x > 0.0 ? (movement.x - step) : (movement.x + step));
            }

            while (movement.z != 0.0 && world->IsFree((player_aabb + Vector3<double>(0.0, -max_up_step, movement.z)).Inflate(-1e-7), false))
            {
                movement.z = (movement.z < step && movement.z >= -step) ? 0.0 : (movement.z > 0.0 ? (movement.z - step) : (movement.z + step));
            }

            while (movement.x != 0.0 && movement.z != 0.0 && world->IsFree((player_aabb + Vector3<double>(movement.x, -max_up_step, movement.z)).Inflate(-1e-7), false))
            {
                movement.x = (movement.x < step && movement.x >= -step) ? 0.0 : (movement.x > 0.0 ? (movement.x - step) : (movement.x + step));
                movement.z = (movement.z < step && movement.z >= -step) ? 0.0 : (movement.z > 0.0 ? (movement.z - step) : (movement.z + step));
            }
        }

        const Vector3<double> movement_before_collisions = movement;
        { // Entity::collide
            if (movement.SqrNorm() != 0.0)
            {
                movement = CollideBoundingBox(player_aabb, movement);
            }

            // Step up if block height delta is < max_up_step
            // If already on ground (or collided with the ground while moving down) and horizontal collision
            // TODO: changed in 1.21, check if this is still accurate
            if ((player->on_ground || (movement.y != movement_before_collisions.y && movement_before_collisions.y < 0.0)) &&
                (movement.x != movement_before_collisions.x || movement.z != movement_before_collisions.z))
            {
                Vector3<double> movement_with_step_up = CollideBoundingBox(player_aabb, Vector3<double>(movement_before_collisions.x, max_up_step, movement_before_collisions.z));
                const Vector3<double> horizontal_movement(
                    movement_before_collisions.x,
                    0.0,
                    movement_before_collisions.z
                );
                const Vector3<double> movement_step_up_only = CollideBoundingBox(AABB(player_aabb.GetCenter() + horizontal_movement * 0.5, player_aabb.GetHalfSize() + horizontal_movement.Abs() * 0.5), Vector3<double>(0.0, max_up_step, 0.0));
                if (movement_step_up_only.y < max_up_step)
                {
                    const Vector3<double> check = CollideBoundingBox(player_aabb + movement_step_up_only, horizontal_movement) + movement_step_up_only;
                    if (check.x * check.x + check.z * check.z > movement_with_step_up.x * movement_with_step_up.x + movement_with_step_up.z * movement_with_step_up.z)
                    {
                        movement_with_step_up = check;
                    }
                }
                if (movement_with_step_up.x * movement_with_step_up.x + movement_with_step_up.z * movement_with_step_up.z > movement.x * movement.x + movement.z * movement.z)
                {
                    movement = movement_with_step_up + CollideBoundingBox(player_aabb + movement_with_step_up, Vector3<double>(0.0, -movement_with_step_up.y + movement_before_collisions.y, 0.0));
                }
            }
        }

        if (movement.SqrNorm() > 1.0e-7)
        {
            player->position += movement;
        }
        const bool collision_x = movement_before_collisions.x != movement.x;
        const bool collision_y = movement_before_collisions.y != movement.y;
        const bool collision_z = movement_before_collisions.z != movement.z;
        player->horizontal_collision = collision_x || collision_z;
        // TODO: add minor horizontal collision check
        { // Entity::setOngroundWithKnownMovement
            player->on_ground = movement_before_collisions.y < 0.0 && collision_y;

            if (player->on_ground)
            {
                const double half_width = 0.5 * player->GetWidthImpl();
                const AABB feet_slice_aabb(
                    Vector3<double>(
                        player->position.x,
                        player->position.y - 0.5e-6,
                        player->position.z),
                    Vector3<double>(half_width, 0.5e-6, half_width));
                std::optional<Position> supporting_block_pos = world->GetSupportingBlockPos(feet_slice_aabb);
                if (supporting_block_pos.has_value() || player->on_ground_without_supporting_block)
                {
                    player->supporting_block_pos = supporting_block_pos;
                }
                else
                {
                    player->supporting_block_pos = world->GetSupportingBlockPos(feet_slice_aabb + Vector3<double>(-movement.x, 0.0, -movement.z));
                }
                player->on_ground_without_supporting_block = !player->supporting_block_pos.has_value();
            }
            else
            {
                player->on_ground_without_supporting_block = false;
                player->supporting_block_pos = std::optional<Position>();
            }
        }

        // Update speeds
        if (collision_x)
        {
            player->speed.x = 0.0;
        }
        if (collision_z)
        {
            player->speed.z = 0.0;
        }
        if (collision_y)
        {
            if (player->inputs.sneak)
            {
                player->speed.y = 0.0;
            }
            else
            {
                const Blockstate* block_below = world->GetBlock(Position(
                    static_cast<int>(std::floor(player->position.x)),
                    static_cast<int>(std::floor(player->position.y - 0.2)),
                    static_cast<int>(std::floor(player->position.z))
                ));
                double new_speed = 0.0;
                if (block_below != nullptr)
                {
                    if (block_below->IsSlime())
                    {
                        new_speed = -player->speed.y;
                    }
                    else if (block_below->IsBed())
                    {
                        new_speed = player->speed.y * -0.66f;
                    }
                }
                player->speed.y = new_speed;
            }
        }

        CheckInsideBlocks();

#if PROTOCOL_VERSION > 578 /* > 1.15.2 */ && PROTOCOL_VERSION < 767 /* < 1.21 */
        short soul_speed_lvl = 0;
        // Get SoulSpeed bonus from boots
        const Slot boots_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_FEET_ARMOR);
        soul_speed_lvl = Utilities::GetEnchantmentLvl(boots_armor, Enchantment::SoulSpeed);
#else
        constexpr short soul_speed_lvl = 0;
#endif
        float block_speed_factor = 1.0f;
        const Blockstate* feet_block = world->GetBlock(Position(
            static_cast<int>(std::floor(player->position.x)),
            static_cast<int>(std::floor(player->position.y)),
            static_cast<int>(std::floor(player->position.z))
        ));
        if (feet_block != nullptr && (feet_block->IsHoney() || (feet_block->IsSoulSand() && soul_speed_lvl == 0)))
        {
            block_speed_factor = 0.4f;
        }
        if (block_speed_factor == 1.0f)
        {
            const Blockstate* below_block = world->GetBlock(GetBlockBelowAffectingMovement());
            if (below_block != nullptr && (below_block->IsHoney() || (below_block->IsSoulSand() && soul_speed_lvl == 0)))
            {
                block_speed_factor = 0.4f;
            }
        }

#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
        block_speed_factor = block_speed_factor + static_cast<float>(player->GetAttributeMovementEfficiencyValueImpl()) * (1.0f - block_speed_factor);
#endif

        player->speed.x *= block_speed_factor;
        player->speed.z *= block_speed_factor;
    }

    void PhysicsManager::OnUpdateAbilities() const
    {
        player->UpdateAbilitiesFlagsImpl();
        std::shared_ptr<ServerboundPlayerAbilitiesPacket> abilities_packet = std::make_shared<ServerboundPlayerAbilitiesPacket>();
        abilities_packet->SetFlags(player->abilities_flags);
#if PROTOCOL_VERSION < 727 /* < 1.16 */
        abilities_packet->SetFlyingSpeed(player->flying_speed);
        abilities_packet->SetWalkingSpeed(player->walking_speed);
#endif
        network_manager->Send(abilities_packet);
    }

    void PhysicsManager::CheckInsideBlocks() const
    {
        const AABB aabb = player->GetColliderImpl().Inflate(-1.0e-7);
        const Vector3<double> min_aabb = aabb.GetMin();
        const Vector3<double> max_aabb = aabb.GetMax();
        Position block_pos;
        for (int y = static_cast<int>(std::floor(min_aabb.y)); y <= static_cast<int>(std::floor(max_aabb.y)); ++y)
        {
            block_pos.y = y;
            for (int z = static_cast<int>(std::floor(min_aabb.z)); z <= static_cast<int>(std::floor(max_aabb.z)); ++z)
            {
                block_pos.z = z;
                for (int x = static_cast<int>(std::floor(min_aabb.x)); x <= static_cast<int>(std::floor(max_aabb.x)); ++x)
                {
                    block_pos.x = x;
                    const Blockstate* block = world->GetBlock(block_pos);
                    if (block == nullptr)
                    {
                        continue;
                    }
                    else if (block->IsCobweb())
                    { // WebBlock::entityInside
                        player->stuck_speed_multiplier = Vector3<double>(0.25, 0.05000000074505806, 0.25);
                    }
                    else if (block->IsBubbleColumn())
                    {
                        const Blockstate* above_block = world->GetBlock(block_pos + Position(0, 1, 0));
                        if (above_block == nullptr || above_block->IsAir())
                        { // Entity::onAboveBubbleCol
                            player->speed.y = block->IsDownBubbleColumn() ? std::max(-0.9, player->speed.y - 0.03) : std::min(1.8, player->speed.y + 0.1);
                        }
                        else
                        { // Entity::onInsideBubbleColumn
                            player->speed.y = block->IsDownBubbleColumn() ? std::max(-0.3, player->speed.y - 0.03) : std::min(0.7, player->speed.y + 0.06);
                        }
                    }
                    else if (block->IsHoney())
                    {
                        // Check if sliding down on the side of the block
                        if (!player->on_ground &&
                            player->position.y <= y + 0.9375 - 1.0e-7 &&
                            player->speed.y < -0.08 && (
                                std::abs(x + 0.5 - player->position.x) + 1.0e-7 > 0.4375 + player->GetWidthImpl() / 2.0 ||
                                std::abs(z + 0.5 - player->position.z) + 1.0e-7 > 0.4375 + player->GetWidthImpl() / 2.0)
                            )
                        {
                            if (player->speed.y < -0.13)
                            {
                                const double factor = -0.05 / player->speed.y;
                                player->speed.x *= factor;
                                player->speed.y = -0.05;
                                player->speed.z *= factor;
                            }
                            else
                            {
                                player->speed.y = -0.05;
                            }
                        }
                    }
                    else if (block->IsBerryBush())
                    { // SweetBerryBushBlock::entityInside
                        player->stuck_speed_multiplier = Vector3<double>(0.800000011920929, 0.75, 0.800000011920929);
                    }
                    else if (block->IsPowderSnow())
                    { // PowderSnowBlock::entityInside
                        const Blockstate* feet_block = world->GetBlock(Position(
                            static_cast<int>(std::floor(player->position.x)),
                            static_cast<int>(std::floor(player->position.y)),
                            static_cast<int>(std::floor(player->position.z))
                        ));
                        if (feet_block != nullptr && feet_block->IsPowderSnow())
                        {
                            player->stuck_speed_multiplier = Vector3<double>(0.8999999761581421, 1.5, 0.8999999761581421);
                        }
                    }
                }
            }
        }
    }

    Position PhysicsManager::GetBlockBelowAffectingMovement() const
    {
        if (player->supporting_block_pos.has_value())
        {
            Position output = player->supporting_block_pos.value();
            output.y = static_cast<int>(std::floor(player->position.y) - 0.500001);
            return output;
        }

        return Position(
            static_cast<int>(std::floor(player->position.x)),
            static_cast<int>(std::floor(player->position.y - 0.500001)),
            static_cast<int>(std::floor(player->position.z))
        );
    }

} //Botcraft
