#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"

namespace Botcraft
{
    namespace AI
    {
        /// <summary>
        /// Try to set a given item in the given hand
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <param name="item_name">Item name to place in hand</param>
        /// <param name="hand">Lef or right hand</param>
        /// <returns>Success if the item is now in hand, Failure otherwise</returns>
        Status SetItemInHand(BehaviourClient& client, const std::string& item_name, const Hand hand = Hand::Right);

        /// <summary>
        /// SetItemInHand that reads parameter from the blackboard
        /// </summary>
        /// <param name="client">The client performing the action</param>
        /// <returns>Success if the item is now in hand, Failure otherwise</returns>
        Status SetItemInHandBlackboard(BehaviourClient& client);
    }
}