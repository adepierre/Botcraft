#include <iostream>
#include <string>

#include "MapCreatorBot.hpp"

void ShowHelp(const char* argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
        << "Options:\n"
        << "\t-h, --help\tShow this help message\n"
        << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
        << "\t--botname\t\tName of the bot, default: BCBuilderBot\n"
        << "\t--n\tNumber of parallel bot to start, default: 1"
        << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        std::string address = "127.0.0.1:25565";
        std::string botname = "BCBuilderBot";
        int num_bot = 1;

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
            else if (arg == "--botname")
            {
                if (i + 1 < argc)
                {
                    botname = argv[++i];
                }
                else
                {
                    std::cerr << "--botname requires an argument" << std::endl;
                    return 1;
                }
            }
            else if (arg == "--n")
            {
                if (i + 1 < argc)
                {
                    num_bot = std::stoi(argv[++i]);
                }
                else
                {
                    std::cerr << "--n requires an argument" << std::endl;
                    return 1;
                }
            }
        }
        std::vector<std::shared_ptr<MapCreatorBot> > clients;
        for (int i = 0; i < num_bot; ++i)
        {
            clients.push_back(std::shared_ptr<MapCreatorBot>(new MapCreatorBot(false)));
            clients[clients.size() - 1]->SetAutoRespawn(true);
            clients[clients.size() - 1]->LoadNBTFile("batman_small.nbt", Botcraft::Position(-64, 1, 63), "minecraft:slime_block", i == 0);
            clients[clients.size() - 1]->Connect(address, botname + "_" + std::to_string(i), "");
        }

        while (true)
        {
            for (int i = clients.size() - 1; i > -1; i--)
            {
                if (clients[i]->GetShouldBeClosed())
                {
                    clients[i]->Disconnect();
                    clients.erase(clients.begin() + i);
                }
            }

            if (clients.size() == 0)
            {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
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