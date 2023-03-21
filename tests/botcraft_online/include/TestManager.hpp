#pragma once

#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

#include <vector>
#include <string>
#include <map>
#include <mutex>

#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/Enums.hpp>
#include <botcraft/Game/ConnectionClient.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/Utilities/SleepUtilities.hpp>


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
    /// @brief Create a book with given content at pos
    /// @param pos Position of the item frame/lectern
    /// @param pages Content of the pages of the book
    /// @param facing Orientation of the item frame/lectern (book is toward this direction)
    /// @param title Title of the book
    /// @param author Author of the book
    /// @param description Description of the book (minecraft tooltip)
    void CreateBook(const Botcraft::Position& pos, const std::vector<std::string>& pages, const std::string& facing = "north", const std::string& title = "", const std::string& author = "", const std::vector<std::string>& description = {});
    void SetGameMode(const std::string& name, const Botcraft::GameType gamemode) const;

    void Teleport(const std::string& name, const Botcraft::Vector3<double>& pos) const;

    template<class ClientType = Botcraft::ConnectionClient,
        std::enable_if_t<std::is_base_of_v<Botcraft::ConnectionClient, ClientType>, bool> = true>
    std::unique_ptr<ClientType> GetBot()
    {
        std::unique_ptr<ClientType> client;
        if constexpr (std::is_same_v<ClientType, Botcraft::ConnectionClient>)
        {
            client = std::make_unique<ClientType>();
        }
        else
        {
            client = std::make_unique<ClientType>(false);
        }

        const std::string botname = "botcraft_" + std::to_string(bot_index++);
        client->Connect("127.0.0.1:25565", botname);
        MinecraftServer::GetInstance().WaitLine(".*?" + botname + " joined the game.*", 2000);

        if constexpr (std::is_same_v<ClientType, Botcraft::ConnectionClient>)
        {
            return client;
        }
        else
        {
            // If this is not a ConnectionClient, wait for all the chunks to be loaded
            const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
            while (true)
            {
                // Something went wrong
                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() >= 5000)
                {
                    throw std::runtime_error(botname + " took too long to load world");
                }
                {
                    std::lock_guard<std::mutex> world_lock(client->GetWorld()->GetMutex());
                    if (client->GetWorld()->GetAllChunks().size() >= 36) // view-distance 5 --> 6x6
                    {
                        break;
                    }
                }
                Botcraft::SleepFor(std::chrono::milliseconds(10));
            }
            return client;
        }
    }

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

    /// @brief Make sure a block is loaded on the server by teleporting the chunk_loader
    /// @param pos The position to load
    void MakeSureLoaded(const Botcraft::Position& pos) const;

    friend class TestManagerListener;
    void testRunStarting(Catch::TestRunInfo const& test_run_info);
    void testCaseStarting(Catch::TestCaseInfo const& test_info);
    void testCasePartialStarting(Catch::TestCaseInfo const& test_info, uint64_t part_number);
    void sectionStarting(Catch::SectionInfo const& section_info);
    void assertionEnded(Catch::AssertionStats const& assertion_stats);
    void testCasePartialEnded(Catch::TestCaseStats const& test_case_stats, uint64_t part_number);
    void testCaseEnded(Catch::TestCaseStats const& test_case_stats);
    void testRunEnded(Catch::TestRunStats const& test_run_info);

private:
    /// @brief Offset in the world for current section/test
    Botcraft::Position current_offset;
    /// @brief Size of the header structure
    Botcraft::Position header_size;

    /// @brief Index of the next bot to be created
    int bot_index;
    /// @brief Bot used to load chunks before running commands on them
    std::unique_ptr<Botcraft::ConnectionClient> chunk_loader;
    /// @brief Name of the bot used as chunk loader
    std::string chunk_loader_name;

    /// @brief Index of the current test in the world
    int current_test_index;
    /// @brief Size of the loaded structure for current test
    Botcraft::Position current_test_size;
    /// @brief All failed assertions in this test case so far
    std::vector<std::string> current_test_case_failures;

    /// @brief Store names of all running (potentially) nested sections
    std::vector<std::string> section_stack;
    /// @brief Position of the header for current section
    Botcraft::Position current_header_position;
};

/// @brief Catch2 listener to get test events and pass them to the main singleton
/// that can be easily accessed from inside the tests. Maybe there is an easier dedicated
/// way to do it without a singleton but couldn't find it.
class TestManagerListener : public Catch::EventListenerBase
{
    using Catch::EventListenerBase::EventListenerBase;

    void testRunStarting(Catch::TestRunInfo const& test_run_info) override;
    void testCaseStarting(Catch::TestCaseInfo const& test_info) override;
    void testCasePartialStarting(Catch::TestCaseInfo const& test_info, uint64_t part_number);
    void sectionStarting(Catch::SectionInfo const& section_info) override;
    void assertionEnded(Catch::AssertionStats const& assertion_stats) override;
    void testCasePartialEnded(Catch::TestCaseStats const& test_case_stats, uint64_t part_number);
    void testCaseEnded(Catch::TestCaseStats const& test_case_stats) override;
    void testRunEnded(Catch::TestRunStats const& test_run_info) override;
};
