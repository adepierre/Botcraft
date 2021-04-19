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
        << "\t--n\tNumber of parallel bot to start, default: 1\n"
        << "\t--nbt\tnbt filename to load, default: empty\n"
        << "\t--offset\t3 ints, offset for the first block, default: 0 0 0\n"
        << "\t--tempblock\tname of the scafholding block, default: minecraft:slime_block\n"
        << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        std::string address = "127.0.0.1:25565";
        std::string botname = "BCBuilderBot";
        int num_bot = 10;
        std::string nbt_file = "";
        Botcraft::Position offset(0, 0, 0);//Botcraft::Position(-64, 1, 63)
        std::string temp_block = "minecraft:slime_block";

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
        std::vector<std::shared_ptr<MapCreatorBot> > clients;
        clients.reserve(num_bot);
        for (int i = 0; i < num_bot; ++i)
        {
            clients.push_back(std::shared_ptr<MapCreatorBot>(new MapCreatorBot(false)));
            clients[clients.size() - 1]->SetAutoRespawn(true);
            clients[clients.size() - 1]->LoadNBTFile(nbt_file, offset, temp_block, i == 0);
            clients[clients.size() - 1]->Connect(address, botname + "_" + std::to_string(i), "");
        }

        while (true)
        {
            for (int i = clients.size() - 1; i > -1; i--)
            {
                if (clients[i]->GetShouldBeClosed())
                {
                    clients[i]->Disconnect();
                    clients[i].reset();
                    clients[i] = std::shared_ptr<MapCreatorBot>(new MapCreatorBot(false));
                    clients[i]->SetAutoRespawn(true);
                    clients[i]->LoadNBTFile(nbt_file, offset, temp_block, i == 0);
                    clients[i]->Connect(address, botname + "_" + std::to_string(i), "");

                    std::cout << botname + "_" + std::to_string(i) << " has been stopped. You should restart it" << std::endl;
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