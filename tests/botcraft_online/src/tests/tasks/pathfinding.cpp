#include "TestManager.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/AI/Tasks/PathfindingTask.hpp>

TEST_CASE("simple pathfinding")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.5, 2.01, 2.5));

	std::vector<std::pair<std::string, Botcraft::Vector3<double>>> directions = {
		{"south", Botcraft::Position(0, 0, 2)},
		{"north", Botcraft::Position(0, 0, -2)},
		{"east", Botcraft::Position(2, 0, 0)},
		{"west", Botcraft::Position(-2, 0, 0)},
	};

	std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
	Botcraft::Vector3<double> init_position;
	{
		std::lock_guard<std::mutex> lock(local_player->GetMutex());
		init_position = local_player->GetPosition();
	}
	for (size_t i = 0; i < directions.size(); ++i)
	{
		SECTION(directions[i].first)
		{
			bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 4.317f, false);
			{
				std::lock_guard<std::mutex> lock(local_player->GetMutex());
				CHECK_THAT(local_player->GetPosition().SqrDist(init_position + directions[i].second), Catch::Matchers::WithinAbs(0.0, 0.1));
			}
		}
	}
}

TEST_CASE("jump pathfinding")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(1.5, 1.01, 1.5));

	std::vector<std::pair<std::string, Botcraft::Vector3<double>>> directions = {
		{"south", Botcraft::Position(0, 1, 1)},
		{"north", Botcraft::Position(0, 1, -1)},
		{"east", Botcraft::Position(1, 1, 0)},
		{"west", Botcraft::Position(-1, 1, 0)},
	};

	std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
	Botcraft::Vector3<double> init_position;
	{
		std::lock_guard<std::mutex> lock(local_player->GetMutex());
		init_position = local_player->GetPosition();
	}
	for (size_t i = 0; i < directions.size(); ++i)
	{
		SECTION(directions[i].first)
		{
			bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 4.317f, true);
			{
				std::lock_guard<std::mutex> lock(local_player->GetMutex());
				CHECK_THAT(local_player->GetPosition().SqrDist(init_position + directions[i].second), Catch::Matchers::WithinAbs(0.0, 0.1));
			}
		}
	}
}

TEST_CASE("gap pathfinding")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.5, 2.01, 2.5));

	std::vector<std::pair<std::string, Botcraft::Vector3<double>>> directions = {
		{"south", Botcraft::Position(0, 0, 2)},
		{"north", Botcraft::Position(0, 0, -2)},
		{"east", Botcraft::Position(2, 0, 0)},
		{"west", Botcraft::Position(-2, 0, 0)},
	};

	std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
	Botcraft::Vector3<double> init_position;
	{
		std::lock_guard<std::mutex> lock(local_player->GetMutex());
		init_position = local_player->GetPosition();
	}
	for (size_t i = 0; i < directions.size(); ++i)
	{
		SECTION(directions[i].first)
		{
			bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 4.317f, true);
			{
				std::lock_guard<std::mutex> lock(local_player->GetMutex());
				CHECK_THAT(local_player->GetPosition().SqrDist(init_position + directions[i].second), Catch::Matchers::WithinAbs(0.0, 0.1));
			}
		}
	}
}

TEST_CASE("climb pathfinding")
{
	std::vector<std::pair<std::string, Botcraft::Vector3<double>>> directions = {
		{"south", Botcraft::Position(0, 4, -2)},
		{"north", Botcraft::Position(0, 4, 2)},
		{"east", Botcraft::Position(-2, 4, 0)},
		{"west", Botcraft::Position(2, 4, 0)},
	};
	const Botcraft::Position& current_offset = TestManager::GetInstance().GetCurrentOffset();

	for (size_t i = 0; i < directions.size(); ++i)
	{
		SECTION(directions[i].first)
		{
			std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.5, 5.01, 2.5) - directions[i].second);

			std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
			Botcraft::Vector3<double> init_position;
			{
				std::lock_guard<std::mutex> lock(local_player->GetMutex());
				init_position = local_player->GetPosition();
			}
			bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 4.317f, true);
			{
				std::lock_guard<std::mutex> lock(local_player->GetMutex());
				CHECK_THAT(local_player->GetPosition().SqrDist(init_position + directions[i].second), Catch::Matchers::WithinAbs(0.0, 0.1));
			}
		}
	}
}

TEST_CASE("fall pathfinding")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.5, 5.01, 2.5));

	std::vector<std::pair<std::string, Botcraft::Vector3<double>>> directions = {
		{"south", Botcraft::Position(0, -4, 2)},
		{"north", Botcraft::Position(0, -4, -2)},
		{"east", Botcraft::Position(2, -4, 0)},
		{"west", Botcraft::Position(-2, -4, 0)},
	};

	std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
	Botcraft::Vector3<double> init_position;
	{
		std::lock_guard<std::mutex> lock(local_player->GetMutex());
		init_position = local_player->GetPosition();
	}
	for (size_t i = 0; i < directions.size(); ++i)
	{
		SECTION(directions[i].first)
		{
			bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 4.317f, true);
			{
				std::lock_guard<std::mutex> lock(local_player->GetMutex());
				CHECK_THAT(local_player->GetPosition().SqrDist(init_position + directions[i].second), Catch::Matchers::WithinAbs(0.0, 0.1));
			}
		}
	}
}

TEST_CASE("full pathfinding")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(0.0, 1.01, 0.0));
	
	const Botcraft::Position delta(2, 3, 24);

	std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
	Botcraft::Vector3<double> init_position;
	{
		std::lock_guard<std::mutex> lock(local_player->GetMutex());
		init_position = local_player->GetPosition();
	}

	bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 4.317f, true);
	{
		std::lock_guard<std::mutex> lock(local_player->GetMutex());
		CHECK_THAT(local_player->GetPosition().SqrDist(init_position + delta), Catch::Matchers::WithinAbs(0.0, 0.1));
		CHECK_THAT(local_player->GetHealth(), Catch::Matchers::WithinAbs(20.0, 0.01));
	}
}
