#include <iostream>
#include <string>

#include "botcraft/Game/World/World.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include "UserControlledClient.hpp"

void ShowHelp(const char* argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
        << "Options:\n"
        << "\t-h, --help\tShow this help message\n"
        << "\t--connect\tIf 0, create a local world for testing instead of connecting to a server, default 1\n"
        << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
        << "\t--login\t\tPlayer name in offline mode, empty for Microsoft account, default: BCUserControl\n"
        << std::endl;
}

struct Args
{
    bool help = false;
    bool connect = true;
    std::string address = "127.0.0.1:25565";
    std::string login = "BCUserControl";

    int return_code = 0;
};

Args ParseCommandLine(int argc, char* argv[]);

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

        UserControlledClient client(args.connect, true);
        
        if (args.connect)
        {
            client.SetAutoRespawn(true);
            LOG_INFO("Starting connection process");
            client.Connect(args.address, args.login);
        }

        while (!client.GetShouldBeClosed())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (args.connect)
        {
            client.Disconnect();
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

    return 0;
}

Args ParseCommandLine(int argc, char* argv[])
{
    Args args;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            args.help = true;
            return args;
        }
        else if (arg == "--connect")
        {
            if (i + 1 < argc)
            {
                args.connect = static_cast<bool>(std::stoi(argv[++i]));
            }
            else
            {
                LOG_FATAL("--connect requires an argument");
                args.return_code = 1;
                return args;
            }
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
        else if (arg == "--login")
        {
            if (i + 1 < argc)
            {
                args.login = argv[++i];
            }
            else
            {
                LOG_FATAL("--login requires an argument");
                args.return_code = 1;
                return args;
            }
        }
    }
    return args;
}
