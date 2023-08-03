#pragma once

#include <botcraft/AI/SimpleBehaviourClient.hpp>

/// @brief Initialize all the blackboard values required to run the tree
/// @param client The client performing the action
/// @return Success if everything was initialize properly, failure otherwise
Botcraft::Status Init(Botcraft::SimpleBehaviourClient& client);

/// @brief Get the next action in the action queue
/// @param client The client performing the action
/// @return Failure if there was no action in the queue, Success otherwise
Botcraft::Status GetNextAction(Botcraft::SimpleBehaviourClient& client);

/// @brief Execute the currently loaded action
/// @param client The client performing the action
/// @return Success if the block was placed/removed, Failure otherwise
Botcraft::Status ExecuteAction(Botcraft::SimpleBehaviourClient& client);

/// @brief Check if the action queue is empty
/// @param client The client performing the action
/// @return Success if the action queue is empty, Failure otherwise
Botcraft::Status CheckActionsDone(Botcraft::SimpleBehaviourClient& client);

/// @brief Remove the first action in the action queue
/// @param client The client performing the action
/// @return Failure if the queue is full, Success otherwise
Botcraft::Status PopAction(Botcraft::SimpleBehaviourClient& client);

/// @brief Check if there is some empty slots in the inventory
/// @param client The client performing the action
/// @return Success if the inventory has no more empty slot, Failure otherwise
Botcraft::Status IsInventoryFull(Botcraft::SimpleBehaviourClient& client);

/// @brief Clean the inventory by throwing on the floor all the undesired items and put some lava on top
/// @param client The client performing the action
/// @return Success if the items were thrown, the lava placed and retrieved, Failure otherwise
Botcraft::Status CleanInventory(Botcraft::SimpleBehaviourClient& client);

/// @brief Decrement current layer index
/// @param client The client performing the action
/// @return Success if not done, Failure if we passed the last layer
Botcraft::Status MoveToNextLayer(Botcraft::SimpleBehaviourClient& client);

/// @brief Plan actions to prepare for the current layer (place ladders)
/// @param client The client performing the action
/// @return Always return Success
Botcraft::Status PrepareLayer(Botcraft::SimpleBehaviourClient& client);

/// @brief Plan actions to fill all fluids from the current layer with solid blocks
/// @param client The client performing the action
/// @return Always return Success
Botcraft::Status PlanLayerFluids(Botcraft::SimpleBehaviourClient& client);

/// @brief Plan actions to all non solid blocks from the current layer with solid ones
/// @param client The client performing the action
/// @return Always return Success
Botcraft::Status PlanLayerNonSolids(Botcraft::SimpleBehaviourClient& client);

/// @brief Plan actions to remove all blocks from the current layer
/// @param client The client performing the action
/// @return Always return Success
Botcraft::Status PlanLayerBlocks(Botcraft::SimpleBehaviourClient& client);

/// @brief Drop all unnecessary items at basecamp
/// @param client The client performing the action
/// @param all_items If true, all items will be thrown (including tools and food)
/// @return Success if nothing bad happened during dropping
Botcraft::Status BaseCampDropItems(Botcraft::SimpleBehaviourClient& client, const bool all_items);

/// @brief Pick all necessary items from basecamp
/// @param client The client performing the action
/// @return Success if nothing bad happened during picking
Botcraft::Status BaseCampPickItems(Botcraft::SimpleBehaviourClient& client);

/// @brief Check if there is a tool of type tool_type in the inventory
/// @param client The client performing the action
/// @param tool_type Tool type to search for
/// @param min_durability Number of time we can use the tool before it breaks
/// @return Success if a tool with >min_durability durability was found, Failure otherwise
Botcraft::Status HasToolInInventory(Botcraft::SimpleBehaviourClient& client, const Botcraft::ToolType tool_type, const int min_durability = 0);
