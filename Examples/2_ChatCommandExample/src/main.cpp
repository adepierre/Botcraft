#include <iostream>
#include <string>

#include "ChatCommandClient.hpp"

int main(int argc, char* argv[])
{
    try
    {
        std::string login = "BCChatCommand";
        std::string password = "";
        std::string ip = "127.0.0.1";
        unsigned short port = 25565;
        
        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
            std::cout << "Usage: 2_ChatCommandExample [ip](127.0.0.1) [port](25565) [login](BCChatCommand) [password]()" << std::endl;
        }

        if (argc > 1)
        {
            ip = argv[1];
        }

        if (argc > 2)
        {
            port = std::stoi(argv[2]);
        }

        if (argc > 3)
        {
            login = argv[3];
        }

        if (argc > 4)
        {
            password = argv[4];
        }

        ChatCommandClient client;
        client.SetAutoRespawn(true);

        std::cout << "Starting connection process" << std::endl;
        client.Connect(ip, port, login, password);

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