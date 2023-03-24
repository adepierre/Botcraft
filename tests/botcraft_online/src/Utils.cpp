#include "Utils.hpp"
#include "TestManager.hpp"

#include <stdexcept>


std::unique_ptr<Botcraft::ManagersClient> SetupTestBot(const Botcraft::Vector3<double>& offset)
{
	std::string botname;
	std::unique_ptr<Botcraft::ManagersClient> bot = TestManager::GetInstance().GetBot(botname);

	const Botcraft::Position pos = TestManager::GetInstance().GetCurrentOffset() + offset;
	TestManager::GetInstance().Teleport(botname, pos);

	if (!Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(bot->GetWorld()->GetMutex());
			return bot->GetWorld()->IsLoaded(pos);
		}, 5000))
	{
		throw std::runtime_error("Timeout waiting " + botname + " to load surroundings");
	}

	return bot;
}
