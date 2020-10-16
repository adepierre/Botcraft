#include <iostream>
#include <string>

#include "botcraft/Game/InterfaceClient.hpp"

int main(int argc, char* argv[])
{
    try
    {
        std::string login = "BCHelloWorld";
        std::string password = "";
        std::string address = "127.0.0.1:25565";

        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
            std::cout << "Usage: 0_HelloWorld [address](127.0.0.1:25565) [login](BCHelloWorld) [password]()" << std::endl;
        }

        if (argc > 1)
        {
            address = argv[1];
        }

        if (argc > 2)
        {
            login = argv[2];
        }

        if (argc > 3)
        {
            password = argv[3];
        }

        Botcraft::InterfaceClient client(true, false);
        client.SetAutoRespawn(true);

        std::cout << "Starting connection process" << std::endl;
        client.Connect(address, login, password);

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