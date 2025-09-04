#include <iostream>
#include <string>

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/Utilities/Logger.hpp>
#include <botcraft/Utilities/SleepUtilities.hpp>

#include "WorldEaterSubTrees.hpp"
#include "WorldEaterClient.hpp"

void ShowHelp(const char* argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
        << "Options:\n"
        << "\t-h, --help\tShow this help message\n"
        << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
        << "\t--numbot\tNumber of parallel bot to start, default: 16\n"
        << "\t--numworld\tNumber of shared world used by bots, less worlds saves RAM, but can be slower if shared between too many bots, default: 4\n"
        << "\t--start\t3 ints, offset for the first block, default: -64 -59 832\n"
        << "\t--end\t3 ints, offset for the last block, default: 63 80 959\n"
        << "\t--tempblock\tname of the temp block, must be a full solid block, default: minecraft:basalt\n"
        << "\t--spared\tcomma-separated list of blocks you don't want the bots to break, default: minecraft:spawner,minecraft:torch\n"
        << "\t--collected\tcomma-separated list of items you want the bot to store (be careful to use item names instead of blocks if tools don't have silk touch), default: minecraft:diamond_ore,minecraft:deepslate_diamond_ore\n"
        << "\t--stopword\tif someone says this word in chat, all bots will go back to basecamp and stop working. Use it if you need to pause the process to be able to resume it, default:banana\n"
        << std::endl;
}

struct Args
{
    bool help = false;
    std::string address = "127.0.0.1:25565";
    int num_bot = 16;
    int num_world = 4;
    Botcraft::Position start = Botcraft::Position(-64, -59, 832);
    Botcraft::Position end = Botcraft::Position(63, 80, 959);
    std::string temp_block = "minecraft:basalt";
    std::string spared_blocks = "minecraft:spawner,minecraft:torch";
    std::string collected_blocks = "minecraft:diamond_ore,minecraft:deepslate_diamond_ore";
    std::string stopword = "banana";

    int return_code = 0;
};

Args ParseCommandLine(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    try
    {
        // Init logging, log everything >= Info, to console and file
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Info);
        Botcraft::Logger::GetInstance().SetFilename("world-eater.logs");
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
            shared_worlds[i] = std::make_shared<Botcraft::World>(true);
        }
        std::vector<std::string> names(args.num_bot);
        std::vector<std::shared_ptr<WorldEaterClient> > clients(args.num_bot);
        for (int i = 0; i < args.num_bot; ++i)
        {
            // Get a unique name for this bot
            names[i] = i < base_names.size() ? base_names[i] : (base_names[i % base_names.size()] + std::to_string(i / base_names.size()));
            // Create the bot client and connect to the server
            clients[i] = std::make_shared<WorldEaterClient>(args.stopword, false);
            clients[i]->SetSharedWorld(shared_worlds[i % args.num_world]);
            clients[i]->SetAutoRespawn(true);
            clients[i]->Connect(args.address, names[i], false);
            // Start behaviour thread and set active tree
            clients[i]->StartBehaviour();
            clients[i]->SetBehaviourTree(eater_behaviour_tree, {
                { "Eater.bot_index" , i },
                { "Eater.num_bot", args.num_bot },
                { "Eater.start_block", args.start },
                { "Eater.end_block", args.end },
                { "Eater.temp_block", args.temp_block },
                { "Eater.spared_blocks", args.spared_blocks },
                { "Eater.collected_blocks", args.collected_blocks }
            });
            // Wait 2 seconds between each bot to avoid having too many bots loading all the chunks at the same time
            Botcraft::Utilities::SleepFor(std::chrono::seconds(2));
        }

        std::vector<std::thread> behaviours_threads(args.num_bot);
        for (int i = 0; i < args.num_bot; ++i)
        {
            behaviours_threads[i] = std::thread(&Botcraft::SimpleBehaviourClient::RunBehaviourUntilClosed, clients[i]);
            // Start all the behaviours with a 2 seconds interval
            Botcraft::Utilities::SleepFor(std::chrono::seconds(2));
        }

        // Wait for all the bots to disconnect (meaning the job is done if everything worked properly)
        for (int i = 0; i < args.num_bot; ++i)
        {
            behaviours_threads[i].join();
        }

        return 0;
    }
    catch (std::exception& e)
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
        else if (arg == "--spared")
        {
            if (i + 1 < argc)
            {
                args.spared_blocks = argv[++i];
            }
            else
            {
                LOG_FATAL("--spared requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--collected")
        {
            if (i + 1 < argc)
            {
                args.collected_blocks = argv[++i];
            }
            else
            {
                LOG_FATAL("--collected requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--stopword")
        {
            if (i + 1 < argc)
            {
                args.stopword = argv[++i];
            }
            else
            {
                LOG_FATAL("--stopword requires an argument");
                args.return_code = 1;
                return args;
            }
        }
    }
    return args;
}
