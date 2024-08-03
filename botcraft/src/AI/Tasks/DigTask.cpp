#include "botcraft/AI/Tasks/DigTask.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

#include "botcraft/Game/AssetsManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/Inventory/InventoryManager.hpp"
#include "botcraft/Game/Inventory/Window.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/ItemUtilities.hpp"


using namespace ProtocolCraft;

namespace Botcraft
{
    Status DigImpl(BehaviourClient& c, const Position& pos, const bool send_swing, const PlayerDiggingFace face, const bool allow_pathfinding)
    {
        std::shared_ptr<LocalPlayer> local_player = c.GetLocalPlayer();

        std::shared_ptr<World> world = c.GetWorld();
        const Blockstate* blockstate = world->GetBlock(pos);

        // Not loaded, pathfind toward it
        if (blockstate == nullptr)
        {
            if (!allow_pathfinding || GoTo(c, pos, 4) == Status::Failure)
            {
                return Status::Failure;
            }
            // Update the block after pathfinding
            blockstate = world->GetBlock(pos);
        }

        // This should not happen as the block should be loaded if we successfully moved near it but just in case
        if (blockstate == nullptr)
        {
            LOG_WARNING("Digging target block is nullptr while being close to player");
            return Status::Failure;
        }

        // Nothing to do
        if (blockstate->IsAir())
        {
            return Status::Success;
        }

        const GameType game_mode = local_player->GetGameMode();

        if (blockstate->IsFluid() || // Can't dig fluids
            game_mode == GameType::Adventure || game_mode == GameType::Spectator || // Can't break block in adventure or spectator mode
            (!local_player->GetInstabuild() && blockstate->GetHardness() < 0.0f) // Non breakable blocks without creative instabuild flag
        )
        {
            return Status::Failure;
        }

        // Check if the block is in range
#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        const double range = game_mode == GameType::Creative ? 5.0 : 4.5;
#else
        const double range = static_cast<double>(local_player->GetAttributePlayerBlockInteractionRangeValue());
#endif
        Vector3<double> eye_pos = local_player->GetPosition() + Vector3<double>(0.0, local_player->GetEyeHeight(), 0.0);
        Vector3<double> closest_point_on_block = blockstate->GetClosestPoint(pos, eye_pos);

        int pathfind_tolerance = 4;
        while (pathfind_tolerance > 0 && eye_pos.SqrDist(closest_point_on_block) >= range * range)
        {
            if (!allow_pathfinding || GoTo(c, pos, pathfind_tolerance) == Status::Failure)
            {
                return Status::Failure;
            }
            eye_pos = local_player->GetPosition() + Vector3<double>(0.0, local_player->GetEyeHeight(), 0.0);
            closest_point_on_block = blockstate->GetClosestPoint(pos, eye_pos);
            pathfind_tolerance -= 1;
        }

        // We didn't manage to get close enough
        if (eye_pos.SqrDist(closest_point_on_block) >= range * range)
        {
            return Status::Failure;
        }

        const Position eyes_block = Position(
            static_cast<int>(std::floor(eye_pos.x)),
            static_cast<int>(std::floor(eye_pos.y)),
            static_cast<int>(std::floor(eye_pos.z))
        );
        const bool is_on_ground = local_player->GetOnGround();

        const Blockstate* head_blockstate = world->GetBlock(eyes_block);
        const bool is_head_in_fluid = head_blockstate != nullptr && head_blockstate->IsFluid();

        ToolType current_tool_type = ToolType::None;
        ToolMaterial current_tool_material = ToolMaterial::None;
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        float efficiency_speed_boost = 0.0f;
#else
        const float efficiency_speed_boost = static_cast<float>(local_player->GetAttributePlayerMiningEfficiencyValue());
#endif
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        float submerged_speed_multiplier = 1.0f;
#else
        float submerged_speed_multiplier = is_head_in_fluid ? static_cast<float>(local_player->GetAttributePlayerSubmergedMiningSpeedValue()) : 1.0f;
#endif
        if (!local_player->GetInstabuild())
        {
            std::shared_ptr<InventoryManager> inventory_manager = c.GetInventoryManager();

#if PROTOCOL_VERSION < 767 /* < 1.21 */
            // Check if we have aqua affinity
            if (is_head_in_fluid)
            {
                const Slot head_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HEAD_ARMOR);
                if (Utilities::GetEnchantmentLvl(head_armor, Enchantment::AquaAffinity) == 0)
                {
                    submerged_speed_multiplier = 0.2f;
                }
            }
#endif

            // Get tool properties
            const Slot main_hand = inventory_manager->GetHotbarSelected();
            if (!main_hand.IsEmptySlot())
            {
                const Item* item;
#if PROTOCOL_VERSION < 347 /* < 1.13 */
                item = AssetsManager::getInstance().GetItem(std::pair<int, unsigned char>{ main_hand.GetBlockId(), static_cast<unsigned char>(main_hand.GetItemDamage()) });
#else
                item = AssetsManager::getInstance().GetItem(main_hand.GetItemId());
#endif
                if (item != nullptr)
                {
                    current_tool_type = item->GetToolType();
                    current_tool_material = item->GetToolMaterial();
                }
#if PROTOCOL_VERSION < 767 /* < 1.21 */
                const short efficiency_level = static_cast<unsigned char>(Utilities::GetEnchantmentLvl(main_hand, Enchantment::Efficiency));
                efficiency_speed_boost = (efficiency_level > 0) * 1.0f + efficiency_level * efficiency_level;
#endif
            }
        }

        unsigned char haste_amplifier = 0;
        unsigned char mining_fatigue_amplifier = 0;
        if (!local_player->GetInstabuild())
        {
            for (const auto& effect : local_player->GetEffects())
            {
                if (effect.type == EntityEffectType::Haste && effect.end > std::chrono::steady_clock::now())
                {
                    haste_amplifier = effect.amplifier + 1; // amplifier is 0 for "Effect I"
                    continue;
                }
                if (effect.type == EntityEffectType::MiningFatigue && effect.end > std::chrono::steady_clock::now())
                {
                    mining_fatigue_amplifier = effect.amplifier + 1;
                    continue;
                }
            }
        }

#if PROTOCOL_VERSION < 766 /* < 1.20.5 */
        constexpr float speed_multiplier = 1.0f;
#else
        const float speed_multiplier = static_cast<float>(local_player->GetAttributePlayerBlockBreakSpeedValue());
#endif

        const float expected_mining_time_s =
            local_player->GetInstabuild() ? 0.0f :
            blockstate->GetMiningTimeSeconds(
                current_tool_type,
                current_tool_material,
                efficiency_speed_boost,
                haste_amplifier,
                mining_fatigue_amplifier,
                is_on_ground,
                speed_multiplier * submerged_speed_multiplier
            );
        if (expected_mining_time_s > 60.0f)
        {
            LOG_INFO("Starting an expected " << expected_mining_time_s << " seconds long mining at " << pos << ".A little help?");
        }

        // TODO check line of sight
        // Look at block
        // TODO look at model AABB center instead of full block center
        local_player->LookAt(Vector3<double>(0.5, 0.5, 0.5) + pos, true);

        std::shared_ptr<NetworkManager> network_manager = c.GetNetworkManager();
        std::shared_ptr<ServerboundPlayerActionPacket> msg_digging = std::make_shared<ServerboundPlayerActionPacket>();
        msg_digging->SetAction(static_cast<int>(PlayerDiggingStatus::StartDigging));
        msg_digging->SetPos(pos.ToNetworkPosition());
        msg_digging->SetDirection(static_cast<int>(face));
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        msg_digging->SetSequence(world->GetNextWorldInteractionSequenceId());
#endif
        network_manager->Send(msg_digging);

        std::shared_ptr<ServerboundSwingPacket> swing_packet;
        std::chrono::steady_clock::time_point last_time_send_swing;
        if (send_swing)
        {
           swing_packet = std::make_shared<ServerboundSwingPacket>();
           swing_packet->SetHand(static_cast<int>(Hand::Main));
           network_manager->Send(swing_packet);
           last_time_send_swing = std::chrono::steady_clock::now();
        }

        auto start = std::chrono::steady_clock::now();
        bool finished_sent = local_player->GetInstabuild(); // In creative mode we don't need to send a finish digging packet
        while (true)
        {
            auto now = std::chrono::steady_clock::now();
            long long int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            if (elapsed > 5000 + expected_mining_time_s * 1000.0f)
            {
                LOG_WARNING("Something went wrong waiting block breaking confirmation (Timeout).");
                return Status::Failure;
            }
            if (elapsed >= expected_mining_time_s * 1000.0f
                && !finished_sent)
            {
                std::shared_ptr<ServerboundPlayerActionPacket> msg_finish(new ServerboundPlayerActionPacket);
                msg_finish->SetAction(static_cast<int>(PlayerDiggingStatus::FinishDigging));
                msg_finish->SetPos(pos.ToNetworkPosition());
                msg_finish->SetDirection(static_cast<int>(face));
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
                msg_finish->SetSequence(world->GetNextWorldInteractionSequenceId());
#endif
                network_manager->Send(msg_finish);

                finished_sent = true;
            }
            if (send_swing && !finished_sent && std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time_send_swing).count() > 250)
            {
                last_time_send_swing = now;
                network_manager->Send(swing_packet);
            }
            const Blockstate* block = world->GetBlock(pos);

            if (block == nullptr || block->IsAir())
            {
                return Status::Success;
            }
            c.Yield();
        }

        return Status::Success;
    }

    Status Dig(BehaviourClient& c, const Position& pos, const bool send_swing, const PlayerDiggingFace face, const bool allow_pathfinding)
    {
        constexpr std::array variable_names = {
            "Dig.pos",
            "Dig.send_swing",
            "Dig.face",
            "Dig.allow_pathfinding"
        };

        Blackboard& blackboard = c.GetBlackboard();

        blackboard.Set<Position>(variable_names[0], pos);
        blackboard.Set<bool>(variable_names[1], send_swing);
        blackboard.Set<PlayerDiggingFace>(variable_names[2], face);
        blackboard.Set<bool>(variable_names[3], allow_pathfinding);

        return DigImpl(c, pos, send_swing, face, allow_pathfinding);
    }

    Status DigBlackboard(BehaviourClient& c)
    {
        constexpr std::array variable_names = {
            "Dig.pos",
            "Dig.send_swing",
            "Dig.face",
            "Dig.allow_pathfinding"
        };

        Blackboard& blackboard = c.GetBlackboard();

        // Mandatory
        const Position& pos = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const bool send_swing = blackboard.Get<bool>(variable_names[1], false);
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[2], PlayerDiggingFace::Up);
        const bool allow_pathfinding = blackboard.Get<bool>(variable_names[3], true);

        return DigImpl(c, pos, send_swing, face, allow_pathfinding);
    }
}
