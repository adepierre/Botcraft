#include "TestManager.hpp"
#include "MinecraftServer.hpp"

#include <botcraft/Game/ManagersClient.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("current offset")
{
	CHECK(TestManager::GetInstance().GetCurrentOffset() != Botcraft::Position());
}

TEST_CASE("commands")
{
	MinecraftServer::GetInstance().SendLine("say hello");
	std::vector<std::string> captured;
	// \\w because we want the regex string to be \w
	REQUIRE_NOTHROW(captured = MinecraftServer::GetInstance().WaitLine(".*: (?:\\[Not Secure\\] )?[[<]Server[>\\]] \\b(\\w+)\\b.*", 2000));
	REQUIRE(captured.size() == 2);
	CHECK(captured[0].substr(captured[0].size() - 5) == "hello");
	CHECK(captured[1] == "hello");
}

TEST_CASE("create block")
{
	const Botcraft::Position anvil_position = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1);
	REQUIRE_NOTHROW(TestManager::GetInstance().SetBlock("anvil", anvil_position));
}

TEST_CASE("create book")
{
	const Botcraft::Position& pos = TestManager::GetInstance().GetCurrentOffset();
	CHECK_NOTHROW(TestManager::GetInstance().SetBlock("anvil", pos + Botcraft::Position(1, 0, 1)));
	REQUIRE_NOTHROW(TestManager::GetInstance().CreateBook(pos + Botcraft::Position(1, 0, 0), { "hello", "", "hello page 3" }, "north", "Title", "author", { "desc1", "desc2" }));
}

TEST_CASE("teleport bot")
{
	std::unique_ptr<Botcraft::ManagersClient> bot;
	std::string botname;
	REQUIRE_NOTHROW(bot = TestManager::GetInstance().GetBot(botname, Botcraft::GameType::Adventure));
	CHECK_NOTHROW(TestManager::GetInstance().Teleport(botname, TestManager::GetInstance().GetCurrentOffset() + Botcraft::Vector3<double>(1, 2, 1)));
}
