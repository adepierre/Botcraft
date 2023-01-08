#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/AI/Blackboard.hpp"
#include "botcraft/AI/Tasks/EntitiesTasks.hpp"
#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/AI/BehaviourTree.hpp"

#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/entities/Entity.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"

#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    Status InteractEntity(BehaviourClient& client, const int entity_id, const Hand hand, const bool swing)
    {
        std::shared_ptr<EntityManager> entity_manager = client.GetEntityManager();

        std::shared_ptr<Entity> entity;
        {
            std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
            entity = entity_manager->GetEntity(entity_id);
        }

        if (!entity)
        {
            LOG_WARNING("Can't interact with unexisting entity: " << entity_id);
            return Status::Failure;
        }

        std::shared_ptr<LocalPlayer> local_player = entity_manager->GetLocalPlayer();

        Vector3<double> entity_position;
        {
            std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
            entity_position = entity->GetPosition();
        }
        Vector3<double> position;
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            position = local_player->GetPosition();
        }

        while (position.SqrDist(entity_position) > 16.0)
        {
            if (GoTo(client, entity_position, 3, 0) == Status::Failure)
            {
                return Status::Failure;
            }

            entity_position = entity->GetPosition();
            position = local_player->GetPosition();
        }
        
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            local_player->LookAt(entity_position + Vector3<double>(0, entity->GetHeight() / 2.0, 0), true);
        }

        std::shared_ptr<NetworkManager> network_manager = client.GetNetworkManager();
        std::shared_ptr<ServerboundInteractPacket> msg_interact = std::make_shared<ServerboundInteractPacket>();
        msg_interact->SetEntityId(entity_id);
        msg_interact->SetAction(0);
        msg_interact->SetHand(static_cast<int>(hand)); 
#if PROTOCOL_VERSION > 722
        msg_interact->SetUsingSecondaryAction(false);
#endif
        network_manager->Send(msg_interact);
        
        if (swing)
        {
            std::shared_ptr<ServerboundSwingPacket> msg_swing = std::make_shared<ServerboundSwingPacket>();
            msg_swing->SetHand(static_cast<int>(hand));

            network_manager->Send(msg_swing);
        }

        return Status::Success;
    }

    Status InteractEntityBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
            "InteractEntity.entity_id",
            "InteractEntity.hand", 
            "InteractEntity.swing" 
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const int entity_id = blackboard.Get<int>(variable_names[0]);

        // Optional
        const Hand hand = blackboard.Get<Hand>(variable_names[1], Hand::Main);
        const bool swing = blackboard.Get<bool>(variable_names[2], false);

        return InteractEntity(client, entity_id, hand, swing);
    }
}
