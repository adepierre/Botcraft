#include <iostream>
#include <string>

#include <botcraft/Game/BaseClient.hpp>

int main(int argc, char* argv[])
{
    try
    {
        std::string login = "BCAFK";
        std::string password = "";
        std::string address = "127.0.0.1:25565";
        
        if (argc == 1)
        {
            std::cout << "No command arguments. Using default options.\n";
            std::cout << "Usage: 3_SimpleAFKExample [address](127.0.0.1:25565) [login](BCAFK) [password]()" << std::endl;
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

#if USE_GUI
        Botcraft::BaseClient client(true, true);
#else
        Botcraft::BaseClient client(false, true);
#endif

        std::cout << "Starting connection process" << std::endl;
        client.Connect(address, login, password);

        while (true)
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