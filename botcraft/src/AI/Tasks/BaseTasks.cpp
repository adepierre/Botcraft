#include "botcraft/AI/Tasks/BaseTasks.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Network/NetworkManager.hpp"

namespace Botcraft
{
    Status Yield(BehaviourClient& client)
    {
        client.Yield();

        return Status::Success;
    }

    Status Disconnect(BehaviourClient& client)
    {
        client.SetShouldBeClosed(true);
        return Status::Success;
    }

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

        Vector3<double> player_pos;
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            player_pos = local_player->GetPosition();
        }

        // Compute the distance from the hand? Might be from somewhere else
        player_pos.y += 1.0;

        if (player_pos.SqrDist(Vector3<double>(0.5, 0.5, 0.5) + pos) > 16.0f)
        {
            // Go in range
            if (GoTo(client, pos, 4) == Status::Failure)
            {
                return Status::Failure;
            }
        }

        std::shared_ptr<ProtocolCraft::ServerboundUseItemOnPacket> place_block_msg = std::make_shared<ProtocolCraft::ServerboundUseItemOnPacket>();
        place_block_msg->SetLocation(pos.ToNetworkPosition());
        place_block_msg->SetDirection(static_cast<int>(face));
        switch (face)
        {
        case PlayerDiggingFace::Down:
            place_block_msg->SetCursorPositionX(0.5f);
            place_block_msg->SetCursorPositionY(0.0f);
            place_block_msg->SetCursorPositionZ(0.5f);
            break;
        case PlayerDiggingFace::Up:
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
        place_block_msg->SetHand(static_cast<int>(Hand::Right));
#if PROTOCOL_VERSION > 758
        {
            std::shared_ptr<World> world = client.GetWorld();
            std::lock_guard<std::mutex> world_guard(world->GetMutex());
            place_block_msg->SetSequence(world->GetNextWorldInteractionSequenceId());
        }
#endif
        client.GetNetworkManager()->Send(place_block_msg);

        if (animation)
        {
            std::shared_ptr<ProtocolCraft::ServerboundSwingPacket> animation_msg = std::make_shared<ProtocolCraft::ServerboundSwingPacket>();
            animation_msg->SetHand(static_cast<int>(Hand::Right));
            client.GetNetworkManager()->Send(animation_msg);
        }

        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            local_player->LookAt(Vector3<double>(0.5, 0.5, 0.5) + pos, true);
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
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[1], PlayerDiggingFace::Up);
        const bool animation = blackboard.Get(variable_names[2], false);

        return InteractWithBlock(client, pos, face, animation);
    }

    Status CheckBlackboardBoolData(BehaviourClient& client, const std::string& key)
    {
        return client.GetBlackboard().Get(key, false) ? Status::Success : Status::Failure;
    }

    Status CheckBlackboardBoolDataBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
            "CheckBlackboardBoolData.key" };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& key = blackboard.Get<std::string>(variable_names[0]);

        return CheckBlackboardBoolData(client, key);
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

    Status IsHungry(BehaviourClient& client)
    {
        return client.GetEntityManager()->GetLocalPlayer()->GetFood() < 20.0f ? Status::Success : Status::Failure;
    }

    Status CopyBlackboardData(BehaviourClient& client, const std::string& src, const std::string& dst)
    {
        client.GetBlackboard().Copy(src, dst);

        return Status::Success;
    }

    Status CopyBlackboardDataBlackboard(BehaviourClient& client)
    {
        const std::vector<std::string> variable_names = {
            "CopyBlackboardData.src",
            "CopyBlackboardData.dst"};

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& src = blackboard.Get<std::string>(variable_names[0]);
        const std::string& dst = blackboard.Get<std::string>(variable_names[1]);

        return CopyBlackboardData(client, src, dst);
    }

    Status IsNightTime(BehaviourClient& client)
    {
        const int day_time = client.GetDayTime();
        return (day_time > 12541 && day_time < 23460) ? Status::Success : Status::Failure;
    }
}