#include <iostream>

#include "botcraft/AI/Tasks/DigTask.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"

#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    Status Dig(BehaviourClient& c, const Position& pos, const PlayerDiggingFace face)
    {
        // Can't go close enough
        if (GoTo(c, pos, 4) == Status::Failure)
        {
            return Status::Failure;
        }

        std::shared_ptr<World> world = c.GetWorld();
        std::shared_ptr<Blockstate> blockstate;
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

        // TODO check line of sight

        std::shared_ptr<NetworkManager> network_manager = c.GetNetworkManager();
        std::shared_ptr<ServerboundPlayerActionPacket> msg_digging(new ServerboundPlayerActionPacket);
        msg_digging->SetAction((int)PlayerDiggingStatus::StartDigging);
        msg_digging->SetPos(pos.ToNetworkPosition());
        msg_digging->SetDirection((int)face);
        network_manager->Send(msg_digging);

        //  TODO, check tools and stuff
        const long long int expected_mining_time = 1000.0f * (c.GetCreativeMode() ? 0.0f : 5.0f * blockstate->GetHardness());

        if (expected_mining_time > 60000)
        {
            std::cout << "Starting an expected " << expected_mining_time / 1000.0f << " seconds long mining at " << pos << ". A little help?" << std::endl;
        }

        auto start = std::chrono::system_clock::now();
        bool finished_sent = false;
        while (true)
        {
            long long int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
            if (elapsed > 5000 + expected_mining_time)
            {
                std::cerr << "Something went wrong waiting block breaking confirmation (Timeout)." << std::endl;
                return Status::Failure;
            }
            if (elapsed >= expected_mining_time
                && !finished_sent)
            {
                std::shared_ptr<ServerboundPlayerActionPacket> msg_finish(new ServerboundPlayerActionPacket);
                msg_finish->SetAction((int)PlayerDiggingStatus::FinishDigging);
                msg_finish->SetPos(pos.ToNetworkPosition());
                msg_finish->SetDirection((int)face);
                network_manager->Send(msg_finish);

                finished_sent = true;
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
            "Dig.pos", "Dig.face" };

        Blackboard& blackboard = c.GetBlackboard();

        // Mandatory
        const Position& pos = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[1], PlayerDiggingFace::Top);

        return Dig(c, pos, face);
    }
}