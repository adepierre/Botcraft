#pragma once

#include "TestManager.hpp"

#include <memory>
#include <stdexcept>

#include <botcraft/AI/TemplatedBehaviourClient.hpp>
#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/Game/ManagersClient.hpp>
#include <botcraft/Game/Vector3.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>

template<class ClientType = Botcraft::ManagersClient>
std::unique_ptr<ClientType> SetupTestBot(const Botcraft::Vector3<double>& offset = { 0,0,0 })
{
	std::string botname;
	std::unique_ptr<ClientType> bot = TestManager::GetInstance().GetBot<ClientType>(botname);

	const Botcraft::Vector3<double> pos = offset + TestManager::GetInstance().GetCurrentOffset();
	TestManager::GetInstance().Teleport(botname, pos);

	// Wait for bot to register teleportation
	std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
	if (!Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(local_player->GetMutex());
			return local_player->GetPosition().SqrDist(pos) < 1.0;
		}, 2000))
	{
		throw std::runtime_error("Timeout waiting " + botname + " to register teleportation");
	}

	// Wait for bot to load center and corner view_distance blocks
	std::shared_ptr<Botcraft::World> world = bot->GetWorld();
	const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(Botcraft::CHUNK_WIDTH)));
	const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(Botcraft::CHUNK_WIDTH)));
	const int view_distance = MinecraftServer::options.view_distance;
	std::vector<std::pair<int, int>> wait_loaded = {
		{chunk_x * Botcraft::CHUNK_WIDTH, chunk_z * Botcraft::CHUNK_WIDTH},
		{(chunk_x + view_distance) * Botcraft::CHUNK_WIDTH - 1, (chunk_z + view_distance) * Botcraft::CHUNK_WIDTH - 1},
		{(chunk_x - view_distance) * Botcraft::CHUNK_WIDTH, (chunk_z + view_distance) * Botcraft::CHUNK_WIDTH - 1},
		{(chunk_x + view_distance) * Botcraft::CHUNK_WIDTH - 1, (chunk_z - view_distance) * Botcraft::CHUNK_WIDTH},
		{(chunk_x - view_distance) * Botcraft::CHUNK_WIDTH, (chunk_z - view_distance) * Botcraft::CHUNK_WIDTH}
	};

	if (!Botcraft::WaitForCondition([&]() {
			std::lock_guard<std::mutex> lock(world->GetMutex());
			for (size_t i = 0; i < wait_loaded.size(); ++i)
			{
				if (!bot->GetWorld()->IsLoaded(Botcraft::Position(wait_loaded[i].first, 2, wait_loaded[i].second)))
				{
					return false;
				}
			}
			return true;
		}, 5000))
	{
		throw std::runtime_error("Timeout waiting " + botname + " to load surroundings");
	}

	return bot;
}
