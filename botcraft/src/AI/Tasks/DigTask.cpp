#include "botcraft/AI/Tasks/DigTask.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"

#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    Status Dig(BehaviourClient& c, const Position& pos, const bool send_swing, const PlayerDiggingFace face, const float mining_time)
    {
        std::shared_ptr<LocalPlayer> local_player = c.GetEntityManager()->GetLocalPlayer();
        Vector3<double> player_pos;
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            player_pos = local_player->GetPosition();
        }

        // Compute the distance from the hand? Might be from somewhere else
        player_pos.y += 1.0;

        if (player_pos.SqrDist(Vector3<double>(0.5, 0.5, 0.5) + pos) > 20.0f)
        {
            // Go in range
            if (GoTo(c, pos, 4) == Status::Failure)
            {
                return Status::Failure;
            }
        }

        std::shared_ptr<World> world = c.GetWorld();
        const Blockstate* blockstate;
        {
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            const Block* block = world->GetBlock(pos);

            // No block
            if (!block || block->GetBlockstate()->IsAir())
            {
                return Status::Success;
            }
            blockstate = block->GetBlockstate();
        }

        // Not breakable
        if (blockstate->IsFluid() ||
            blockstate->GetHardness() == -1.0f)
        {
            return Status::Failure;
        }

        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            // TODO look at model AABB center
            local_player->LookAt(Vector3<double>(0.5, 0.5, 0.5) + pos, true);
        }

        // TODO check line of sight

        std::shared_ptr<NetworkManager> network_manager = c.GetNetworkManager();
        std::shared_ptr<ServerboundPlayerActionPacket> msg_digging = std::make_shared<ServerboundPlayerActionPacket>();
        msg_digging->SetAction((int)PlayerDiggingStatus::StartDigging);
        msg_digging->SetPos(pos.ToNetworkPosition());
        msg_digging->SetDirection((int)face);
#if PROTOCOL_VERSION > 758
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
           swing_packet->SetHand(static_cast<int>(Hand::Right));
           network_manager->Send(swing_packet);
           last_time_send_swing = std::chrono::steady_clock::now();
        }

        // TODO, check tools and stuff
        const long long int expected_mining_time = 1000.0f * (mining_time < 0.0f ? (c.GetCreativeMode() ? 0.0f : 5.0f * blockstate->GetHardness()) : mining_time);

        if (expected_mining_time > 60000)
        {
            LOG_INFO("Starting an expected " << expected_mining_time / 1000.0f << " seconds long mining at " << pos << ".A little help?");
        }

        auto start = std::chrono::steady_clock::now();
        bool finished_sent = false;
        while (true)
        {
            auto now = std::chrono::steady_clock::now();
            long long int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            if (elapsed > 5000 + expected_mining_time)
            {
                LOG_WARNING("Something went wrong waiting block breaking confirmation (Timeout).");
                return Status::Failure;
            }
            if (elapsed >= expected_mining_time
                && !finished_sent)
            {
                std::shared_ptr<ServerboundPlayerActionPacket> msg_finish(new ServerboundPlayerActionPacket);
                msg_finish->SetAction((int)PlayerDiggingStatus::FinishDigging);
                msg_finish->SetPos(pos.ToNetworkPosition());
                msg_finish->SetDirection((int)face);
#if PROTOCOL_VERSION > 758
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

    Status DigBlackboard(BehaviourClient& c)
    {
        const std::vector<std::string> variable_names = {
            "Dig.pos",
            "Dig.send_swing",
            "Dig.face",
            "Dig.mining_time"
        };

        Blackboard& blackboard = c.GetBlackboard();

        // Mandatory
        const Position& pos = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const bool send_swing = blackboard.Get<bool>(variable_names[1], false);
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[2], PlayerDiggingFace::Up);
        const float mining_time = blackboard.Get<float>(variable_names[3], -1.0f);

        return Dig(c, pos, send_swing, face, mining_time);
    }
}