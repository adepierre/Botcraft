#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Physics/PhysicsManager.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"
#include "botcraft/Utilities/NBTUtilities.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Item.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/World/World.hpp"
#if USE_GUI
#include "botcraft/Renderer/RenderingManager.hpp"
#endif

#define PI 3.14159265359

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
        ticks_since_last_position_sent = 0;

        const AssetsManager& assets_manager = AssetsManager::getInstance();

        elytra_item = assets_manager.GetItem(assets_manager.GetItemID("minecraft:elytra"));
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

    void PhysicsManager::Physics()
    {
        Logger::GetInstance().RegisterThread("Physics - " + network_manager->GetMyName());

        while (should_run)
        {
            // End of the current tick
            auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(50);

            if (network_manager->GetConnectionState() == ConnectionState::Play)
            {
                if (player == nullptr)
                {
                    player = entity_manager->GetLocalPlayer();
                }

                if (player != nullptr && !std::isnan(player->GetY()))
                {
                    // As PhysicsManager is a friend of LocalPlayer, we can lock the whole entity
                    // while physics is processed. This also means we can't use public interface
                    // as it's thread-safe by design and would deadlock because of this global lock
                    std::scoped_lock<std::shared_mutex> lock(player->entity_mutex);
                    PhysicsTick();
                }
            }
            // Wait for end of tick
            Utilities::SleepUntil(end);
        }
    }

    void PhysicsManager::PhysicsTick()
    {
        // TODO: add firework rocket speed if present
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

                    InputsToCrouch();

                    // TODO: if game_mode != GameType::Spectator, move towards closest free space if inside block

                    InputsToSprint();

                    InputsToFly();

                    // If sneaking in water, add downward speed
                    if (player->in_water && player->inputs.sneak && !player->flying)
                    {
                        player->speed.y -= 0.04;
                    }

                    // If flying in spectator/creative, go up/down if sneak/jump
                    if (player->flying)
                    {
                        player->speed.y += (-1 * player->inputs.sneak + player->inputs.jump) * player->flying_speed * 3.0;
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

                        player->inputs.forward_axis *= 0.98;
                        player->inputs.left_axis *= 0.98;

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

                // TODO: UpdatePlayerPose() ?
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
                push *= 0.0045000000000000005 / push_norm;
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

        // If crouch, slow down player inputs
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        if (player->crouching || (player->GetDataPoseImpl() == Pose::Swimming && !player->in_water))
#else
        if (player->crouching)
#endif
        {
            float sneak_coefficient = 0.3f;
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
            // Get SneakSpeed bonus from pants
            const Slot leggings_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_LEGS_ARMOR);
            sneak_coefficient += Utilities::GetEnchantmentLvl(leggings_armor.GetNBT(), "swift_sneak") * 0.15f;
            sneak_coefficient = std::min(std::max(0.0f, sneak_coefficient), 1.0f);
#endif
            player->inputs.forward_axis *= sneak_coefficient;
            player->inputs.left_axis *= sneak_coefficient;
        }
    }

    void PhysicsManager::InputsToSprint() const
    {
        bool has_blindness = false;
        for (const auto& effect : player->effects)
        {
            if (effect.type == EntityEffectType::Blindness && effect.end > std::chrono::steady_clock::now())
            {
                has_blindness = true;
                break;
            }
        }

        const bool can_start_sprinting = !player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) &&
            player->inputs.forward_axis >= (player->under_water ? 1e-5 : 0.8) &&
            (player->may_fly || player->food > 6) &&
            !player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying) &&
            !has_blindness;

        // Start sprinting if possible
        const bool could_sprint_previous = player->previous_forward >= (player->under_water ? 1e-5 : 0.8);
        if (can_start_sprinting && player->inputs.sprint && (
            (!player->in_water || player->under_water) ||
            ((player->on_ground || player->under_water) && !player->previous_sneak && !could_sprint_previous)
            ))
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
        player->RemoveAttributeModifierImpl(EntityAttribute::Type::MovementSpeed, PlayerEntity::speed_modifier_sprinting_uuid);
        if (b)
        {
            player->SetAttributeModifierImpl(EntityAttribute::Type::MovementSpeed, PlayerEntity::speed_modifier_sprinting_uuid,
                EntityAttribute::Modifier{
                    0.3,                                                // amount
                    EntityAttribute::Modifier::Operation::MultiplyTotal // operation
                });
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
            player->previous_jump &&
            !player->flying &&
            !player->on_climbable &&
            !player->on_ground &&
            !player->in_water &&
            !player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying) &&
            !has_levitation_effect)
        {
            const Slot chest_slot = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_CHEST_ARMOR);
            if (!chest_slot.IsEmptySlot() &&
                chest_slot.GetItemID() == elytra_item->GetId() &&
                Utilities::GetDamageCount(chest_slot.GetNBT()) < 432 - 1) // TODO: replace 432 by max elytra durability
            {
                player->SetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying, true);
                std::shared_ptr<ServerboundPlayerCommandPacket> player_command_msg = std::make_shared<ServerboundPlayerCommandPacket>();
                player_command_msg->SetAction(static_cast<int>(PlayerCommandAction::StartFallFlying));
                player_command_msg->SetId_(player->entity_id);
                network_manager->Send(player_command_msg);
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
                player->speed.y += 0.04;
            }
            // Jump from ground
            else if (player->on_ground && player->jump_delay == 0)
            {
                // Get jump boost
                double jump_boost = 0.0;
                for (const auto& effect : player->effects)
                {
                    if (effect.type == EntityEffectType::JumpBoost && effect.end > std::chrono::steady_clock::now())
                    {
                        jump_boost = 0.1 * effect.amplifier + 0.1; // amplifier is 0 for "Effect I"
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
                    const Blockstate* below_block = world->GetBlock(Position(
                        static_cast<int>(std::floor(player->position.x)),
                        static_cast<int>(std::floor(player->position.y - 0.5)),
                        static_cast<int>(std::floor(player->position.z))
                    ));
                    if (below_block != nullptr && below_block->IsHoney())
                    {
                        block_jump_factor = 0.4f;
                    }
                }
                else
                {
                    block_jump_factor = 0.4f;
                }

                const double jump_power = 0.42 * block_jump_factor + jump_boost;
                player->speed.y = jump_power;
                if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting))
                {
                    const double yaw_rad = player->yaw * PI / 180.0;
                    player->speed.x -= std::sin(yaw_rad) * 0.2;
                    player->speed.z += std::cos(yaw_rad) * 0.2;
                }
                player->jump_delay = 10;
            }
        }
        else
        {
            player->jump_delay = 0;
        }
    }

    void PhysicsManager::ApplyInputs(const double strength) const
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
        const double sin_yaw = std::sin(player->yaw * PI / 180.0);
        const double cos_yaw = std::cos(player->yaw * PI / 180.0);

        player->speed.x += input_vector.x * cos_yaw - input_vector.z * sin_yaw;
        player->speed.y += input_vector.y;
        player->speed.z += input_vector.x * sin_yaw + input_vector.z * cos_yaw;
    }

    void PhysicsManager::SendPosition()
    {
        ticks_since_last_position_sent += 1;

        const bool sprinting = player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting);
        if (sprinting != player->previous_sprinting)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_msg = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_msg->SetAction(static_cast<int>(sprinting ? PlayerCommandAction::StartSprinting : PlayerCommandAction::StopSprinting));
            player_command_msg->SetId_(player->entity_id);
            network_manager->Send(player_command_msg);
            player->previous_sprinting = sprinting;
        }

        const bool shift_key_down = player->inputs.sneak;
        if (shift_key_down != player->previous_shift_key_down)
        {
            std::shared_ptr<ServerboundPlayerCommandPacket> player_command_msg = std::make_shared<ServerboundPlayerCommandPacket>();
            player_command_msg->SetAction(static_cast<int>(shift_key_down ? PlayerCommandAction::PressShiftKey : PlayerCommandAction::ReleaseShifKey));
            player_command_msg->SetId_(player->entity_id);
            network_manager->Send(player_command_msg);
            player->previous_shift_key_down = shift_key_down;
        }

        const bool has_moved = (player->position - player->previous_position).SqrNorm() > 4e-8 || ticks_since_last_position_sent >= 20;
        const bool has_rotated = player->yaw != player->previous_yaw || player->pitch != player->previous_pitch;
        if (has_moved && has_rotated)
        {
            std::shared_ptr<ServerboundMovePlayerPacketPosRot> move_player_msg = std::make_shared<ServerboundMovePlayerPacketPosRot>();
            move_player_msg->SetX(player->position.x);
            move_player_msg->SetY(player->position.y);
            move_player_msg->SetZ(player->position.z);
            move_player_msg->SetXRot(player->pitch);
            move_player_msg->SetYRot(player->yaw);
            move_player_msg->SetOnGround(player->on_ground);
            network_manager->Send(move_player_msg);
        }
        else if (has_moved)
        {
            std::shared_ptr<ServerboundMovePlayerPacketPos> move_player_msg = std::make_shared<ServerboundMovePlayerPacketPos>();
            move_player_msg->SetX(player->position.x);
            move_player_msg->SetY(player->position.y);
            move_player_msg->SetZ(player->position.z);
            move_player_msg->SetOnGround(player->on_ground);
            network_manager->Send(move_player_msg);
        }
        else if (has_rotated)
        {
            std::shared_ptr<ServerboundMovePlayerPacketRot> move_player_msg = std::make_shared<ServerboundMovePlayerPacketRot>();
            move_player_msg->SetXRot(player->pitch);
            move_player_msg->SetYRot(player->yaw);
            move_player_msg->SetOnGround(player->on_ground);
            network_manager->Send(move_player_msg);
        }
        else if (player->on_ground != player->previous_on_ground)
        {
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
            std::shared_ptr<ServerboundMovePlayerPacketStatusOnly> move_player_msg = std::make_shared<ServerboundMovePlayerPacketStatusOnly>();
#else
            std::shared_ptr<ServerboundMovePlayerPacket> move_player_msg = std::make_shared<ServerboundMovePlayerPacket>();
#endif
            move_player_msg->SetOnGround(player->on_ground);
            network_manager->Send(move_player_msg);
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

    void PhysicsManager::Collisions(Vector3<double>& movement, AABB& aabb) const
    {
        const std::vector<AABB> colliders = world->GetColliders(aabb, movement);
        // TODO: add world borders to colliders?
        if (colliders.size() == 0)
        {
            return;
        }
        Vector3<double> min_aabb = aabb.GetMin();
        Vector3<double> max_aabb = aabb.GetMax();
        // Collisions on Y axis
        for (const AABB& collider : colliders)
        {
            if (std::abs(movement.y) < 1.0e-7)
            {
                movement.y = 0.0;
                break;
            }
            const Vector3<double> min_collider = collider.GetMin();
            const Vector3<double> max_collider = collider.GetMax();
            if (max_aabb.x - 1e-7 > min_collider.x && min_aabb.x + 1e-7 < max_collider.x &&
                max_aabb.z - 1e-7 > min_collider.z && min_aabb.z + 1e-7 < max_collider.z)
            {
                if (movement.y > 0.0 && max_aabb.y - 1e-7 <= min_collider.y)
                {
                    movement.y = std::min(min_collider.y - max_aabb.y, movement.y);
                }
                else if (movement.y < 0.0 && min_aabb.y + 1e-7 >= max_collider.y)
                {
                    movement.y = std::max(max_collider.y - min_aabb.y, movement.y);
                }
            }
        }
        aabb.Translate(Vector3<double>(0.0, movement.y, 0.0));
        min_aabb = aabb.GetMin();
        max_aabb = aabb.GetMax();

        // Collision on X axis before Z
        if (std::abs(movement.x) > std::abs(movement.z))
        {
            // Collisions on X axis
            for (const AABB& collider : colliders)
            {
                if (std::abs(movement.x) < 1.0e-7)
                {
                    movement.x = 0.0;
                    break;
                }
                const Vector3<double> min_collider = collider.GetMin();
                const Vector3<double> max_collider = collider.GetMax();
                if (max_aabb.y - 1e-7 > min_collider.y && min_aabb.y + 1e-7 < max_collider.y &&
                    max_aabb.z - 1e-7 > min_collider.z && min_aabb.z + 1e-7 < max_collider.z)
                {
                    if (movement.x > 0.0 && max_aabb.x - 1e-7 <= min_collider.x)
                    {
                        movement.x = std::min(min_collider.x - max_aabb.x, movement.x);
                    }
                    else if (movement.x < 0.0 && min_aabb.x + 1e-7 >= max_collider.x)
                    {
                        movement.x = std::max(max_collider.x - min_aabb.x, movement.x);
                    }
                }
            }
            aabb.Translate(Vector3<double>(movement.x, 0.0, 0.0));
            min_aabb = aabb.GetMin();
            max_aabb = aabb.GetMax();
        }

        // Collisions on Z axis
        for (const AABB& collider : colliders)
        {
            if (std::abs(movement.z) < 1.0e-7)
            {
                movement.z = 0.0;
                break;
            }
            const Vector3<double> min_collider = collider.GetMin();
            const Vector3<double> max_collider = collider.GetMax();
            if (max_aabb.x - 1e-7 > min_collider.x && min_aabb.x + 1e-7 < max_collider.x &&
                max_aabb.y - 1e-7 > min_collider.y && min_aabb.y + 1e-7 < max_collider.y)
            {
                if (movement.z > 0.0 && max_aabb.z - 1e-7 <= min_collider.z)
                {
                    movement.z = std::min(min_collider.z - max_aabb.z, movement.z);
                }
                else if (movement.z < 0.0 && min_aabb.z + 1e-7 >= max_collider.z)
                {
                    movement.z = std::max(max_collider.z - min_aabb.z, movement.z);
                }
            }
        }
        aabb.Translate(Vector3<double>(0.0, 0.0, movement.z));

        // Collision on X after Z
        if (std::abs(movement.x) <= std::abs(movement.z))
        {
            min_aabb = aabb.GetMin();
            max_aabb = aabb.GetMax();
            // Collisions on X axis
            for (const AABB& collider : colliders)
            {
                if (std::abs(movement.x) < 1.0e-7)
                {
                    movement.x = 0.0;
                    break;
                }
                const Vector3<double> min_collider = collider.GetMin();
                const Vector3<double> max_collider = collider.GetMax();
                if (max_aabb.y - 1e-7 > min_collider.y && min_aabb.y + 1e-7 < max_collider.y &&
                    max_aabb.z - 1e-7 > min_collider.z && min_aabb.z + 1e-7 < max_collider.z)
                {
                    if (movement.x > 0.0 && max_aabb.x - 1e-7 <= min_collider.x)
                    {
                        movement.x = std::min(min_collider.x - max_aabb.x, movement.x);
                    }
                    else if (movement.x < 0.0 && min_aabb.x + 1e-7 >= max_collider.x)
                    {
                        movement.x = std::max(max_collider.x - min_aabb.x, movement.x);
                    }
                }
            }
            aabb.Translate(Vector3<double>(movement.x, 0.0, 0.0));
        }
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
        const double drag = (going_down && has_slow_falling) ? 0.01 : 0.08;

        // Move in water
        if (player->in_water && !player->flying)
        {
            const double init_y = player->position.y;
            double water_slow_down = player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::Sprinting) ? 0.8 : 0.8;
            double inputs_strength = 0.02;

            const Slot boots_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_FEET_ARMOR);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
            double depth_strider_mult = std::min(Utilities::GetEnchantmentLvl(boots_armor.GetNBT(), EnchantmentID::DepthStrider), static_cast<short>(3));
#else
            double depth_strider_mult = std::min(Utilities::GetEnchantmentLvl(boots_armor.GetNBT(), "depth_strider"), static_cast<short>(3));
#endif
            if (!player->on_ground)
            {
                depth_strider_mult *= 0.5;
            }
            if (depth_strider_mult > 0.0)
            {
                water_slow_down += (0.54600006 - water_slow_down) * depth_strider_mult / 3.0;
                inputs_strength += (player->GetAttributeMovementSpeedValueImpl() - inputs_strength) * depth_strider_mult / 3.0;
            }

#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
            for (const auto& effect : player->effects)
            {
                if (effect.type == EntityEffectType::DolphinsGrace && effect.end > std::chrono::steady_clock::now())
                {
                    water_slow_down = 0.96;
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
            player->speed.y *= 0.8;
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
                world->IsFree(player->GetColliderImpl().Inflate(-1e-7) + player->speed + Vector3<double>(0.0, 0.6 - player->position.y + init_y, 0.0), true))
            {
                player->speed.y = 0.3;
            }
        }
        // Move in lava
        else if (player->in_lava && !player->flying)
        {
            const double init_y = player->position.y;
            ApplyInputs(0.02);
            ApplyMovement();
            player->speed *= 0.5;
            player->speed.y -= drag / 4.0;
            // Jump out of lava
            if (player->horizontal_collision &&
                world->IsFree(player->GetColliderImpl().Inflate(-1e-7) + player->speed + Vector3<double>(0.0, 0.6 - player->position.y + init_y, 0.0), true))
            {
                player->speed.y = 0.3;
            }
        }
        // Move with elytra
        else if (player->GetDataSharedFlagsIdImpl(EntitySharedFlagsId::FallFlying))
        {
            // sqrt(front_vector.x² + front_vector.z²) to follow vanilla code
            // it's equal to cos(pitch) (as -90°<=pitch<=90°, cos(pitch) >= 0.0)
            const double cos_pitch = std::cos(player->pitch * PI / 180.0);
            const double cos_pitch_sqr = cos_pitch * cos_pitch;
            const double horizontal_speed = std::sqrt(player->speed.x * player->speed.x + player->speed.z * player->speed.z);

            player->speed.y += drag * (-1.0 + 0.75 * cos_pitch_sqr);

            if (player->speed.y < 0.0 && cos_pitch > 0.0) // cos condition to prevent dividing by 0
            {
                const double delta_speed = -player->speed.y * 0.1 * cos_pitch_sqr;
                player->speed.x += player->front_vector.x * delta_speed / cos_pitch;
                player->speed.y += delta_speed;
                player->speed.z += player->front_vector.z * delta_speed / cos_pitch;
            }
            if (player->pitch < 0.0 && cos_pitch > 0.0) // cos condition to prevent dividing by 0
            {
                // player->front_vector.y == -sin(pitch)
                const double delta_speed = horizontal_speed * player->front_vector.y * 0.04;
                player->speed.x -= player->front_vector.x * delta_speed / cos_pitch;
                player->speed.y += delta_speed * 3.2;
                player->speed.z -= player->front_vector.z * delta_speed / cos_pitch;
            }
            if (cos_pitch > 0.0) // cos condition to prevent dividing by 0
            {
                player->speed.x += (player->front_vector.x / cos_pitch * horizontal_speed - player->speed.x) * 0.1;
                player->speed.z += (player->front_vector.z / cos_pitch * horizontal_speed - player->speed.z) * 0.1;
            }
            player->speed *= Vector3<double>(0.99, 0.98, 0.99);
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
            const Blockstate* below_block = world->GetBlock(Position(
                static_cast<int>(std::floor(player->position.x)),
                static_cast<int>(std::floor(player->position.y - 0.5)),
                static_cast<int>(std::floor(player->position.z))
            ));
            const float friction = below_block == nullptr ? 0.6f : below_block->GetFriction();
            const float inertia = player->on_ground ? friction * 0.91f : 0.91f;

            ApplyInputs(player->on_ground ? (player->GetAttributeMovementSpeedValueImpl() * (0.21600002 / (friction * friction * friction))) : 0.02);
            if (player->on_climbable)
            { // LivingEntity::handleOnClimbable
                player->speed.x = std::clamp(player->speed.x, -0.15, 0.15);
                player->speed.y = std::max(player->speed.y, -0.15);
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
                player->speed.z = std::clamp(player->speed.z, -0.15, 0.15);
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
            player->speed.y *= 0.98;
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

        AABB player_aabb = player->GetColliderImpl();
        if (!player->flying && movement.y <= 0.0 && player->inputs.sneak && player->on_ground)
        { // Player::maybeBackOffFromEdge
            const double step = 0.05;

            while (movement.x != 0.0 && world->IsFree((player_aabb + Vector3<double>(movement.x, -0.6, 0.0)).Inflate(-1e-7), false))
            {
                movement.x = (movement.x < step && movement.x >= -step) ? 0.0 : (movement.x > 0.0 ? (movement.x - step) : (movement.x + step));
            }

            while (movement.z != 0.0 && world->IsFree((player_aabb + Vector3<double>(0.0, -0.6, movement.z)).Inflate(-1e-7), false))
            {
                movement.z = (movement.z < step && movement.z >= -step) ? 0.0 : (movement.z > 0.0 ? (movement.z - step) : (movement.z + step));
            }

            while (movement.x != 0.0 && movement.z != 0.0 && world->IsFree((player_aabb + Vector3<double>(movement.x, -0.6, movement.z)).Inflate(-1e-7), false))
            {
                movement.x = (movement.x < step && movement.x >= -step) ? 0.0 : (movement.x > 0.0 ? (movement.x - step) : (movement.x + step));
                movement.z = (movement.z < step && movement.z >= -step) ? 0.0 : (movement.z > 0.0 ? (movement.z - step) : (movement.z + step));
            }
        }

        const Vector3<double> movement_before_collisions = movement;
        { // Entity::collide
            if (movement.SqrNorm() != 0.0)
            {
                Collisions(movement, player_aabb);
            }
            // TODO: Step up if block height delta is < 0.6
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
        player->on_ground = movement_before_collisions.y < 0.0 && collision_y;

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
                double speed_multiplier = 0.0;
                if (block_below != nullptr)
                {
                    if (block_below->IsSlime())
                    {
                        speed_multiplier = -1.0;
                    }
                    else if (block_below->IsBed())
                    {
                        speed_multiplier = -0.66;
                    }
                }
                player->speed.y = speed_multiplier * player->speed.y;
            }
        }

        CheckInsideBlocks();

        short soul_speed_lvl = 0;
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        // Get SoulSpeed bonus from boots
        const Slot boots_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_FEET_ARMOR);
        soul_speed_lvl = Utilities::GetEnchantmentLvl(boots_armor.GetNBT(), "soul_speed");
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
            const Blockstate* below_block = world->GetBlock(Position(
                static_cast<int>(std::floor(player->position.x)),
                static_cast<int>(std::floor(player->position.y - 0.5)),
                static_cast<int>(std::floor(player->position.z))
            ));
            if (below_block != nullptr && (below_block->IsHoney() || (below_block->IsSoulSand() && soul_speed_lvl == 0)))
            {
                block_speed_factor = 0.4f;
            }
        }
        player->speed.x *= block_speed_factor;
        player->speed.z *= block_speed_factor;
    }

    void PhysicsManager::OnUpdateAbilities() const
    {
        player->UpdateAbilitiesFlagsImpl();
        std::shared_ptr<ServerboundPlayerAbilitiesPacket> abilities_msg = std::make_shared<ServerboundPlayerAbilitiesPacket>();
        abilities_msg->SetFlags(player->abilities_flags);
#if PROTOCOL_VERSION < 727 /* < 1.16 */
        abilities_msg->SetFlyingSpeed(player->flying_speed);
        abilities_msg->SetWalkingSpeed(player->walking_speed);
#endif
        network_manager->Send(abilities_msg);
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
                    {
                        player->stuck_speed_multiplier = Vector3<double>(0.25, 0.05, 0.25);
                    }
                    else if (block->IsBubbleColumn())
                    {
                        const Blockstate* above_block = world->GetBlock(block_pos + Position(0, 1, 0));
                        if (above_block == nullptr || above_block->IsAir())
                        {
                            player->speed.y = block->IsDownBubbleColumn() ? std::max(-0.9, player->speed.y - 0.03) : std::min(1.8, player->speed.y + 0.1);
                        }
                        else
                        {
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
                    {
                        player->stuck_speed_multiplier = Vector3<double>(0.8, 0.75, 0.8);
                    }
                    else if (block->IsPowderSnow())
                    {
                        player->stuck_speed_multiplier = Vector3<double>(0.9, 1.5, 0.9);
                    }
                }
            }
        }
    }

} //Botcraft
