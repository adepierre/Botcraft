#pragma once

/// @brief Base functions you can use as tree leaf 
/// in any Botcraft behaviour tree. When a function
/// has some arguments, there are three versions:
/// 1. XXXImpl is the actual task implementation. It
/// is only defined in the cpp file and not available
/// outside of it
/// 2. XXX is the main way to call the task. It will
/// call XXXImpl under the hood after registering its
/// values in the blackboard for easier debugging
/// 3. XXXBlackboard is the same as XXX but will read
/// all parameters from the blackboard (or get default
/// ones)
/// All blackboard variables are saved with the naming
/// convention: FunctionName.param_name

#include "botcraft/AI/Tasks/BaseTasks.hpp"
#include "botcraft/AI/Tasks/DigTask.hpp"
#include "botcraft/AI/Tasks/EntitiesTasks.hpp"
#include "botcraft/AI/Tasks/InventoryTasks.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"
