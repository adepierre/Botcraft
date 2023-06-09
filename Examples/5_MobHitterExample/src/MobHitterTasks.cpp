#include "MobHitterTasks.hpp"

#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Network/NetworkManager.hpp"

using namespace Botcraft;
using namespace ProtocolCraft;

Status HitCloseHostiles(BehaviourClient& c)
{
    std::shared_ptr<EntityManager> entity_manager = c.GetEntityManager();
    std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();
    std::shared_ptr<NetworkManager> network_manager = c.GetNetworkManager();
    Blackboard& blackboard = c.GetBlackboard();
    
    const NotifyOnEndUseRef<std::map<int, std::chrono::steady_clock::time_point>> last_time_hit_wrapper = blackboard.GetRef("Entities.LastTimeHit", std::map<int, std::chrono::steady_clock::time_point>());
    std::map<int, std::chrono::steady_clock::time_point>& last_time_hit = last_time_hit_wrapper.ref();

    Vector3<double> player_pos;
    {
        std::lock_guard<std::mutex> player_guard(local_player->GetMutex());
        player_pos = local_player->GetPosition();
    }

    auto now = std::chrono::steady_clock::now();
    {
        std::lock_guard<std::mutex> entities_guard(entity_manager->GetMutex());
        for (auto& it : entity_manager->GetEntities())
        {
            if (it.second->IsMonster() && (it.second->GetPosition()- player_pos).SqrNorm() < 16.0)
            {
                auto time = last_time_hit.find(it.first);
                if (time != last_time_hit.end() &&
                    std::chrono::duration_cast<std::chrono::milliseconds>(now - time->second).count() < 500)
                {
                    continue;
                }

                last_time_hit[it.first] = now;

                {
                    std::lock_guard<std::mutex> player_guard(local_player->GetMutex());
                    local_player->LookAt(it.second->GetPosition());
                }

                std::shared_ptr<ServerboundInteractPacket> msg = std::make_shared<ServerboundInteractPacket>();
                msg->SetAction(1);
                msg->SetEntityId(it.first);
#if PROTOCOL_VERSION > 722
                msg->SetUsingSecondaryAction(false);
#endif
                std::shared_ptr<ServerboundSwingPacket> msg_swing = std::make_shared<ServerboundSwingPacket>();
                msg_swing->SetHand(0);

                network_manager->Send(msg);
                network_manager->Send(msg_swing);
            }
        }
    }

    return Status::Success;
}

Status CleanLastTimeHit(BehaviourClient& c)
{
    const NotifyOnEndUseRef<std::map<int, std::chrono::steady_clock::time_point>> last_time_hit_wrapper = c.GetBlackboard().GetRef("Entities.LastTimeHit", std::map<int, std::chrono::steady_clock::time_point>());
    std::map<int, std::chrono::steady_clock::time_point>& last_time_hit = last_time_hit_wrapper.ref();

    auto now = std::chrono::steady_clock::now();
    for (auto it = last_time_hit.begin(); it != last_time_hit.end();)
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(now - it->second).count() > 10)
        {
            it = last_time_hit.erase(it);
        }
        else
        {
            ++it;
        }
    }

    return Status::Success;
}
