#include <iostream>
#include <string>

#include "botcraft/Game/InterfaceClient.hpp"

int main(int argc, char* argv[])
{
    try
    {
        std::string login = "BCHelloWorld";
        std::string password = "";
        std::string ip = "127.0.0.1";
        unsigned short port = 25565;

        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
            std::cout << "Usage: 0_HelloWorld [ip](127.0.0.1) [port](25565) [login](BCHelloWorld) [password]()" << std::endl;
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

        Botcraft::InterfaceClient client;
        client.SetAutoRespawn(true);

        std::cout << "Starting connection process" << std::endl;
        client.Connect(ip, port, login, password);

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        client.Say("Hello world!");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

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

    return 0;
}