#include <iostream>
#include <string>

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/SimpleBehaviourClient.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "botcraft/Utilities/SleepUtilities.hpp"

#include "WorldEaterSubTrees.hpp"
#include "WorldEaterTasks.hpp"

void ShowHelp(const char* argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
        << "Options:\n"
        << "\t-h, --help\tShow this help message\n"
        << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
        << "\t--numbot\tNumber of parallel bot to start, default: 16\n"
        << "\t--numworld\tNumber of shared world used by bots, less worlds saves RAM, but can be slower if shared between too many bots, default: 8\n"
        << "\t--start\t3 ints, offset for the first block, default: -64 -59 832\n"
        << "\t--end\t3 ints, offset for the last block, default: 63 80 959\n"
        << "\t--tempblock\tname of the temp block, must be a full solid block, default: minecraft:basalt\n"
        << std::endl;
}

struct Args
{
    bool help = false;
    std::string address = "127.0.0.1:25565";
    int num_bot = 16;
    int num_world = 8;
    Botcraft::Position start = Botcraft::Position(-64, -59, 832);
    Botcraft::Position end = Botcraft::Position(63, 80, 959);
    std::string temp_block = "minecraft:basalt";

    int return_code = 0;
};

Args ParseCommandLine(int argc, char* argv[]);

std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> CreateTree();

int main(int argc, char* argv[])
{
    try
    {
        // Init logging, log everything >= Info, only to console, no file
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Info);
        Botcraft::Logger::GetInstance().SetFilename("");
        // Add a name to this thread for logging
        Botcraft::Logger::GetInstance().RegisterThread("main");

        Args args;
        if (argc == 1)
        {
            LOG_WARNING("No command arguments. Using default options.");
            ShowHelp(argv[0]);
        }
        else
        {
            args = ParseCommandLine(argc, argv);
            if (args.help)
            {
                ShowHelp(argv[0]);
                return 0;
            }
            if (args.return_code != 0)
            {
                return args.return_code;
            }
        }

        const std::vector<std::string> base_names = {
            "BotAuFeu", "Botager", "Botiron", "BotEnTouche",
            "BotDeVin", "BotAuxRoses", "BotronMinet", "Botmobile",
            "Botman", "Botentiel", "BotDog", "Botrefois",
            "Botomate", "Botaku", "Botaubus", "Bothentique"
        };

        const std::shared_ptr<Botcraft::BehaviourTree<Botcraft::SimpleBehaviourClient>> eater_behaviour_tree = FullTree();

        std::vector<std::shared_ptr<Botcraft::World> > shared_worlds(args.num_world);
        for (int i = 0; i < args.num_world; ++i)
        {
            shared_worlds[i] = std::make_shared<Botcraft::World>(true, false);
        }
        std::vector<std::string> names(args.num_bot);
        std::vector<std::shared_ptr<Botcraft::SimpleBehaviourClient> > clients(args.num_bot);
        for (int i = 0; i < args.num_bot; ++i)
        {
            // Get a unique name for this bot
            names[i] = i < base_names.size() ? base_names[i] : ("Botcraft_" + std::to_string(i / base_names.size()));
            // Create the bot client and connect to the server
            clients[i] = std::make_shared<Botcraft::SimpleBehaviourClient>(i == -1);
            clients[i]->SetSharedWorld(shared_worlds[i % args.num_world]);
            clients[i]->Connect(args.address, names[i], false);
            // Start behaviour thread and set active tree
            clients[i]->StartBehaviour();
            clients[i]->SetBehaviourTree(eater_behaviour_tree, { 
                { "Eater.bot_index" , i },
                { "Eater.num_bot", args.num_bot },
                { "Eater.start_block", args.start },
                { "Eater.end_block", args.end },
                { "Eater.temp_block", args.temp_block }
            });
        }

        // Wait for everything to be loaded
        Botcraft::Utilities::SleepFor(std::chrono::seconds(5));
        while (true)
        {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);

            // Step all clients
            for (const auto& c : clients)
            {
                c->BehaviourStep();
            }

            Botcraft::Utilities::SleepUntil(end);
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

Args ParseCommandLine(int argc, char* argv[])
{
    Args args;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            ShowHelp(argv[0]);
            args.help = true;
            return args;
        }
        else if (arg == "--address")
        {
            if (i + 1 < argc)
            {
                args.address = argv[++i];
            }
            else
            {
                LOG_FATAL("--address requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--numbot")
        {
            if (i + 1 < argc)
            {
                args.num_bot = std::stoi(argv[++i]);
            }
            else
            {
                LOG_FATAL("--numbot requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--numworld")
        {
            if (i + 1 < argc)
            {
                args.num_world = std::stoi(argv[++i]);
            }
            else
            {
                LOG_FATAL("--numworld requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--start")
        {
            if (i + 3 < argc)
            {
                int x = std::stoi(argv[++i]);
                int y = std::stoi(argv[++i]);
                int z = std::stoi(argv[++i]);
                args.start = Botcraft::Position(x, y, z);
            }
            else
            {
                LOG_FATAL("--start requires 3 arguments");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--end")
        {
            if (i + 3 < argc)
            {
                int x = std::stoi(argv[++i]);
                int y = std::stoi(argv[++i]);
                int z = std::stoi(argv[++i]);
                args.end = Botcraft::Position(x, y, z);
            }
            else
            {
                LOG_FATAL("--end requires 3 arguments");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--tempblock")
        {
            if (i + 1 < argc)
            {
                args.temp_block = argv[++i];
            }
            else
            {
                LOG_FATAL("--tempblock requires an argument");
                args.return_code = 1;
                return args;
            }
        }
    }
    return args;
}
