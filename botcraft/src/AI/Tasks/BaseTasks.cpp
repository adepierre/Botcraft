#include "botcraft/AI/Tasks/BaseTasks.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Network/NetworkManager.hpp"
#include "botcraft/Game/World/Blockstate.hpp"


#include <iostream>

namespace Botcraft
{
    namespace AI
    {
        Status Say(BehaviourClient& client, const std::string& msg)
        {
            client.SendChatMessage(msg);
            return Status::Success;
        }

        Status SayBlackboard(BehaviourClient& client)
        {
            const std::vector<std::string> variable_names = {
                "Say.msg" };

            Blackboard& blackboard = client.GetBlackboard();

            // Mandatory
            const std::string& msg = blackboard.Get<std::string>(variable_names[0]);

            return Say(client, msg);
        }

        Status InteractWithBlock(BehaviourClient& client, const Position& pos, const PlayerDiggingFace face, const bool animation)
        {
            std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();
            const Vector3<double> dist(std::floor(local_player->GetPosition().x) - pos.x, std::floor(local_player->GetPosition().y) - pos.y, std::floor(local_player->GetPosition().z) - pos.z);
            double distance = std::sqrt(dist.dot(dist));
            if (distance > 5.0f)
            {
                std::cout << "I am asked to interact at " << pos << " but I'm affraid that's out of my range (" << distance << "m)." << std::endl;

                return Status::Failure;
            }

            std::shared_ptr<ProtocolCraft::ServerboundUseItemOnPacket> place_block_msg(new ProtocolCraft::ServerboundUseItemOnPacket);
            place_block_msg->SetLocation(pos.ToNetworkPosition());
            place_block_msg->SetDirection((int)face);
            switch (face)
            {
            case PlayerDiggingFace::Bottom:
                place_block_msg->SetCursorPositionX(0.5f);
                place_block_msg->SetCursorPositionY(0.0f);
                place_block_msg->SetCursorPositionZ(0.5f);
                break;
            case PlayerDiggingFace::Top:
                place_block_msg->SetCursorPositionX(0.5f);
                place_block_msg->SetCursorPositionY(1.0f);
                place_block_msg->SetCursorPositionZ(0.5f);
                break;
            case PlayerDiggingFace::North:
                place_block_msg->SetCursorPositionX(0.5f);
                place_block_msg->SetCursorPositionY(0.5f);
                place_block_msg->SetCursorPositionZ(0.0f);
                break;
            case PlayerDiggingFace::South:
                place_block_msg->SetCursorPositionX(0.5f);
                place_block_msg->SetCursorPositionY(0.5f);
                place_block_msg->SetCursorPositionZ(1.0f);
                break;
            case PlayerDiggingFace::East:
                place_block_msg->SetCursorPositionX(1.0f);
                place_block_msg->SetCursorPositionY(0.5f);
                place_block_msg->SetCursorPositionZ(0.5f);
                break;
            case PlayerDiggingFace::West:
                place_block_msg->SetCursorPositionX(0.0f);
                place_block_msg->SetCursorPositionY(0.5f);
                place_block_msg->SetCursorPositionZ(0.5f);
                break;
            default:
                break;
            }
#if PROTOCOL_VERSION > 452
            place_block_msg->SetInside(false);
#endif
            place_block_msg->SetHand((int)Hand::Right);
            client.GetNetworkManager()->Send(place_block_msg);

            if (animation)
            {
                std::shared_ptr<ProtocolCraft::ServerboundSwingPacket> animation_msg(new ProtocolCraft::ServerboundSwingPacket);
                animation_msg->SetHand((int)Hand::Right);
                client.GetNetworkManager()->Send(animation_msg);
            }

            return Status::Success;
        }

        Status InteractWithBlockBlackboard(BehaviourClient& client)
        {
            const std::vector<std::string> variable_names = { 
                "InteractWithBlock.pos" , "InteractWithBlock.face", "InteractWithBlock.animation" };

            Blackboard& blackboard = client.GetBlackboard();

            // Mandatory
            const Position& pos = blackboard.Get<Position>(variable_names[0]);

            // Optional
            const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[1], PlayerDiggingFace::Top);
            const bool animation = blackboard.Get(variable_names[2], false);

            return InteractWithBlock(client, pos, face, animation);
        }

        Status RemoveBlackboardData(BehaviourClient& client, const std::string& key)
        {
            client.GetBlackboard().Erase(key);

            return Status::Success;
        }

        Status RemoveBlackboardDataBlackboard(BehaviourClient& client)
        {
            const std::vector<std::string> variable_names = {
                "RemoveBlackboardData.key" };

            Blackboard& blackboard = client.GetBlackboard();

            // Mandatory
            const std::string& key = blackboard.Get<std::string>(variable_names[0]);

            return RemoveBlackboardData(client, key);
        }
    }
}