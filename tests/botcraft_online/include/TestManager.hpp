#pragma once

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

class TestManager
{
private:
    TestManager();
    ~TestManager();
    TestManager(const TestManager&) = delete;
    TestManager(TestManager&&) = delete;
    TestManager& operator=(const TestManager&) = delete;

public:
    static TestManager& GetInstance();

};

class TestManagerListener : public Catch::EventListenerBase
{
    using Catch::EventListenerBase::EventListenerBase;
    
    void testRunStarting(Catch::TestRunInfo const& test_run_info) override;
    void testCaseStarting(Catch::TestCaseInfo const& test_info) override;
    void testCaseEnded(Catch::TestCaseStats const& test_case_stats) override;
    void sectionStarting(Catch::SectionInfo const& section_info) override;
    void sectionEnded(Catch::SectionStats const& section_stats) override;
};
CATCH_REGISTER_LISTENER(TestManagerListener)
