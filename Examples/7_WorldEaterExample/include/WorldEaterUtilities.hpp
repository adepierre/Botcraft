#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>


#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/AI/SimpleBehaviourClient.hpp>

/// @brief Split a string into subcomponents
/// @param s String to split
/// @param delimiter Delimiter character
/// @return An unordered set of substrings in s
std::unordered_set<std::string> SplitString(const std::string& s, const char delimiter);

/// @brief Find all interest points in the surroundings and load them in the blackboard
/// @param client The client performing the action
/// @return True if everything was found, false otherwise
bool IdentifyBaseCampLayout(Botcraft::SimpleBehaviourClient& client);

/// @brief Helper function. Get all blocks between start and end positions. Assumes start.y == end.y
/// @param world World to query
/// @param start Start position
/// @param end End position
/// @param layer Y position of the current layer
/// @param fluids If true, will gather fluid blocks
/// @param solids If true, will gather solid blocks
/// @return A set of positions respecting the given constraints
std::unordered_set<Botcraft::Position> CollectBlocks(const std::shared_ptr<Botcraft::World> world, const Botcraft::Position& start, const Botcraft::Position& end, const int layer, const bool fluids, const bool solids);

/// @brief Helper function. Group a set of positions on the same layer in connected components
/// @param start Start block of the layer
/// @param end End block of the layer
/// @param start_point Starting point on the layer (typically the access ladder)
/// @param client Client used to check for pathfinding reachability
/// @param positions Positions to process
/// @param additional_neighbours If set, will be filled with additional neighbours for each components (i.e. blocks that are not directly next to each other but still reachable from each other by pathfinding algorithm)
/// @return A vector of connected components
std::vector<std::unordered_set<Botcraft::Position>> GroupBlocksInComponents(const Botcraft::Position& start, const Botcraft::Position& end, const Botcraft::Position& start_point, const Botcraft::BehaviourClient& client, const std::unordered_set<Botcraft::Position>& positions, std::unordered_map<Botcraft::Position, std::unordered_set<Botcraft::Position>>* additional_neighbours);

/// @brief Given a set of connected components, get a list of blocks to add to link them together
/// @param components The components (i.e. group of blocks) to link together
/// @param start_point Starting point on the layer (typically the access ladder)
/// @param bound_min Min bound of the working area (to be sure we don't add block outside of it)
/// @param bound_max Max bound of the working area (to be sure we don't add block outside of it)
/// @return An ordered vector of blocks to add to the layer to link all components together
std::vector<Botcraft::Position> GetBlocksToAdd(const std::vector<std::unordered_set<Botcraft::Position>>& components, const Botcraft::Position& start_point, const Botcraft::Position& bound_min, const Botcraft::Position& bound_max);

/// @brief Merge sets of positions into one set
/// @param components Connected components positions
/// @param additional_blocks Additional blocks to link the components together
/// @return One set of all sets merged
std::unordered_set<Botcraft::Position> FlattenComponentsAndAdditionalBlocks(const std::vector<std::unordered_set<Botcraft::Position>>& components, const std::vector<Botcraft::Position>& additional_blocks);

/// @brief Order all given positions such as we go one by one until we reach exit_block without ever "cutting the branch we are sitting on"
/// @param blocks All block to order. Intentional copy as we need to remove the blocks one by one once processed
/// @param start_block Block to start with
/// @param orientation Orientation of the work area compared to the entry point (North, South, East or West), used to "optimize" the ordering along one axis rather than the other and minimize travel time
/// @param additional_neighbours Potential additional neighbours for some blocks (i.e. blocks that are not direct neighbours but that we can reach by pathfinding)
/// @return Ordered positions to follow, should end with exit_block
std::vector<Botcraft::Position> ComputeBlockOrder(std::unordered_set<Botcraft::Position> blocks, const Botcraft::Position& start_block, const Botcraft::Direction orientation, const std::unordered_map<Botcraft::Position, std::unordered_set<Botcraft::Position>>& additional_neighbours = {});
