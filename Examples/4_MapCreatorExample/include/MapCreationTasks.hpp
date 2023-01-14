#pragma once

#include <string>

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/BehaviourClient.hpp"
#include "botcraft/Game/Vector3.hpp"

/// @brief Check all blocks nearby for chests. Save the found positions in World.ChestsPos
/// @param c The client performing the action
/// @return Always return Success
Botcraft::Status GetAllChestsAround(Botcraft::BehaviourClient& c);

/// @brief Search in nearby chests for a stack of food, put it in the inventory when found.
/// @param c The client performing the action
/// @param food_name The food item name
/// @return Success if the given food is in inventory, Failure otherwise
Botcraft::Status GetSomeFood(Botcraft::BehaviourClient& c, const std::string& food_name);

/// @brief Get list of blocks in the inventory (ignoring the offhand), store it in the blackboard at Inventory.block_list
/// @param c The client performing the action
/// @return Success if at least one block, Failure otherwise
Botcraft::Status GetBlocksAvailableInInventory(Botcraft::BehaviourClient& c);

/// @brief Take or deposit items in nearby chests
/// @param c The client performing the action
/// @param food_name Food item you don't want to take/deposit
/// @param take_from_chest If true, take items from chests, if false deposit items
/// @return Success if all the items were deposited/the inventory is full, Failure otherwise
Botcraft::Status SwapChestsInventory(Botcraft::BehaviourClient& c, const std::string& food_name, const bool take_from_chest);

/// @brief Read block list in blackboard at Inventory.block_list and fill in NextTask.action, NextTask.pos, NextTask.face and NextTask.item
/// @param c The client performing the action
/// @return success if a task was found, failure otherwise
Botcraft::Status FindNextTask(Botcraft::BehaviourClient& c);

/// @brief Read the blackboard NextTask.XXX values, and perform the given task
/// @param c The client performing the action
/// @return Success if the task was correctly executed, failure otherwise
Botcraft::Status ExecuteNextTask(Botcraft::BehaviourClient& c);

/// @brief Check if the whole structure is built, check in the blackboard for CheckCompletion.(print_details, print_errors and full_check) to know if details should be displayed in the console
/// @param c The client performing the action
/// @return Success if the structure is fully built, failure otherwise
Botcraft::Status CheckCompletion(Botcraft::BehaviourClient& c);

/// @brief Write a message in the console, prefixed with bot name
/// @param c The client performing the action
/// @param msg The string to write in the console
/// @return Always return success
Botcraft::Status WarnConsole(Botcraft::BehaviourClient& c, const std::string& msg);

/// @brief Loads a NBT file (unzipped) and store the target structure in the blackboard of the given client
/// @param c The client performing the action
/// @param path The path to the unzipped NBT file
/// @param offset Starting offset position to build the structure
/// @param temp_block Minecraft item/block name used as scafholding block in the NBT
/// @param log_info Whether or not the loading information should be logged
/// @return Success if the file was correctly loaded, failure otherwise
Botcraft::Status LoadNBT(Botcraft::BehaviourClient& c, const std::string& path, const Botcraft::Position& offset, const std::string& temp_block, const bool log_info);
