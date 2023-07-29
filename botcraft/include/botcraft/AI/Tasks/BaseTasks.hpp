#pragma once

#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/AI/Status.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    /// @brief Just call client.Yield(). Can be used to Idle the behaviour.
    /// @param client The client performing the action
    /// @return Always return Success
    Status Yield(BehaviourClient& client);


    /// @brief Ask this client to disconnect from the server by setting should_be_closed to true.
    /// @param client The client performing the action
    /// @return Always return Success
    Status Disconnect(BehaviourClient& client);


    /// @brief Send a message in the game chat
    /// @param client The client performing the action
    /// @param msg The message to send
    /// @return Always return Success
    Status Say(BehaviourClient& client, const std::string& msg);

    /// @brief Same thing as Say, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status SayBlackboard(BehaviourClient& client);


    /// @brief Interact (right click) with the block at the given location. If too far, will try to pathfind toward it.
    /// @param client The client performing the action
    /// @param pos The position of the block
    /// @param face Face on which we want to clik on
    /// @param animation Whether or not we should send an animation to the server (vanilla client does)
    /// @return Failure if couldn't interact (because the client couldn't get close enough for example). Success otherwise.
    Status InteractWithBlock(BehaviourClient& client, const Position& pos, const PlayerDiggingFace face = PlayerDiggingFace::Up, const bool animation = false);

    /// @brief Same thing as InteractWithBlock, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Failure if couldn't interact (because the client couldn't get close enough for example). Success otherwise.
    Status InteractWithBlockBlackboard(BehaviourClient& client);


    /// @brief Check in the blackboard if the bool at key is true
    /// @param client The client performing the action
    /// @param key The key to get the bool from
    /// @return Success if true, failure if false or not found
    Status CheckBlackboardBoolData(BehaviourClient& client, const std::string& key);

    /// @brief Same thing as CheckBlackboardBoolData, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if true, failure if false or not found
    Status CheckBlackboardBoolDataBlackboard(BehaviourClient& client);


    namespace Internal
    {
        template<typename T>
        Status SetBlackboardDataImpl(BehaviourClient& client, const std::string& key, const T& data)
        {
            client.GetBlackboard().Set(key, data);
            return Status::Success;
        }
    }

    /// @brief Set a value in the blackboard
    /// @tparam T Any type
    /// @param client The client performing the action
    /// @param key The key in the blackboard
    /// @param data The data to store
    /// @return Always return success
    template<typename T>
    Status SetBlackboardData(BehaviourClient& client, const std::string& key, const T& data)
    {
        constexpr std::array variable_names = {
            "SetBlackboardData.key",
            "SetBlackboardData.data"
        };

        Blackboard& blackboard = client.GetBlackboard();

        blackboard.Set<std::string>(variable_names[0], key);
        blackboard.Set<T>(variable_names[1], data);

        return Internal::SetBlackboardDataImpl<T>(client, key, data);
    }

    /// @brief Same thing as SetBlackboardData, but reads its parameters from the blackboard
    /// @tparam T Any type
    /// @param client The client performing the action
    /// @return Always return success
    template<typename T>
    Status SetBlackboardDataBlackboard(BehaviourClient& client)
    {
        constexpr std::array variable_names = {
            "SetBlackboardData.key",
            "SetBlackboardData.data"
        };

        Blackboard& blackboard = client.GetBlackboard();

        // Mandatory
        const std::string& key = blackboard.Get<std::string>(variable_names[0]);
        const T& data = blackboard.Get<T>(variable_names[1]);

        return Internal::SetBlackboardDataImpl<T>(client, key, data);
    }


    /// @brief Remove a value from the blackboard if exist
    /// @param client The client performing the action
    /// @param key The key to clear
    /// @return Always return Success
    Status RemoveBlackboardData(BehaviourClient& client, const std::string& key);

    /// @brief Same thing as RemoveBlackboardData, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status RemoveBlackboardDataBlackboard(BehaviourClient& client);


    /// @brief Return success if player food is below a threshold
    /// @param client The client performing the action
    /// @param threshold Threshold under which the player is considered to be hungry
    /// @return Success if player.GetFood() < threshold, Failure otherwise
    Status IsHungry(BehaviourClient& client, const int threshold = 20);

    /// @brief Same thing as IsHungry, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if player.GetFood() < threshold, Failure otherwise
    Status IsHungryBlackboard(BehaviourClient& client);


    /// @brief Copy a blackboard data
    /// @param client The client performing the action
    /// @param src Source blackboard key
    /// @param dst Destination blackboard key
    /// @return Always return Success
    Status CopyBlackboardData(BehaviourClient& client, const std::string& src, const std::string& dst);

    /// @brief Same thing as CopyBlackboardData, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status CopyBlackboardDataBlackboard(BehaviourClient& client);


    /// @brief Return Success if it's night time (sleep is possible)
    /// @param client The client performing the action
    /// @return Success if it's time to sleep, Failure otherwise
    Status IsNightTime(BehaviourClient& client);


    /// @brief Return success if player is alive
    /// @param client The client performing the action
    /// @return Success if player.GetHealth() > 0, Failure otherwise
    Status IsAlive(BehaviourClient& client);
} // namespace Botcraft
