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
#include "botcraft/Utilities/NBTUtilities.hpp"


using namespace ProtocolCraft;

namespace Botcraft
{
    Status DigImpl(BehaviourClient& c, const Position& pos, const bool send_swing, const PlayerDiggingFace face)
    {
        std::shared_ptr<LocalPlayer> local_player = c.GetEntityManager()->GetLocalPlayer();
        Vector3<double> hand_pos;
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            // Get hand (?) pos to check the distance to the center of the target block
            // (unsure about the 1.0 distance, might be from the eyes or somewhere else)
            hand_pos = local_player->GetPosition();
            hand_pos.y += 1.0;
        }

        if (hand_pos.SqrDist(Vector3<double>(0.5, 0.5, 0.5) + pos) > 20.0f)
        {
            // Go in range
            if (GoTo(c, pos, 4) == Status::Failure)
            {
                return Status::Failure;
            }
        }

        Position eyes_block;
        bool is_on_ground;
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            eyes_block = Position(
                static_cast<int>(std::floor(local_player->GetX())),
                static_cast<int>(std::floor(local_player->GetY() + 1.6)),
                static_cast<int>(std::floor(local_player->GetZ()))
            );
            is_on_ground = local_player->GetOnGround();
        }

        std::shared_ptr<World> world = c.GetWorld();
        const Blockstate* blockstate;
        bool is_head_in_fluid = false;
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            const Block* block = world->GetBlock(pos);

            // No block
            if (!block || block->GetBlockstate()->IsAir())
            {
                return Status::Success;
            }
            blockstate = block->GetBlockstate();

            block = world->GetBlock(eyes_block);
            is_head_in_fluid = block && block->GetBlockstate()->IsFluid();
        }

        // Not breakable
        if (blockstate->IsFluid() ||
            (blockstate->GetHardness() < 0.0f && !c.GetCreativeMode()))
        {
            return Status::Failure;
        }

        ToolType current_tool_type = ToolType::None;
        ToolMaterial current_tool_material = ToolMaterial::None;
        unsigned char current_tool_efficiency = 0;
        if (!c.GetCreativeMode())
        {
            std::shared_ptr<InventoryManager> inventory_manager = c.GetInventoryManager();
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());

            // Check if we have aqua affinity
            if (is_head_in_fluid)
            {
                const Slot& head_armor = inventory_manager->GetPlayerInventory()->GetSlot(Window::INVENTORY_HEAD_ARMOR);
                is_head_in_fluid = Utilities::GetEnchantmentLvl(head_armor.GetNBT(), "minecraft:aqua_affinity") == 0;
            }

            // Get tool properties
            const Slot& main_hand = inventory_manager->GetHotbarSelected();
            if (!main_hand.IsEmptySlot())
            {
                const Item* item;
#if PROTOCOL_VERSION < 347 /* < 1.13 */
                item = AssetsManager::getInstance().GetItem({ main_hand.GetBlockID(), static_cast<unsigned char>(main_hand.GetItemDamage()) });
#else
                item = AssetsManager::getInstance().GetItem(main_hand.GetItemID());
#endif
                if (item != nullptr)
                {
                    current_tool_type = item->GetToolType();
                    current_tool_material = item->GetToolMaterial();
                }
                current_tool_efficiency = static_cast<unsigned char>(Utilities::GetEnchantmentLvl(main_hand.GetNBT(), "minecraft:efficiency"));
            }
        }

        unsigned char haste_amplifier = 0;
        unsigned char mining_fatigue_amplifier = 0;
        if (!c.GetCreativeMode())
        {
            std::scoped_lock<std::mutex> entity_manager_lock(c.GetEntityManager()->GetMutex());

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

        const float expected_mining_time_s = c.GetCreativeMode() ? 0.0f : blockstate->GetMiningTimeSeconds(current_tool_type, current_tool_material, current_tool_efficiency, haste_amplifier, mining_fatigue_amplifier, is_on_ground, is_head_in_fluid);
        if (expected_mining_time_s > 60.0f)
        {
            LOG_INFO("Starting an expected " << expected_mining_time_s << " seconds long mining at " << pos << ".A little help?");
        }

        // TODO check line of sight
        // Look at block
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            // TODO look at model AABB center instead of full block center
            local_player->LookAt(Vector3<double>(0.5, 0.5, 0.5) + pos, true);
        }

        std::shared_ptr<NetworkManager> network_manager = c.GetNetworkManager();
        std::shared_ptr<ServerboundPlayerActionPacket> msg_digging = std::make_shared<ServerboundPlayerActionPacket>();
        msg_digging->SetAction(static_cast<int>(PlayerDiggingStatus::StartDigging));
        msg_digging->SetPos(pos.ToNetworkPosition());
        msg_digging->SetDirection(static_cast<int>(face));
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            msg_digging->SetSequence(world->GetNextWorldInteractionSequenceId());
        }
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
        bool finished_sent = c.GetCreativeMode(); // In creative mode we don't need to send a finish digging packet
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
                {
                    std::lock_guard<std::mutex> world_guard(world->GetMutex());
                    msg_finish->SetSequence(world->GetNextWorldInteractionSequenceId());
                }
#endif
                network_manager->Send(msg_finish);

                finished_sent = true;
            }
            if (send_swing && !finished_sent && std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time_send_swing).count() > 250)
            {
                last_time_send_swing = now;
                network_manager->Send(swing_packet);
            }
            {
                std::lock_guard<std::mutex> world_guard(world->GetMutex());
                const Block* block = world->GetBlock(pos);

                if (!block || block->GetBlockstate()->IsAir())
                {
                    return Status::Success;
                }
            }
            c.Yield();
        }

        return Status::Success;
    }

    Status Dig(BehaviourClient& c, const Position& pos, const bool send_swing, const PlayerDiggingFace face)
    {
        constexpr std::array variable_names = {
            "Dig.pos",
            "Dig.send_swing",
            "Dig.face"
        };

        Blackboard& blackboard = c.GetBlackboard();

        blackboard.Set<Position>(variable_names[0], pos);
        blackboard.Set<bool>(variable_names[1], send_swing);
        blackboard.Set<PlayerDiggingFace>(variable_names[2], face);

        return DigImpl(c, pos, send_swing, face);
    }

    Status DigBlackboard(BehaviourClient& c)
    {
        constexpr std::array variable_names = {
            "Dig.pos",
            "Dig.send_swing",
            "Dig.face"
        };

        Blackboard& blackboard = c.GetBlackboard();

        // Mandatory
        const Position& pos = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const bool send_swing = blackboard.Get<bool>(variable_names[1], false);
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[2], PlayerDiggingFace::Up);

        return DigImpl(c, pos, send_swing, face);
    }
}
