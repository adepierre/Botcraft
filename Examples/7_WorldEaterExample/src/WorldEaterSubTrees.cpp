#include "WorldEaterSubTrees.hpp"
#include "WorldEaterTasks.hpp"

#include <botcraft/AI/Tasks/AllTasks.hpp>

using namespace Botcraft;

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> FullTree()
{
    std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> go_to_top_ladder = GoToTopLadderTree();
    return Builder<SimpleBehaviourClient>("Full Tree")
        .sequence()
            .tree(InitTree())
            .tree(BaseCampResupplyTree())
            // Make sure we go near the ladder position first,
            // to avoid pathfinding through the other bots
            // working area
            .tree(go_to_top_ladder)
            .tree(MainTree())
            .tree(go_to_top_ladder)
            // If we exited main tree because of an error, clean inventory before going back to basecamp
            .leaf("Clean inventory", CleanInventory)
            .tree(CompletionTree())
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> InitTree()
{
    return Builder<SimpleBehaviourClient>("Init Tree")
        .selector()
            .leaf("Is init?", CheckBlackboardBoolData, "Eater.init")
            .selector()
                .leaf("Init", Init)
                // If init failed, stop the behaviour
                .leaf("Stop behaviour", [](SimpleBehaviourClient& c) { c.SetBehaviourTree(nullptr); c.Yield(); return Status::Success; })
            .end()
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> BaseCampResupplyTree()
{
    return Builder<SimpleBehaviourClient>("Basecamp Resupply Tree")
        .sequence()
            .leaf("Drop items", BaseCampDropItems, false)
            .leaf("Pick items", BaseCampPickItems)
            .leaf("Has lava", HasItemInInventory, "minecraft:lava_bucket", 1)
            .leaf("Has shears", HasToolInInventory, ToolType::Shears, 2)
            .leaf("Has hoe", HasToolInInventory, ToolType::Hoe, 2)
            .leaf("Has shovel", HasToolInInventory, ToolType::Shovel, 2)
            .leaf("Has axe", HasToolInInventory, ToolType::Axe, 2)
            .leaf("Has food", HasItemInInventory, "minecraft:golden_carrot", 64)
            .leaf("Has ladder", HasItemInInventory, "minecraft:ladder", 64)
            .leaf(CopyBlackboardData, "Eater.temp_block", "HasItemInInventory.item_name")
            .leaf(SetBlackboardData<int>, "HasItemInInventory.quantity", 5*64)
            .leaf("Has temp block", HasItemInInventoryBlackboard)
            .leaf("Has pickaxe", HasToolInInventory, ToolType::Pickaxe, 2)
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> MainTree()
{
    std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> action_loop_tree = ActionLoopTree();
    return Builder<SimpleBehaviourClient>("Main Tree")
        .repeater("Layer loop", 0).inverter() // repeater(0) + inverter --> repeat until it fails
            .sequence("Layer loop body")
                .leaf("Validate current layer", ValidateCurrentLayer)
                .leaf("Prepare layer", PrepareLayer)
                .tree(action_loop_tree)
                // CheckActionsDone will exit this loop early if all the
                // actions weren't done during the internal loop
                .leaf("Check done", CheckActionsDone)
                .leaf("Plan layer non walkable", PlanLayerNonWalkable)
                .tree(action_loop_tree)
                .leaf("Check done", CheckActionsDone)
                .leaf("Plan layer fluids", PlanLayerFluids)
                .tree(action_loop_tree)
                .leaf("Check done", CheckActionsDone)
                .leaf("Plan layer blocks", PlanLayerBlocks)
                .tree(action_loop_tree)
                .leaf("Check done", CheckActionsDone)
                .leaf("Move to next layer", MoveToNextLayer)
            .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> ActionLoopTree()
{
    return Builder<SimpleBehaviourClient>("Action Loop Tree")
        .sequence()
            // Count the number of failed action performed in a row, reset after every successful action
            .leaf("Reset failure counter", SetBlackboardData<int>, "Eater.failed_loop", 0)
            // Repeat the whole loop until it fails.
            // The last leaf makes sure it fails only
            // if the internal loop failed three times in
            // a row.
            .repeater(0).inverter()
                .sequence()
                    // Exit early if action queue is empty
                    .inverter().leaf("Check done", CheckActionsDone)
                    .selector()
                        // Try to perform next action
                        .sequence("Action loop body")
                            .selector("Eat")
                                .inverter().leaf(IsHungry, 15) // Try to optimize golden carrots eating pattern with 15 threshold
                                .leaf(Eat, "minecraft:golden_carrot", true)
                            .end()
                            .selector("Clean inventory")
                                .inverter().leaf(IsInventoryFull)
                                .leaf(CleanInventory)
                            .end()
                            .inverter().leaf(IsInventoryFull) // If inventory is still full after cleaning, stop loop and go back to basecamp to empty it
                            .leaf("Get next action", GetNextAction)
                            .leaf("Execute action", ExecuteAction)
                            // If the action succeeded, reset failure counter to 0
                            .leaf("Reset failure counter", SetBlackboardData<int>, "Eater.failed_loop", 0)
                            .leaf("Pop action", PopAction)
                        .end()
                        // If action failed, wait for ~1 sec and increment failure counter
                        .sequence()
                            .repeater(100).leaf("Sleep", Yield)
                            .leaf("Increment failure counter", [](SimpleBehaviourClient& c) { c.GetBlackboard().Set<int>("Eater.failed_loop", c.GetBlackboard().Get<int>("Eater.failed_loop") + 1); return Status::Success; })
                        .end()
                    .end()
                    // If failure counter is equal to 3, break out of the loop
                    .leaf("Exit loop if 3 failures", [](SimpleBehaviourClient& c) { return c.GetBlackboard().Get<int>("Eater.failed_loop") == 3 ? Status::Failure : Status::Success; })
                .end()
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> CompletionTree()
{
    return Builder<SimpleBehaviourClient>("Completion Tree")
        .sequence()
            .leaf("Check done", CheckBlackboardBoolData, "Eater.done")
            .leaf("Drop all items", BaseCampDropItems, true)
            .leaf("Go to out pos", [](SimpleBehaviourClient& c) { LOG_INFO("Go to out position" << c.GetBlackboard().Get<Position>("Eater.out_position")); return GoTo(c, c.GetBlackboard().Get<Position>("Eater.out_position") + Position(0, 1, 0), 0, 0); })
            .leaf("Notify", Say, "It's over. It's done.")
            .leaf("Set should be closed", [](SimpleBehaviourClient& c) { c.SetShouldBeClosed(true); return Status::Success; })
            .leaf("Set null tree", [](SimpleBehaviourClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
        .end();
}

std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> GoToTopLadderTree()
{
    return Builder<SimpleBehaviourClient>("Go To Top Ladder Tree")
        .sequence()
            .leaf(CopyBlackboardData, "Eater.ladder", "GoTo.goal")
            .leaf(SetBlackboardData<int>, "GoTo.dist_tolerance", 4)
            .leaf(SetBlackboardData<int>, "GoTo.min_end_dist", 1)
            .leaf(SetBlackboardData<int>, "GoTo.min_end_dist_xz", 1)
            .leaf("Go to ladder", GoToBlackboard)
        .end();
}
