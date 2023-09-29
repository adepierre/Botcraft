#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <botcraft/Utilities/Logger.hpp>

class testRunListener : public Catch::EventListenerBase
{
public:
    using Catch::EventListenerBase::EventListenerBase;

    void testRunStarting(Catch::TestRunInfo const&) override
    {
        // Set log level to warning before starting the tests
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Warning);
    }
};

CATCH_REGISTER_LISTENER(testRunListener)
