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

    const Vector3<double> player_pos = local_player->GetPosition();

    auto now = std::chrono::steady_clock::now();
    {
        auto entities = entity_manager->GetEntities();
        for (const auto& [id, entity] : *entities)
        {
            if (entity->IsMonster() && (entity->GetPosition()- player_pos).SqrNorm() < 16.0)
            {
                auto time = last_time_hit.find(id);
                if (time != last_time_hit.end() &&
                    std::chrono::duration_cast<std::chrono::milliseconds>(now - time->second).count() < 500)
                {
                    continue;
                }

                last_time_hit[id] = now;

                local_player->LookAt(entity->GetPosition());

#if PROTOCOL_VERSION < 775 /* < 26.1 */
                std::shared_ptr<ServerboundInteractPacket> packet_attack = std::make_shared<ServerboundInteractPacket>();
                packet_attack->SetAction(1);
                packet_attack->SetEntityId(id);
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
                packet_attack->SetUsingSecondaryAction(false);
#endif
#else
                std::shared_ptr<ServerboundAttackPacket> packet_attack = std::make_shared<ServerboundAttackPacket>();
                packet_attack->SetEntityId(id);
#endif
                network_manager->Send(packet_attack);

#if PROTOCOL_VERSION < 777 /* < 26.3 */
                std::shared_ptr<ServerboundSwingPacket> packet_swing = std::make_shared<ServerboundSwingPacket>();
                packet_swing->SetHand(0);
                network_manager->Send(packet_swing);
#endif
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
