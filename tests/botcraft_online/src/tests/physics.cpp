#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <botcraft/Network/NetworkManager.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/LocalPlayer.hpp>
#include <botcraft/Utilities/SleepUtilities.hpp>

#include <sstream>

TEST_CASE("gravity")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot(Botcraft::Vector3<double>(1.0, 2.0, 1.0));
    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetLocalPlayer();

    CHECK(Botcraft::Utilities::WaitForCondition([&]()
        {
            return !local_player->GetOnGround();
        }, 5000));
    CHECK(Botcraft::Utilities::WaitForCondition([&]()
        {
            return local_player->GetPosition().y < 2.2 && local_player->GetOnGround();
        }, 5000));
    const Botcraft::Vector3<double> target_pos = Botcraft::Vector3<double>(1.5, 0.0, 1.5) + TestManager::GetInstance().GetCurrentOffset();
    CHECK(local_player->GetPosition().SqrDist(target_pos) < 0.2);
}

TEST_CASE("collisions")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot(Botcraft::Vector3<double>(2.5, 1.51, 2.5));

    std::vector<std::tuple<std::string, float, double, double, Botcraft::Vector3<double>>> directions = {
        {"south", 0.0f, 1.0, 0.0, Botcraft::Vector3<double>(0.0, 0.0, 1.0)},
        {"north", 0.0f, -1.0, 0.0, Botcraft::Vector3<double>(0.0, 0.0, -1.0)},
        {"east", 0.0f, 0.0, 1.0, Botcraft::Vector3<double>(1.0, 0.0, 0.0)},
        {"west", 0.0f, 0.0, -1.0, Botcraft::Vector3<double>(-1.0, 0.0, 0.0)},
        {"south facing east", -90.0f, 0.0, -1.0, Botcraft::Vector3<double>(0.0, 0.0, 1.0)},
        {"north facing east", -90.0f, 0.0, 1.0, Botcraft::Vector3<double>(0.0, 0.0, -1.0)},
        {"east facing east", -90.0f, 1.0, 0.0, Botcraft::Vector3<double>(1.0, 0.0, 0.0)},
        {"west facing east", -90.0f, -1.0, 0.0, Botcraft::Vector3<double>(-1.0, 0.0, 0.0)},
    };

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetLocalPlayer();
    // Wait the bot to be on ground
    Botcraft::Utilities::WaitForCondition([&]()
        {
            return local_player->GetY() - TestManager::GetInstance().GetCurrentOffset().y < 1.2 && local_player->GetOnGround();
        }, 5000);
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();
    for (size_t i = 0; i < directions.size(); ++i)
    {
        SECTION(std::get<0>(directions[i]))
        {
            local_player->SetYaw(std::get<1>(directions[i]));
            // Walk in the given direction for 40 ticks (2s)
            for (size_t j = 0; j < 40; ++j)
            {
                local_player->SetInputsForward(std::get<2>(directions[i]));
                local_player->SetInputsLeft(std::get<3>(directions[i]));
                Botcraft::Utilities::WaitForCondition([&local_player]() -> bool
                    {
                        return !local_player->GetDirtyInputs();
                    }, 100);
            }
            // Check the wall stopped the walk
            CHECK(local_player->GetPosition().SqrDist(init_position + std::get<4>(directions[i]) * 1.2) < 0.2);
        }
    }
}
