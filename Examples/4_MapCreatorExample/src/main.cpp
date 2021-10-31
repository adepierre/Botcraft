#include <iostream>
#include <string>

#include <botcraft/Game/World/World.hpp>
#include <botcraft/AI/BehaviourTree.hpp>
#include <botcraft/AI/Tasks/AllTasks.hpp>
#include <botcraft/AI/SimpleBehaviourClient.hpp>

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

using namespace Botcraft::AI;

std::shared_ptr<BehaviourTree<SimpleBehaviourClient>> GenerateMapArtCreatorTree()
{
    const std::string food_name = "minecraft:golden_carrot";
    
    auto completion_tree = Builder<SimpleBehaviourClient>()
        .succeeder()
            .sequence()
                .leaf(CheckCompletion)
                .leaf(WarnConsole, "Task fully completed!")
                .repeater(0)
                    .inverter()
                        .leaf(Yield)
                    .end()
                .end()
            .end()
        .end()
        .build();
    
    auto disconnect_subtree = Builder<SimpleBehaviourClient>()
        .sequence()
            .leaf(Disconnect)
            .repeater(0)
                .inverter()
                    .leaf(Yield)
                .end()
            .end()
        .end()
        .build();

    auto eat_subtree = Builder<SimpleBehaviourClient>()
        .selector()
            // If hungry
            .inverter()
                .leaf(IsHungry)
            .end()
            // Get some food, then eat
            .sequence()
                .selector()
                    .leaf(SetItemInHand, food_name, Botcraft::Hand::Left)
                    .sequence()
                        .leaf(GetSomeFood, food_name)
                        .leaf(SetItemInHand, food_name, Botcraft::Hand::Left)
                    .end()
                    .leaf(WarnConsole, "Can't find food anywhere!")
                .end()
                .selector()
                    .leaf(Eat, food_name, true)
                    .inverter()
                        .leaf(WarnConsole, "Can't eat!")
                    .end()
                    // If we are here, hungry and can't eat --> Disconnect
                    .tree(disconnect_subtree)
                .end()
            .end()
        .end()
        .build();

    auto getinventory_tree = Builder<SimpleBehaviourClient>()
        // List all blocks in the inventory
        .selector()
            .leaf(GetBlocksAvailableInInventory)
            // If no block found, get some in neighbouring chests
            .sequence()
                .leaf(SwapChestsInventory, food_name, true)
                .selector()
                    .leaf(GetBlocksAvailableInInventory)
                    .inverter()
                        .leaf(WarnConsole, "No more block in chests, I will stop here.")
                    .end()
                    .tree(disconnect_subtree)
                .end()
            .end()
        .end()
        .build();

    auto placeblock_tree = Builder<SimpleBehaviourClient>()
        .selector()
            // Try to perform a task 5 times
            .decorator<RepeatUntilSuccess<SimpleBehaviourClient>>(5)
                .selector()
                    .sequence()
                        .leaf(FindNextTask)
                        .leaf(ExecuteNextTask)
                    .end()
                    // If the previous task failed, sleep for ~1 second
                    // before retrying to get an action
                    .inverter()
                        .repeater(100)
                            .leaf(Yield)
                        .end()
                    .end()
                .end()
            .end()
            // If failed 5 times, put all blocks in chests to
            // randomize available blocks for next time
            .leaf(SwapChestsInventory, food_name, false)
        .end()
        .build();

    return Builder<SimpleBehaviourClient>()
        // Main sequence of actions
        .sequence()
            .tree(completion_tree)
            .tree(eat_subtree)
            .tree(getinventory_tree)
            .tree(placeblock_tree)
        .end()
        .build();
}

int main(int argc, char* argv[])
{
    try
    {
        std::string address = "127.0.0.1:25565";
        int num_bot = 5;
        int num_world = 1;
        std::string nbt_file = "";
        Botcraft::Position offset(0, 0, 0);
        std::string temp_block = "minecraft:slime_block";

        std::vector<std::string> base_names = { "BotAuFeu", "Botager", "Botiron", "BotEnTouche", "BotDeVin", "BotAuxRoses", "BotronMinet", "Botmobile", "Botman", "Botentiel" };

        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
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
                    std::cerr << "--address requires an argument" << std::endl;
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
                    std::cerr << "--numbot requires an argument" << std::endl;
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
                    std::cerr << "--numworld requires an argument" << std::endl;
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
                    std::cerr << "--nbt requires an argument" << std::endl;
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
                    std::cerr << "--offset requires 3 arguments" << std::endl;
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
                    std::cerr << "--tempblock requires an argument" << std::endl;
                    return 1;
                }
            }
        }

        auto map_art_behaviour_tree = GenerateMapArtCreatorTree();

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
            LoadNBT(*(clients[i]), nbt_file, offset, temp_block, i == 0);
            clients[i]->Connect(address, names[i], "");
            clients[i]->StartBehaviour();
            clients[i]->SetBehaviourTree(map_art_behaviour_tree);
        }

        std::map<int, std::chrono::system_clock::time_point> restart_time;

        while (true)
        {
            for (int i = 0; i < clients.size(); ++i)
            {
                if (clients[i]->GetShouldBeClosed())
                {
                    clients[i]->Disconnect();
                    clients[i].reset();
                    clients[i] = std::make_shared<SimpleBehaviourClient>(false);
                    clients[i]->SetSharedWorld(shared_worlds[i % num_world]);
                    clients[i]->SetAutoRespawn(true);
                    LoadNBT(*(clients[i]), nbt_file, offset, temp_block, i == 0);
                    clients[i]->Connect(address, names[i], "");

                    // Restart client[i] in 10 seconds
                    std::cout << names[i] << " has been stopped. Scheduling a restart in 10 seconds..." << std::endl;
                    restart_time[i] = std::chrono::system_clock::now() + std::chrono::seconds(10);
                }
            }

            auto now = std::chrono::system_clock::now();
            for (auto it = restart_time.begin(); it != restart_time.end(); )
            {
                if (now > it->second)
                {
                    std::cout << "Restarting " << names[it->first] << "..." << std::endl;
                    clients[it->first]->StartBehaviour();
                    clients[it->first]->SetBehaviourTree(map_art_behaviour_tree);
                    restart_time.erase(it++);
                }
                else
                {
                    ++it;
                }
            }

            std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
            std::chrono::system_clock::time_point end = start + std::chrono::milliseconds(10);

            for (int i = 0; i < clients.size(); ++i)
            {
                clients[i]->BehaviourStep();
            }

            std::this_thread::sleep_until(end);
        }

        return 0;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception\n";
        return 2;
    }

}