#include "WorldEaterSubTrees.hpp"
#include "WorldEaterTasks.hpp"

#include <botcraft/AI/Tasks/AllTasks.hpp>

using namespace Botcraft;

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> FullTree()
{
    return Builder<SimpleBehaviourClient>("Full Tree")
        .sequence()
            .tree(IsDeadTree())
            .tree(InitTree())
            .tree(BaseCampResupplyTree())
            .tree(MainTree())
            // If we exited main tree because of an error, clean inventory before going back to basecamp
            .leaf("Clean inventory", CleanInventory)
            .tree(CompletionTree())
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> IsDeadTree()
{
    return Builder<SimpleBehaviourClient>("Is Dead Tree")
        .selector()
            .leaf(IsAlive)
            .sequence()
                .leaf(Say, "I might have died...")
                .leaf([](SimpleBehaviourClient& c) { LOG_WARNING("I died... And now I respawn!"); return Status::Success; })
                .leaf([](SimpleBehaviourClient& c) { c.Respawn(); return Status::Success; })
            .end()
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
            .leaf("Has sword", HasToolInInventory, ToolType::Sword, 2)
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
    return Builder<SimpleBehaviourClient>("Main Tree")
        .sequence()
            // Count the number of failed action performed in a row, reset after every successful action
            .leaf("Reset failure counter", SetBlackboardData<int>, "Eater.failed_loop", 0)
            // Repeat the whole loop until it fails.
            // The last leaf makes sure it fails only
            // if the internal loop failed three times in
            // a row.
            .repeater(0).inverter()
                .sequence()
                    .repeater("Layer loop", 0).inverter() // repeater(0) + inverter --> repeat until it fails
                        .selector()
                            .sequence("Layer loop body")
                                .leaf("Prepare layer", PrepareLayer)
                                .tree(ActionLoopTree())
                                .leaf("Check done", CheckActionsDone)
                                .leaf("Plan layer fluids", PlanLayerFluids)
                                .tree(ActionLoopTree())
                                .leaf("Check done", CheckActionsDone)
                                .leaf("Plan layer non solids", PlanLayerNonSolids)
                                .tree(ActionLoopTree())
                                .leaf("Check done", CheckActionsDone)
                                .leaf("Plan layer blocks", PlanLayerBlocks)
                                .tree(ActionLoopTree())
                                .leaf("Check done", CheckActionsDone)
                                .leaf("Move to next layer", MoveToNextLayer)
                            .end()
                            // if previous sequence didn't succeed, sleep for ~1 second and increment failure counter
                            .sequence()
                                .repeater(100).leaf("Sleep", Yield)
                                .leaf("Increment failure counter", [](SimpleBehaviourClient& c) { c.GetBlackboard().Set<int>("Eater.failed_loop", c.GetBlackboard().Get<int>("Eater.failed_loop") + 1); return Status::Failure; })
                            .end()
                        .end()
                    .leaf("Exit loop if 3 failures", [](SimpleBehaviourClient& c) { return c.GetBlackboard().Get<int>("Eater.failed_loop") == 3 ? Status::Failure : Status::Success; })
                .end()
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> ActionLoopTree()
{
    return Builder<SimpleBehaviourClient>("Action Loop Tree")
        .repeater("Action loop", 0).inverter() // repeater(0) + inverter --> repeat until it fails
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
            .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> CompletionTree()
{
    return Builder<SimpleBehaviourClient>("Completion Tree")
        .sequence()
            .leaf("Check done", CheckBlackboardBoolData, "Eater.done")
            .leaf("Drop all items", BaseCampDropItems, true)
            .leaf("Go to init pos", [](SimpleBehaviourClient& c) { return GoTo(c, c.GetBlackboard().Get<Position>("Eater.init_pos"), 0, 0); })
            .leaf("Notify", Say, "It's over. It's done.")
            .leaf("Set null tree", [](SimpleBehaviourClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
        .end();
}
