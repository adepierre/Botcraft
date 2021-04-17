#include <iostream>
#include <string>

#include "MapCreatorBot.hpp"

void ShowHelp(const char* argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
        << "Options:\n"
        << "\t-h, --help\tShow this help message\n"
        << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
        << "\t--login\t\tMojang account login for connection, default: BCMapCreatorBot\n"
        << "\t--password\tMojang account password for connection, empty for servers in offline mode, default: empty\n"
        << "\t--jsonaccount\tPath to a json file from the official minecraft launcher, can be used for people with a Microsoft account, default: empty"
        << std::endl;
}

int main(int argc, char* argv[])
{
    try
    {
        std::string address = "127.0.0.1:25565";
        std::string login = "BCMapCreatorBot";
        std::string password = "";
        std::string launcher_accounts_file = "";

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
            else if (arg == "--login")
            {
                if (i + 1 < argc)
                {
                    login = argv[++i];
                }
                else
                {
                    std::cerr << "--login requires an argument" << std::endl;
                    return 1;
                }
            }
            else if (arg == "--password")
            {
                if (i + 1 < argc)
                {
                    password = argv[++i];
                }
                else
                {
                    std::cerr << "--password requires an argument" << std::endl;
                    return 1;
                }
            }
            else if (arg == "--jsonaccount")
            {
                if (i + 1 < argc)
                {
                    launcher_accounts_file = argv[++i];
                }
                else
                {
                    std::cerr << "--jsonaccount requires an argument" << std::endl;
                    return 1;
                }
            }
        }

        MapCreatorBot client(false);
        client.SetAutoRespawn(true);
        client.LoadNBTFile("batman_small.nbt", Botcraft::Position(-64, 1, 64), "minecraft:slime_block");

        if (!launcher_accounts_file.empty())
        {
            std::cout << "Starting connection process using launcher accounts file" << std::endl;
            client.Connect(address, launcher_accounts_file);
        }
        else
        {
            std::cout << "Starting connection process using login and password" << std::endl;
            client.Connect(address, login, password);
        }

        while (!client.GetShouldBeClosed())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        client.Disconnect();

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