#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "botcraft/Game/ConnectionClient.hpp"
#include "botcraft/Utilities/Logger.hpp"

void ShowHelp(const char *argv0)
{
    std::cout << "Usage: " << argv0 << " <options>\n"
              << "Options:\n"
              << "\t-h, --help\tShow this help message\n"
              << "\t--address\tAddress of the server you want to connect to, default: 127.0.0.1:25565\n"
              << "\t--email\t\tEmail, default: bot1@ws01.ltd\n"
              << "\t--password\t\tPassword, default: bot1@ws01.ltd\n"
              << "\t--url\t\tYggdrasil url, default: https://mc.login.kim:6066/api/yggdrasil\n"
              << std::endl;
}

struct Args
{
    bool help = false;
    std::string address = "10.0.0.103:25565";
    std::string email = "bot1@ws01.ltd";
    std::string password = "bot1@ws01.ltd";
    std::string url = "https://mc.login.kim:6066/api/yggdrasil";

    int return_code = 0;
};

Args ParseCommandLine(int argc, char *argv[]);

int main(int argc, char *argv[])
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

        Botcraft::ConnectionClient client;

        LOG_INFO("Starting connection process");
        client.Connect(args.address, args.url, args.email, args.password);

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        client.SendChatMessage(u8"Hello, World!");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        client.Disconnect();

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

Args ParseCommandLine(int argc, char *argv[])
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
        else if (arg == "--email")
        {
            if (i + 1 < argc)
            {
                args.email = argv[++i];
            }
            else
            {
                LOG_FATAL("--login requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--password")
        {
            if (i + 1 < argc)
            {
                args.password = argv[++i];
            }
            else
            {
                LOG_FATAL("--password requires an argument");
                args.return_code = 1;
                return args;
            }
        }
        else if (arg == "--url")
        {
            if (i + 1 < argc)
            {
                args.url = argv[++i];
            }
            else
            {
                LOG_FATAL("--url requires an argument");
                args.return_code = 1;
                return args;
            }
        }
    }
    return args;
}
