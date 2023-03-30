#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/AI/Tasks/BaseTasks.hpp>

#include <sstream>

TEST_CASE("say")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

	bot->SyncAction(Botcraft::Say, "Hello, world!");
	const std::string& botname = bot->GetNetworkManager()->GetMyName();

	REQUIRE_NOTHROW(MinecraftServer::GetInstance().WaitLine(".*: (?:\\[Not Secure\\] )?[[<]" + botname + "[>\\]] Hello, world!.*", 2000));
}
