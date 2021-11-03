#pragma once

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/Game/Vector3.hpp"

namespace Botcraft
{    
    /// @brief Swap two slots in a given container
    /// @param client The client performing the action
    /// @param container_id Container ID
    /// @param first_slot First slot index
    /// @param second_slot Second slot index
    /// @return Success if the two slots have been correctly swapped, Failure otherwise
    Status SwapItemsInContainer(BehaviourClient& client, const short container_id, const short first_slot, const short second_slot);

    /// @brief Same thing as SwapItemsInContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the two slots have been correctly swapped, Failure otherwise
    Status SwapItemsInContainerBlackboard(BehaviourClient& client);

    /// @brief Try to set a given item in the given hand
    /// @param client The client performing the action
    /// @param item_name Item name to place in hand
    /// @param hand Left or right hand
    /// @return Success if the item is now in hand, Failure otherwise
    Status SetItemInHand(BehaviourClient& client, const std::string& item_name, const Hand hand = Hand::Right);

    /// @brief Same thing as SetItemInHand, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the item is now in hand, Failure otherwise
    Status SetItemInHandBlackboard(BehaviourClient& client);

    /// @brief Try to place the item at given pos. If too far, will try
    /// to pathfind toward the position first.
    /// @param client The client performing the action
    /// @param item_name The item to place
    /// @param pos The location where we want to place the block
    /// @param face The face on which the block is placed
    /// @param wait_confirmation If true, waits for the server to send the new block in pos
    /// @return Success if placement attempt was made (and confirmed by the server if wait_confirmation is true), Failure otherwise
    Status PlaceBlock(BehaviourClient& client, const std::string& item_name, const Position& pos, const PlayerDiggingFace face = PlayerDiggingFace::Top, const bool wait_confirmation = false);

    /// @brief Same thing as PlaceBlock, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if placement attempt was made (and confirmed by the server if wait_confirmation is true), Failure otherwise
    Status PlaceBlockBlackboard(BehaviourClient& client);

    /// @brief Search for food item in the inventory and eat it
    /// @param client The client performing the action
    /// @param food_name The item to eat
    /// @param wait_confirmation If true, waits for the eaten stack to be reduced by 1 before returning Success
    /// @return 
    Status Eat(BehaviourClient& client, const std::string& food_name, const bool wait_confirmation = false);

    /// @brief Same thing as Eat, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the item was eaten (and confirmed if wait_confirmation is true), Failure otherwise
    Status EatBlackboard(BehaviourClient& client);

    /// @brief Open a container at a given position
    /// @param client The client performing the action
    /// @param pos The position of the container
    /// @return Success if the container is opened, Failure otherwise
    Status OpenContainer(BehaviourClient& client, const Position& pos);

    /// @brief Same thing as OpenContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Success if the container is opened, Failure otherwise
    Status OpenContainerBlackboard(BehaviourClient& client);

    /// @brief Close an opened container
    /// @param client The client performing the action
    /// @param container_id The id of the container to close
    /// @return Always return Success
    Status CloseContainer(BehaviourClient& client, const short container_id);

    /// @brief Same thing as CloseContainer, but reads its parameters from the blackboard
    /// @param client The client performing the action
    /// @return Always return Success
    Status CloseContainerBlackboard(BehaviourClient& client);
}
