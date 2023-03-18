#pragma once

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <stack>
#include <string>
#include <map>

#include <botcraft/Game/Vector3.hpp>

/// @brief Singleton class that organizes the layout of the tests
/// in the world and sets them up.
class TestManager
{
private:
    TestManager();
    ~TestManager();
    TestManager(const TestManager&) = delete;
    TestManager(TestManager&&) = delete;
    TestManager& operator=(const TestManager&) = delete;

    static constexpr int spacing_x = 5;
    static constexpr int spacing_z = 5;

    //friend class TestManagerListener;

    /// @brief Read a NBT structure file and extract its size
    /// @return A X/Y/Z size Vector3
    Botcraft::Position GetStructureSize(const std::string& filename) const;

public:
    static TestManager& GetInstance();

    const Botcraft::Position& GetCurrentOffset() const;

    void testRunStarting(Catch::TestRunInfo const& test_run_info);
    void testCaseStarting(Catch::TestCaseInfo const& test_info);
    void testCaseEnded(Catch::TestCaseStats const& test_case_stats);
    void sectionStarting(Catch::SectionInfo const& section_info);
    void sectionEnded(Catch::SectionStats const& section_stats);

    void LoadStructure(const std::string& filename, const Botcraft::Position& pos, const Botcraft::Position& load_offset = Botcraft::Position());
#if PROTOCOL_VERSION == 340
    void SetBlock(const std::string& name, const Botcraft::Position& pos, const int block_variant = 0, const std::map<std::string, std::string>& metadata = {});
#endif

private:
    /// @brief Offset in the world for current test
    Botcraft::Position current_offset;

    /// @brief Size of the loaded structure for current test
    Botcraft::Position current_test_size;

    /// @brief Name of the current test
    std::string current_test_name;

    /// @brief Whether or not all assertions in the current test passed
    bool current_test_success;

    /// @brief Position of the header for current test
    Botcraft::Position current_header_position;

    /// @brief Size of the header structure
    Botcraft::Position header_size;

    /// @brief Store a stack of currently running (potentially) nested sections
    std::stack<std::string> section_stack;
};

/// @brief Catch2 listener to get test events and pass them to the main singleton
/// that can be easily accessed from inside the tests. Maybe there is an easier dedicated
/// way to do it without a singleton but couldn't find it.
class TestManagerListener : public Catch::EventListenerBase
{
    using Catch::EventListenerBase::EventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& test_run_info) override;
    void testCaseStarting(Catch::TestCaseInfo const& test_info) override;
    void testCaseEnded(Catch::TestCaseStats const& test_case_stats) override;
    void sectionStarting(Catch::SectionInfo const& section_info) override;
    void sectionEnded(Catch::SectionStats const& section_stats) override;
};
