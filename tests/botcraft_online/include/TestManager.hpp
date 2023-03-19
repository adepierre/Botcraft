#pragma once

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <vector>
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

    /// @brief Spacing between tests
    static constexpr int spacing_x = 10;
    /// @brief Spacing between sections
    static constexpr int spacing_z = 5;

public:
    static TestManager& GetInstance();

    /// @brief current_offset getter
    /// @return The offset in the world of the currently running section
    const Botcraft::Position& GetCurrentOffset() const;

#if PROTOCOL_VERSION == 340
    void SetBlock(const std::string& name, const Botcraft::Position& pos, const int block_variant = 0, const std::map<std::string, std::string>& metadata = {}) const;
#endif

private:
    /// @brief Read a NBT structure file and extract its size
    /// @return A X/Y/Z size Vector3
    Botcraft::Position GetStructureSize(const std::string& filename) const;

    /// @brief Create a TP sign
    /// @param src Position of the sign.
    /// @param dst TP destination coordinates
    /// @param texts A list of strings to display on the sign
    void CreateTPSign(const Botcraft::Position& src, const Botcraft::Vector3<double>& dst, const std::vector<std::string>& texts, const std::string& facing = "north") const;

    /// @brief Load a structure block into the world
    /// @param filename The structure block to load. If it doesn't exist, will use "_default" instead
    /// @param pos position of the structure block
    /// @param load_offset offset to load the structure to (w.r.t pos), default to (0,0,0)
    void LoadStructure(const std::string& filename, const Botcraft::Position& pos, const Botcraft::Position& load_offset = Botcraft::Position()) const;

    friend class TestManagerListener;
    void testRunStarting(Catch::TestRunInfo const& test_run_info);
    void testCaseStarting(Catch::TestCaseInfo const& test_info);
    void testCaseEnded(Catch::TestCaseStats const& test_case_stats);
    void sectionStarting(Catch::SectionInfo const& section_info);
    void sectionEnded(Catch::SectionStats const& section_stats);

private:
    /// @brief Offset in the world for current test
    Botcraft::Position current_offset;

    /// @brief Size of the loaded structure for current test
    Botcraft::Position current_test_size;

    /// @brief Name of the current test
    std::string current_test_name;

    /// @brief Index of the current test in the world
    int current_test_index;

    /// @brief Index of the current section in the current test
    int current_section_index;

    /// @brief Whether or not all assertions in the current test passed
    bool current_test_success;

    /// @brief Position of the header for current test
    Botcraft::Position current_header_position;

    /// @brief Size of the header structure
    Botcraft::Position header_size;

    /// @brief Store names of all running (potentially) nested sections
    std::vector<std::string> section_stack;

    /// @brief Current depth level of the running section
    int current_section_stack_depth;
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
