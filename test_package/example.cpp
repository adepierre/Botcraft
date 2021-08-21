#include <iostream>
#include <string>

#define PROTOCOL_VERSION 756 // from <botcraft/Version.hpp>
#include <botcraft/Game/InterfaceClient.hpp>

int main(int argc, char* argv[])
{
    {
        Botcraft::InterfaceClient client(true, false);
        client.SetAutoRespawn(true);
    }

    std::cout<<"No errors occurred, exiting..."<<std::endl;
    return 0;
}