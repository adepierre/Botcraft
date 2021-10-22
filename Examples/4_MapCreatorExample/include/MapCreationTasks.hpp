#pragma once

#include <string>

#include <botcraft/AI/BehaviourTree.hpp>
#include <botcraft/AI/BehaviourClient.hpp>

/// @brief Check all blocks nearby for chests. Save the found positions in World.ChestsPos
/// @param c The client performing the action
/// @return Always return Success
Botcraft::AI::Status GetAllChestsAround(Botcraft::AI::BehaviourClient& c);

/// @brief Search in nearby chests for a stack of food, put it in the inventory when found.
/// @param c The client performing the action
/// @param food_name The food item name
/// @return Success if the given food is in inventory, Failure otherwise
Botcraft::AI::Status GetSomeFood(Botcraft::AI::BehaviourClient& c, const std::string& food_name);

/// @brief Get list of blocks in the inventory (ignoring the offhand), store it in the blackboard at Inventory.block_list
/// @param c The client performing the action
/// @return Success if at least one block, Failure otherwise
Botcraft::AI::Status GetBlocksAvailableInInventory(Botcraft::AI::BehaviourClient& c);

Botcraft::AI::Status SwapChestsInventory(Botcraft::AI::BehaviourClient& c, const std::string& food_name, const bool take_from_chest);

// Read block list in blackboard at Inventory.block_list and fill in
// NextTask.pos, NextTask.item and NextTask.face
// Return success if a task was found, failure otherwise
Botcraft::AI::Status FindNextTask(Botcraft::AI::BehaviourClient& c);

// Read the blackboard NextTask.XXX values, and perform
// the given task
Botcraft::AI::Status ExecuteNextTask(Botcraft::AI::BehaviourClient& c);

// Check if the whole structure is built
// return success if yes, failure otherwise
Botcraft::AI::Status CheckCompletion(Botcraft::AI::BehaviourClient& c);

Botcraft::AI::Status WarnCantFindFood(Botcraft::AI::BehaviourClient& c);

Botcraft::AI::Status WarnCantEat(Botcraft::AI::BehaviourClient& c);

Botcraft::AI::Status WarnNoBlockInChest(Botcraft::AI::BehaviourClient& c);

Botcraft::AI::Status WarnCompleted(Botcraft::AI::BehaviourClient& c);