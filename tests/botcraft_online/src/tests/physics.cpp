#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <botcraft/Network/NetworkManager.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>

#include <sstream>

TEST_CASE("gravity")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot(Botcraft::Vector3<double>(1.0, 2.0, 1.0));
    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();

    CHECK_FALSE(local_player->GetOnGround());
    CHECK(Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            return local_player->GetPosition().y < 2.2 && local_player->GetOnGround();
        }, 5000));
    const Botcraft::Vector3<double> target_pos = Botcraft::Vector3<double>(1.5, 0.0, 1.5) + TestManager::GetInstance().GetCurrentOffset();
    std::lock_guard<std::mutex> lock(local_player->GetMutex());
    CHECK(local_player->GetPosition().SqrDist(target_pos) < 0.2);
}

TEST_CASE("collisions")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot(Botcraft::Vector3<double>(2.5, 1.51, 2.5));

    std::vector<std::pair<std::string, Botcraft::Vector3<double>>> directions = {
        {"south", Botcraft::Vector3<double>(0.0, 0.0, 1.0)},
        {"north", Botcraft::Vector3<double>(0.0, 0.0, -1.0)},
        {"east", Botcraft::Vector3<double>(1.0, 0.0, 0.0)},
        {"west", Botcraft::Vector3<double>(-1.0, 0.0, 0.0)},
    };

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    // Wait the bot to be on ground
    Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            return local_player->GetY() - TestManager::GetInstance().GetCurrentOffset().y < 1.2;
        }, 5000);
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();
    for (size_t i = 0; i < directions.size(); ++i)
    {
        SECTION(directions[i].first)
        {
            // Walk in the given direction for a total of 2m
            for (size_t j = 0; j < 20; ++j)
            {
                {
                    std::lock_guard<std::mutex> lock(local_player->GetMutex());
                    local_player->AddPlayerInputs(directions[i].second * 0.1);
                }
                Botcraft::Utilities::SleepFor(std::chrono::milliseconds(30));
            }
            // Check the wall stopped the walk
            std::lock_guard<std::mutex> lock(local_player->GetMutex());
            CHECK(local_player->GetPosition().SqrDist(init_position + directions[i].second * 1.2) < 0.2);
        }
    }
}
