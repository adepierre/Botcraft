#include "WorldEaterSubTrees.hpp"
#include "WorldEaterTasks.hpp"

#include <botcraft/AI/Tasks/AllTasks.hpp>

using namespace Botcraft;

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> FullTree()
{
    return Builder<SimpleBehaviourClient>("Full Tree")
        .sequence()
            .tree(IsDeadTree())
            .tree(BaseCampResupplyTree())
            .tree(InitTree())
            .tree(MainTree())
            .tree(CompletionTree())
        .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> IsDeadTree()
{
    return Builder<SimpleBehaviourClient>("Is Dead Tree")
        .selector()
            .leaf(IsAlive)
            .leaf([](SimpleBehaviourClient& c) { c.Respawn(); return Status::Success; })
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
        .leaf(Yield);
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> MainTree()
{
    return Builder<SimpleBehaviourClient>("Main Tree")
        
        .repeater(3) // Repeat the whole loop 3 times so the bot doesn't exit the loop
                     // everytime there is a small pathfinding error, but instead only
                     // when there are 3 failure in a row (probably meaning it is missing
                     // something in its inventory and needs to resupply)
        .repeater("Layer loop", 0).inverter() // repeater(0) + inverter --> repeat until it fails
            .sequence("Layer loop body")
                .leaf("Prepare layer", PrepareLayer)
                .tree(ActionLoopTree())
                //.leaf("Plan layer fluids", PlanLayerFluids)
                //.tree(ActionLoopTree())
                .leaf("Plan layer blocks", PlanLayerBlocks)
                .tree(ActionLoopTree())
                .leaf("Check done", CheckActionsDone)
                .leaf("Move to next layer", MoveToNextLayer)
            .end();
}

std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> ActionLoopTree()
{
    return Builder<SimpleBehaviourClient>("Action Loop Tree")
        .repeater("Action loop", 0).inverter() // repeater(0) + inverter --> repeat until it fails
            .sequence("Action loop body")
                .selector("Eat")
                    .inverter().leaf(IsHungry, 15) // Try to optimize golden carrots eating pattern
                    .leaf(Eat, "minecraft:golden_carrot", true)
                .end()
                .selector("Clean inventory")
                    .inverter().leaf(IsInventoryFull)
                    .leaf(CleanInventory)
                .end()
                .inverter().leaf(IsInventoryFull) // If inventory is still full after cleaning, stop loop and go back to basecamp to empty it
                .leaf("Get next action", GetNextAction)
                .leaf("Execute action", ExecuteAction)
                .leaf("Pop action", PopAction)
            .end();
}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> CompletionTree()
{
    return Builder<SimpleBehaviourClient>("Completion Tree")
        .sequence()
            .leaf("Check done", CheckBlackboardBoolData, "Eater.done")
            .leaf("Go to init pos", [](SimpleBehaviourClient& c) { return GoTo(c, c.GetBlackboard().Get<Position>("Eater.init_pos"), 0, 0); })
            .leaf("Notify", Say, "It's over. It's done.")
            .leaf("Set null tree", [](SimpleBehaviourClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
        .end();
}
