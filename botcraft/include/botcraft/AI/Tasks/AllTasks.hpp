#pragma once

#include "botcraft/AI/Tasks/BaseTasks.hpp"
#include "botcraft/AI/Tasks/PathfindingTask.hpp"

/// <summary>
/// Base functions you can use as tree leaf 
/// in any Botcraft behaviour tree. When a function
/// has some arguments, there are two versions. The first,
/// with arguments, can be used with a lambda or std::bind
/// to force arguments. It will **NOT** use the blackboard
/// 
/// FunctionNameBlackboard functions on the other hand
/// read data directly from the blackboard, with the 
/// naming convention: FunctionName.param_name, and then
/// call their blackboardless counterpart with the retrieved
/// data.
/// </summary>