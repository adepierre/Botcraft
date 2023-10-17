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


    Status SayImpl(BehaviourClient& client, const std::string& msg)
    {
        client.SendChatMessage(msg);
        return Status::Success;
    }

    Status Say(BehaviourClient& client, const std::string& msg)
    {
        constexpr std::array variable_names = {
            "Say.msg"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<std::string>(variable_names[0], msg);

        return SayImpl(client, msg);
    }

    Status SayBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "Say.msg"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& msg = blackboard.Get<std::string>(variable_names[0]);

        return SayImpl(client, msg);
    }


    Status InteractWithBlockImpl(BehaviourClient& client, const Position& pos, const PlayerDiggingFace face, const bool animation)
    {
        std::shared_ptr<LocalPlayer> local_player = client.GetEntityManager()->GetLocalPlayer();

        // Compute the distance from the hand? Might be from somewhere else
        const Vector3<double> player_hand_pos = local_player->GetPosition() + Vector3<double>(0.0, 1.0, 0.0);

        if (player_hand_pos.SqrDist(Vector3<double>(0.5, 0.5, 0.5) + pos) > 16.0f)
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
#if PROTOCOL_VERSION > 452 /* > 1.13.2 */
        place_block_msg->SetInside(false);
#endif
        place_block_msg->SetHand(static_cast<int>(Hand::Right));
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        place_block_msg->SetSequence(client.GetWorld()->GetNextWorldInteractionSequenceId());
#endif
        client.GetNetworkManager()->Send(place_block_msg);

        if (animation)
        {
            std::shared_ptr<ProtocolCraft::ServerboundSwingPacket> animation_msg = std::make_shared<ProtocolCraft::ServerboundSwingPacket>();
            animation_msg->SetHand(static_cast<int>(Hand::Right));
            client.GetNetworkManager()->Send(animation_msg);
        }

        LookAt(client, Vector3<double>(0.5) + pos, true);

        return Status::Success;
    }

    Status InteractWithBlock(BehaviourClient& client, const Position& pos, const PlayerDiggingFace face, const bool animation)
    {
        constexpr std::array variable_names = {
            "InteractWithBlock.pos",
            "InteractWithBlock.face",
            "InteractWithBlock.animation"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<Position>(variable_names[0], pos);
        blackboard.Set<PlayerDiggingFace>(variable_names[1], face);
        blackboard.Set<bool>(variable_names[2], animation);

        return InteractWithBlockImpl(client, pos, face, animation);
    }

    Status InteractWithBlockBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "InteractWithBlock.pos",
            "InteractWithBlock.face",
            "InteractWithBlock.animation"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const Position& pos = blackboard.Get<Position>(variable_names[0]);

        // Optional
        const PlayerDiggingFace face = blackboard.Get<PlayerDiggingFace>(variable_names[1], PlayerDiggingFace::Up);
        const bool animation = blackboard.Get(variable_names[2], false);

        return InteractWithBlockImpl(client, pos, face, animation);
    }


    Status CheckBlackboardBoolDataImpl(BehaviourClient& client, const std::string& key)
    {
        return client.GetBlackboard().Get(key, false) ? Status::Success : Status::Failure;
    }

    Status CheckBlackboardBoolData(BehaviourClient& client, const std::string& key)
    {
        constexpr std::array variable_names = {
            "CheckBlackboardBoolData.key"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<std::string>(variable_names[0], key);

        return CheckBlackboardBoolDataImpl(client, key);
    }

    Status CheckBlackboardBoolDataBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "CheckBlackboardBoolData.key"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& key = blackboard.Get<std::string>(variable_names[0]);

        return CheckBlackboardBoolDataImpl(client, key);
    }


    Status RemoveBlackboardDataImpl(BehaviourClient& client, const std::string& key)
    {
        client.GetBlackboard().Erase(key);

        return Status::Success;
    }

    Status RemoveBlackboardData(BehaviourClient& client, const std::string& key)
    {
        constexpr std::array variable_names = {
            "RemoveBlackboardData.key"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<std::string>(variable_names[0], key);

        return RemoveBlackboardDataImpl(client, key);
    }

    Status RemoveBlackboardDataBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "RemoveBlackboardData.key"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& key = blackboard.Get<std::string>(variable_names[0]);

        return RemoveBlackboardDataImpl(client, key);
    }


    Status IsHungryImpl(BehaviourClient& client, const int threshold)
    {
        return client.GetEntityManager()->GetLocalPlayer()->GetFood() < threshold ? Status::Success : Status::Failure;
    }

    Status IsHungry(BehaviourClient& client, const int threshold)
    {
        constexpr std::array variable_names = {
            "IsHungry.threshold"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<int>(variable_names[0], threshold);

        return IsHungryImpl(client, threshold);
    }

    Status IsHungryBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "IsHungry.threshold"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const int threshold = blackboard.Get<int>(variable_names[0]);

        return IsHungryImpl(client, threshold);
    }


    Status CopyBlackboardDataImpl(BehaviourClient& client, const std::string& src, const std::string& dst)
    {
        client.GetBlackboard().Copy(src, dst);

        return Status::Success;
    }

    Status CopyBlackboardData(BehaviourClient& client, const std::string& src, const std::string& dst)
    {
        constexpr std::array variable_names = {
            "CopyBlackboardData.src",
            "CopyBlackboardData.dst"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<std::string>(variable_names[0], src);
        blackboard.Set<std::string>(variable_names[1], dst);

        return CopyBlackboardDataImpl(client, src, dst);
    }

    Status CopyBlackboardDataBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "CopyBlackboardData.src",
            "CopyBlackboardData.dst"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& src = blackboard.Get<std::string>(variable_names[0]);
        const std::string& dst = blackboard.Get<std::string>(variable_names[1]);

        return CopyBlackboardDataImpl(client, src, dst);
    }


    Status IsNightTime(BehaviourClient& client)
    {
        const int day_time = client.GetDayTime();
        return (day_time > 12541 && day_time < 23460) ? Status::Success : Status::Failure;
    }


    Status IsAlive(BehaviourClient& client)
    {
        return client.GetEntityManager()->GetLocalPlayer()->GetHealth() > 0.0f ? Status::Success : Status::Failure;
    }
}
