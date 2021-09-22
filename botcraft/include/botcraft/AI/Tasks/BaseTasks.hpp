#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    namespace AI
    {
        /// <summary>
        /// Say something in the chat
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <param name="msg">The message to send</param>
        /// <returns>Success</returns>
        Status Say(BehaviourClient& client, const std::string& msg);

        /// <summary>
        /// Say version that reads parameters from the blackboard
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <returns>Success</returns>
        Status SayBlackboard(BehaviourClient& client);

        /// <summary>
        /// Interact (right click) with the block at the given location. Must be in range.
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <param name="pos">The position of the block</param>
        /// <param name="face">Face on which we want to clik on</param>
        /// <param name="animation">Whether or not we should send an animation to the server (vanilla client does)</param>
        /// <returns></returns>
        Status InteractWithBlock(BehaviourClient& client, const Position& pos, const PlayerDiggingFace face = PlayerDiggingFace::Top, const bool animation = false);

        /// <summary>
        /// InteractWithBlock version that reads parameters from the blackboard
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <returns>Failure if couldn't interact (because the client is too far for example). Success otherwise.</returns>
        Status InteractWithBlockBlackboard(BehaviourClient& client);

        /// <summary>
        /// Set a value in the blackboard.
        /// </summary>
        /// <typeparam name="T">Any type</typeparam>
        /// <param name="client">The client performing the action</param>
        /// <param name="key">The key in the blackboard</param>
        /// <param name="data">The data to set to key</param>
        /// <returns>Success</returns>
        template<typename T>
        Status SetBlackboardData(BehaviourClient& client, const std::string& key, const T& data)
        {
            client.GetBlackboard().Set(key, data);
            return Status::Success;
        }

        /// <summary>
        /// SetBlackboardData that reads parameters from the blackboard
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <returns>Success</returns>
        template<typename T>
        Status SetBlackboardDataBlackboard(BehaviourClient& client)
        {
            const std::vector<std::string> variable_names = {
                "SetBlackboardData.key" , "SetBlackboardData.data" };

            Blackboard& blackboard = client.GetBlackboard();

            // Mandatory
            const std::string& key = blackboard.Get<std::string>(variable_names[0]);

            // Optional
            const T& data = blackboard.Get<T>(variable_names[1]);

            return SetBlackboardData(client, key, data);
        }

        /// <summary>
        /// Remove a value from the blackboard if exist.
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <param name="key">The key in the blackboard</param>
        /// <returns>Sucess</returns>
        Status RemoveBlackboardData(BehaviourClient& client, const std::string& key);

        /// <summary>
        /// RemoveBlackboardData that reads parameter from the blackboard
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <returns>Success</returns>
        Status RemoveBlackboardDataBlackboard(BehaviourClient& client);

    } // namespace AI
} // namespace Botcraft