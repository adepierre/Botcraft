#include <iostream>
#include <string>

#include "UserControlledClient.hpp"
#include "botcraft/Game/World/World.hpp"

int main(int argc, char* argv[])
{
    try
    {
        bool ONLINE = true;
        std::string login = "BCUserControl";
        std::string password = "";
        std::string address = "127.0.0.1:25565";

        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
            std::cout << "Usage: 1_UserControlledExample [online](1) [address](127.0.0.1:25565) [login](BCUserControl) [password]()" << std::endl;
        }

        if (argc > 1)
        {
            ONLINE = std::stoi(argv[1]);
        }

        if (argc > 2)
        {
            address = argv[2];
        }

        if (argc > 3)
        {
            login = argv[3];
        }

        if (argc > 4)
        {
            password = argv[4];
        }

        UserControlledClient client(ONLINE, true);
        
        if (ONLINE)
        {
            client.SetAutoRespawn(true);
            std::cout << "Starting connection process" << std::endl;
            client.Connect(address, login, password);
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