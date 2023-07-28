#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>


#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/World/World.hpp>

Botcraft::Status Init(Botcraft::SimpleBehaviourClient& client);

Botcraft::Status GetNextAction(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status ExecuteAction(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status CheckActionsDone(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status PopAction(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status IsInventoryFull(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status CleanInventory(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status MoveToNextLayer(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status PrepareLayer(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status PlanLayerFluids(Botcraft::SimpleBehaviourClient& client);
Botcraft::Status PlanLayerBlocks(Botcraft::SimpleBehaviourClient& client);

/// @brief Helper function. Get all blocks between start and end positions. Assumes start.y == end.y
/// @param world World to query
/// @param start Start position
/// @param end End position
/// @param layer Y position of the current layer
/// @param solids If true, will gather solid blocks, if false, will gather fluid blocks
/// @param ignored_blocks Block to ignore in the search
/// @return A set of positions respecting the given constraints
std::unordered_set<Botcraft::Position> CollectBlocks(const std::shared_ptr<Botcraft::World> world, const Botcraft::Position& start, const Botcraft::Position& end, const int layer, const bool fluids, const std::unordered_set<std::string>& ignored_blocks);

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
/// @return An ordered vector of blocks to add to the layer to link all components together
std::vector<Botcraft::Position> GetBlocksToAdd(const std::vector<std::unordered_set<Botcraft::Position>>& components, const Botcraft::Position& start_point);

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

/// @brief Get the position in blocks that is the furthest from p
/// @param blocks Blocks to search
/// @param p Comparison point
/// @return The farthest position
Botcraft::Position GetFarthestXZBlock(const std::unordered_set<Botcraft::Position>& blocks, const Botcraft::Position& p);
