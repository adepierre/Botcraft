#include <iostream>
#include <string>

#include "UserControlledClient.hpp"

int main(int argc, char* argv[])
{
    try
    {
        bool ONLINE = false;
        unsigned short port = 25565;
        std::string player_name = "BCUserControl";
        std::string ip = "127.0.0.1";

        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
            std::cout << "Usage: 1_UserControlledExample [online](1) [ip](127.0.0.1) [port](25565) [name](BCUserControl)" << std::endl;
        }

        if (argc > 1)
        {
            ONLINE = std::stoi(argv[1]);
        }

        if (argc > 2)
        {
            ip = argv[2];
        }

        if (argc > 3)
        {
            port = std::stoi(argv[3]);
        }

        if (argc > 4)
        {
            player_name = argv[4];
        }

        UserControlledClient client(ONLINE);

        if (ONLINE)
        {
            client.SetAutoRespawn(true);
            std::cout << "Starting connection process" << std::endl;
            client.Connect(ip, port, player_name);
        }

        while (!client.GetShouldBeClosed())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (ONLINE)
        {
            client.Disconnect();
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

    return 0;
}