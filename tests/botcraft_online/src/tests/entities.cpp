#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/entities/Entity.hpp>

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("summoning")
{
	const std::vector<std::string> types = {
		"cow",
		"horse",
		"villager",
		"witch"
	};
	std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();
	const Botcraft::Vector3<double> pos = Botcraft::Vector3<double>(1.5, 0, 1.5) + TestManager::GetInstance().GetCurrentOffset();

	for (const auto& t : types)
	{
		SECTION(t)
		{
			std::stringstream command;
			command
				<< "summon" << " "
				<< t << " "
				<< pos.x << " "
				<< pos.y << " "
				<< pos.z << " "
				<< "{NoAI:1b,PersistenceRequired:1b}";
			MinecraftServer::GetInstance().SendLine(command.str());
#if PROTOCOL_VERSION > 340
			MinecraftServer::GetInstance().WaitLine(".*?: Summoned new.*", 2000);
#else
			MinecraftServer::GetInstance().WaitLine(".*?: Object successfully summoned.*", 2000);
#endif
			std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
			std::shared_ptr<Botcraft::Entity> entity;
			// Wait for the entity to be registered on bot side
			REQUIRE(Botcraft::WaitForCondition([&]()
				{
					std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
					for (const auto& [k, v] : entity_manager->GetEntities())
					{
						if (v->GetPosition().SqrDist(pos) < 0.2)
						{
							entity = v;
							return true;
						}
					}
					return false;
				}, 2000));
			REQUIRE(entity != nullptr);
			CHECK(entity->GetName() == t);
		}
	}
}
