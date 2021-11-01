#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{
    /// <summary>
    /// Swap two slots in a given container
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <param name="container_id">Container ID</param>
    /// <param name="first_slot">First slot index</param>
    /// <param name="second_slot">Second slot index</param>
    /// <returns>Success if the two slots have been correctly swapped, Failure otherwise</returns>
    Status SwapItemsInContainer(BehaviourClient& client, const short container_id, const short first_slot, const short second_slot);

    /// <summary>
    /// SwapItemsInContainer that reads parameter from the blackboard
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <returns>Success if the two slots have been correctly swapped, Failure otherwise</returns>
    Status SwapItemsInContainerBlackboard(BehaviourClient& client);

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

    /// <summary>
    /// Try to place the item at given pos. If too far, will try
    /// to pathfind toward the position first.
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <param name="item_name">The item to place</param>
    /// <param name="pos">The location where we want to place the block</param>
    /// <param name="face">The face on which the block is placed</param>
    /// <param name="wait_confirmation">If true, waits for the server to send the new block in pos</param>
    /// <returns>Success if placement attempt was made and confirmed by the server if wait_confirmation is true, Failure otherwise</returns>
    Status PlaceBlock(BehaviourClient& client, const std::string& item_name, const Position& pos, const PlayerDiggingFace face = PlayerDiggingFace::Top, const bool wait_confirmation = false);

    /// <summary>
    /// PlaceBlock that reads parameter from the blackboard
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <returns>Success if placement attempt was made and confirmed by the server if wait_confirmation is true, Failure otherwise</returns>
    Status PlaceBlockBlackboard(BehaviourClient& client);

    /// <summary>
    /// Search for food item in the inventory and eat it
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <param name="food_name">The item to eat</param>
    /// <param name="wait_confirmation">If true, waits for the eaten stack to be reduced by 1 before returning Success</param>
    /// <returns>Success if the item was eaten, Failure otherwise</returns>
    Status Eat(BehaviourClient& client, const std::string& food_name, const bool wait_confirmation = false);

    /// <summary>
    /// Eat that reads parameter from the blackboard
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <returns>Success if the item was eaten, Failure otherwise</returns>
    Status EatBlackboard(BehaviourClient& client);

    /// <summary>
    /// Open a container at a given position
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <param name="pos">The position of the container</param>
    /// <returns>Success if the container is opened, Failure otherwise</returns>
    Status OpenContainer(BehaviourClient& client, const Position& pos);

    /// <summary>
    /// OpenContainer that reads parameter from the blackboard
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <returns>Success if the container is opened, Failure otherwise</returns>
    Status OpenContainerBlackboard(BehaviourClient& client);

    /// <summary>
    /// Close an opened container
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <param name="container_id">The id of the container to close</param>
    /// <returns>Success</returns>
    Status CloseContainer(BehaviourClient& client, const short container_id);

    /// <summary>
    /// CloseContainer that reads parameter from the blackboard
    /// </summary>
    /// <param name="client">The client performing the action</param>
    /// <returns>Success</returns>
    Status CloseContainerBlackboard(BehaviourClient& client);
}
