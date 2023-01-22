#include <iostream>
#include <string>

#include "botcraft/Game/World/World.hpp"
#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/Tasks/AllTasks.hpp"
#include "botcraft/AI/SimpleBehaviourClient.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"

#include "CustomBehaviourTree.hpp"
#include "MapCreationTasks.hpp"

void ShowHelp(const char* argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
        << "Options:\n"
        << "\t-h, --help\tShow this help message\n"
        << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
        << "\t--numbot\tNumber of parallel bot to start, default: 5\n"
        << "\t--numworld\tNumber of parallel world to use, less worlds saves RAM, but slows the bots down, default: 1\n"
        << "\t--nbt\tnbt filename to load, default: empty\n"
        << "\t--offset\t3 ints, offset for the first block, default: 0 0 0\n"
        << "\t--tempblock\tname of the scafholding block, default: minecraft:slime_block\n"
        << std::endl;
}

using namespace Botcraft;

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> GenerateMapArtCreatorTree(const std::string& food_name,
    const std::string& nbt_path, const Botcraft::Position& offset, const std::string& temp_block, const bool detailed);

int main(int argc, char* argv[])
{
    try
    {
        // Init logging, log everything >= Info, only to console, no file
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Info);
        Botcraft::Logger::GetInstance().SetFilename("");
        // Add a name to this thread for logging
        Botcraft::Logger::GetInstance().RegisterThread("main");

        std::string address = "127.0.0.1:25565";
        int num_bot = 5;
        int num_world = 1;
        std::string nbt_file = "";
        Botcraft::Position offset(0, 0, 0);
        std::string temp_block = "minecraft:slime_block";

        std::vector<std::string> base_names = { "BotAuFeu", "Botager", "Botiron", "BotEnTouche", "BotDeVin", "BotAuxRoses", "BotronMinet", "Botmobile", "Botman", "Botentiel" };

        if (argc == 1)
        {
            LOG_WARNING("No command arguments. Using default options.");
            ShowHelp(argv[0]);
        }

        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg == "-h" || arg == "--help")
            {
                ShowHelp(argv[0]);
                return 0;
            }
            else if (arg == "--address")
            {
                if (i + 1 < argc)
                {
                    address = argv[++i];
                }
                else
                {
                    LOG_FATAL("--address requires an argument");
                    return 1;
                }
            }
            else if (arg == "--numbot")
            {
                if (i + 1 < argc)
                {
                    num_bot = std::stoi(argv[++i]);
                }
                else
                {
                    LOG_FATAL("--numbot requires an argument");
                    return 1;
                }
            }
            else if (arg == "--numworld")
            {
                if (i + 1 < argc)
                {
                    num_world = std::stoi(argv[++i]);
                }
                else
                {
                    LOG_FATAL("--numworld requires an argument");
                    return 1;
                }
            }
            else if (arg == "--nbt")
            {
                if (i + 1 < argc)
                {
                    nbt_file = argv[++i];
                }
                else
                {
                    LOG_FATAL("--nbt requires an argument");
                    return 1;
                }
            }
            else if (arg == "--offset")
            {
                if (i + 3 < argc)
                {
                    int x = std::stoi(argv[++i]);
                    int y = std::stoi(argv[++i]);
                    int z = std::stoi(argv[++i]);
                    offset = Botcraft::Position(x, y, z);
                }
                else
                {
                    LOG_FATAL("--offset requires 3 arguments");
                    return 1;
                }
            }
            else if (arg == "--tempblock")
            {
                if (i + 1 < argc)
                {
                    temp_block = argv[++i];
                }
                else
                {
                    LOG_FATAL("--tempblock requires an argument");
                    return 1;
                }
            }
        }

        auto map_art_detailed_behaviour_tree = GenerateMapArtCreatorTree("minecraft:golden_carrot", nbt_file, offset, temp_block, true);
        auto map_art_behaviour_tree = GenerateMapArtCreatorTree("minecraft:golden_carrot", nbt_file, offset, temp_block, false);

        std::vector<std::shared_ptr<Botcraft::World> > shared_worlds(num_world);
        for (int i = 0; i < num_world; i++)
        {
            shared_worlds[i] = std::shared_ptr<Botcraft::World>(new Botcraft::World(true, false));
        }
        std::vector<std::string> names(num_bot);
        std::vector<std::shared_ptr<SimpleBehaviourClient> > clients(num_bot);
        for (int i = 0; i < num_bot; ++i)
        {
            names[i] = base_names[i] + (i < base_names.size() ? "" : ("_" + std::to_string(i / base_names.size())));
            clients[i] = std::make_shared<SimpleBehaviourClient>(false);
            clients[i]->SetSharedWorld(shared_worlds[i % num_world]);
            clients[i]->SetAutoRespawn(true);
            clients[i]->Connect(address, names[i], false);
            clients[i]->StartBehaviour();
            clients[i]->SetBehaviourTree(i == 0 ? map_art_detailed_behaviour_tree : map_art_behaviour_tree);
        }

        std::map<int, std::chrono::steady_clock::time_point> restart_time;

        std::chrono::steady_clock::time_point next_time_display = std::chrono::steady_clock::now() + std::chrono::minutes(2);

        while (true)
        {
            // Check if any client should be closed, and schedule the restart 10 seconds later
            for (int i = 0; i < clients.size(); ++i)
            {
                if (clients[i]->GetShouldBeClosed())
                {
                    clients[i]->Disconnect();
                    clients[i].reset();
                    clients[i] = std::make_shared<SimpleBehaviourClient>(false);
                    clients[i]->SetSharedWorld(shared_worlds[i % num_world]);
                    clients[i]->SetAutoRespawn(true);
                    clients[i]->Connect(address, names[i], false);

                    // Restart client[i] in 10 seconds
                    LOG_INFO(names[i] << " has been stopped. Scheduling a restart in 10 seconds...");
                    restart_time[i] = std::chrono::steady_clock::now() + std::chrono::seconds(10);
                }
            }

            // Check if any scheduled restart should happen
            auto now = std::chrono::steady_clock::now();
            for (auto it = restart_time.begin(); it != restart_time.end(); )
            {
                if (now > it->second)
                {
                    LOG_INFO("Restarting " << names[it->first] << "...");
                    clients[it->first]->StartBehaviour();
                    clients[it->first]->SetBehaviourTree(map_art_behaviour_tree);
                    restart_time.erase(it++);
                }
                else
                {
                    ++it;
                }
            }

            // Check if we should display progress details
            if (now > next_time_display)
            {
                Blackboard& blackboard = clients[0]->GetBlackboard();

                // Set blackboard values to true so the next check completion will print the details
                blackboard.Set<bool>("CheckCompletion.print_details", true);
                blackboard.Set<bool>("CheckCompletion.print_errors", true);
                blackboard.Set<bool>("CheckCompletion.full_check", true);

                next_time_display += std::chrono::minutes(2);
            }

            std::chrono::steady_clock::time_point end = now + std::chrono::milliseconds(10);

            for (int i = 0; i < clients.size(); ++i)
            {
                clients[i]->BehaviourStep();
            }

            SleepUntil(end);
        }

        return 0;
    }
    catch (std::exception &e)
    {
        LOG_FATAL("Exception: " << e.what());
        return 1;
    }
    catch (...)
    {
        LOG_FATAL("Unknown exception");
        return 2;
    }

}

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> GenerateMapArtCreatorTree(const std::string& food_name,
    const std::string& nbt_path, const Botcraft::Position& offset, const std::string& temp_block, const bool detailed)
{
    auto loading_tree = Builder<SimpleBehaviourClient>("loading")
        .selector()
            // Check if the structure is already loaded
            .leaf(CheckBlackboardBoolData, "Structure.loaded")
            // Otherwise load it
            .leaf("load NBT file", LoadNBT, nbt_path, offset, temp_block, detailed)
        .end()
        .build();

    auto completion_tree = Builder<SimpleBehaviourClient>("completion check")
        .succeeder().sequence()
            .leaf("check completion", CheckCompletion)
            .leaf(WarnConsole, "Task fully completed!")
            .repeater(0).inverter().leaf(Yield)
        .end()
        .build();
    
    auto disconnect_subtree = Builder<SimpleBehaviourClient>("disconnect")
        .sequence()
            .leaf("disconnect", Disconnect)
            .repeater(0).inverter().leaf(Yield)
        .end()
        .build();

    auto eat_subtree = Builder<SimpleBehaviourClient>("eat")
        .selector()
            // If hungry
            .inverter().leaf(IsHungry)
            // Get some food, then eat
            .sequence()
                .selector()
                    .leaf(SetItemInHand, food_name, Botcraft::Hand::Left)
                    .sequence()
                        .leaf("get food", GetSomeFood, food_name)
                        .leaf(SetItemInHand, food_name, Botcraft::Hand::Left)
                    .end()
                    .leaf(WarnConsole, "Can't find food anywhere!")
                .end()
                .selector()
                    .leaf(Eat, food_name, true)
                    .inverter().leaf(WarnConsole, "Can't eat!")
                    // If we are here, hungry and can't eat --> Disconnect
                    .tree(disconnect_subtree)
                .end()
            .end()
        .end()
        .build();

    auto getinventory_tree = Builder<SimpleBehaviourClient>("list blocks in inventory")
        // List all blocks in the inventory
        .selector()
            .leaf("get block in inventory", GetBlocksAvailableInInventory)
            // If no block found, get some in neighbouring chests
            .sequence()
                .selector()
                    .leaf("get some blocks from chests", SwapChestsInventory, food_name, true)
                    .inverter().leaf(WarnConsole, "Can't swap with chests, will wait before retrying.")
                    // If the previous task failed, maybe chests were just
                    // not loaded yet, sleep for ~1 second
                    .inverter().repeater(100).leaf(Yield)
                .end()
                .selector()
                    .leaf("get block in inventory after swapping", GetBlocksAvailableInInventory)
                    .inverter().leaf(WarnConsole, "No more block in chests, I will stop here.")
                    .tree(disconnect_subtree)
                .end()
            .end()
        .end()
        .build();

    auto placeblock_tree = Builder<SimpleBehaviourClient>("place block")
        .selector()
            // Try to perform a task 5 times
            .decorator<RepeatUntilSuccess<SimpleBehaviourClient>>(5).selector()
                .sequence()
                    .leaf("find next task", FindNextTask)
                    .leaf("execute next task", ExecuteNextTask)
                .end()
                // If the previous task failed, sleep for ~1 second
                // before retrying to get an action
                .inverter().repeater(100).leaf(Yield)
            .end()
            // If failed 5 times, put all blocks in chests to
            // randomize available blocks for next time
            .leaf("dump all items in chest", SwapChestsInventory, food_name, false)
        .end()
        .build();

    return Builder<SimpleBehaviourClient>("main")
        // Main sequence of actions
        .sequence()
            .tree(loading_tree)
            .tree(completion_tree)
            .tree(eat_subtree)
            .tree(getinventory_tree)
            .tree(placeblock_tree)
        .end()
        .build();
}
