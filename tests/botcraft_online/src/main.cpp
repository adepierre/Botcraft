#include <catch2/catch_session.hpp>

#include <botcraft/Utilities/Logger.hpp>

#include "MinecraftServer.hpp"

int main(int argc, char* argv[])
{
    MinecraftServer::options.argv0 = argv[0];
    Botcraft::Logger::GetInstance().RegisterThread("main");

    Catch::Session session;

    // Parse the command line
    int ret = session.applyCommandLine(argc, argv);
    if (ret != 0)
    {
        return ret;
    }

    // Adapt botcraft logger to catch loglevel
    switch (session.config().verbosity())
    {
    case Catch::Verbosity::Quiet:
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Fatal);
        break;
    case Catch::Verbosity::Normal:
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Warning);
        break;
    case Catch::Verbosity::High:
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Debug);
        break;
    }

    return session.run();
}
