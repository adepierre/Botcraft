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
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0.0f, false);
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
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0.0f, true);
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
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0.0f, true);
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
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0.0f, true);
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
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0.0f, true);
            {
                std::lock_guard<std::mutex> lock(local_player->GetMutex());
                CHECK_THAT(local_player->GetPosition().SqrDist(init_position + directions[i].second), Catch::Matchers::WithinAbs(0.0, 0.1));
            }
        }
    }
}

TEST_CASE("full pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot;
    SECTION("survival")
    {
        bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(0.0, 1.01, 0.0));
    }
    SECTION("creative")
    {
        bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(0.0, 1.01, 0.0), Botcraft::GameType::Creative);
    }

    const Botcraft::Position delta(2, 3, 24);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    Botcraft::Vector3<double> init_position;
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }

    bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 0.0f, true);
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        CHECK_THAT(local_player->GetPosition().SqrDist(init_position + delta), Catch::Matchers::WithinAbs(0.0, 0.1));
        CHECK_THAT(local_player->GetHealth(), Catch::Matchers::WithinAbs(20.0, 0.01));
    }
}

TEST_CASE("hazardous pathfinding")
{
    Botcraft::GameType gamemode = Botcraft::GameType::Survival;
    float expected_time_s = 0.0f;

    SECTION("creative")
    {
        gamemode = Botcraft::GameType::Creative;
        // Can take direct route through lava ==> faster
        expected_time_s = 3.0f;
    }

    SECTION("survival")
    {
        gamemode = Botcraft::GameType::Survival;
        // Has to avoid lava and magma blocks ==> slower
        expected_time_s = 4.7f;
    }

    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(1.0, 1.01, 0.0), gamemode);
    const Botcraft::Position delta(0, 4, 2);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    Botcraft::Vector3<double> init_position;
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }

    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 0.0f, true);
    {
        const float time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        CHECK_THAT(local_player->GetPosition().SqrDist(init_position + delta), Catch::Matchers::WithinAbs(0.0, 0.1));
        CHECK_THAT(local_player->GetHealth(), Catch::Matchers::WithinAbs(20.0, 0.01));
        CHECK_THAT(time_taken, Catch::Matchers::WithinAbs(expected_time_s, 0.5));
    }
}

TEST_CASE("water walking pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.0, 2.01, 0.0));
    const Botcraft::Position delta(0, 0, 6);
    const Botcraft::Position string_control_check_delta(0, 2, 3);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<Botcraft::World> world = bot->GetWorld();

    Botcraft::Vector3<double> init_position;
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }
    Botcraft::Position init_position_int = Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z));

    bot->SyncAction(Botcraft::GoTo, init_position_int + delta, 0, 0, 0.0f, true);
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        CHECK_THAT(local_player->GetPosition().SqrDist(init_position + delta), Catch::Matchers::WithinAbs(0.0, 0.1));
        {
            std::lock_guard<std::mutex> lock(world->GetMutex());
            const Botcraft::Block* should_be_air = world->GetBlock(init_position_int + string_control_check_delta);
            CHECK((should_be_air == nullptr || should_be_air->GetBlockstate()->IsAir())); // Extra parenthesis as || is not supported without in catch2
        }
    }
}

TEST_CASE("ladder walking pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.0, 2.01, 0.0));
    const Botcraft::Position delta(0, 0, 6);
    const Botcraft::Position string_control_check_delta(0, 2, 3);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<Botcraft::World> world = bot->GetWorld();

    Botcraft::Vector3<double> init_position;
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }
    Botcraft::Position init_position_int = Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z));

    bot->SyncAction(Botcraft::GoTo, init_position_int + delta, 0, 0, 0.0f, true);
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        CHECK_THAT(local_player->GetPosition().SqrDist(init_position + delta), Catch::Matchers::WithinAbs(0.0, 0.1));
        {
            std::lock_guard<std::mutex> lock(world->GetMutex());
            const Botcraft::Block* should_not_be_air = world->GetBlock(init_position_int + string_control_check_delta);
            REQUIRE_FALSE(should_not_be_air == nullptr);
            CHECK_FALSE(should_not_be_air->GetBlockstate()->IsAir());
        }
    }
}

TEST_CASE("speed pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(0.0, 1.01, 0.0));
    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    const std::string& botname = bot->GetNetworkManager()->GetMyName();

    bool sprint = false;
    int speed_effect = 0;
    // Expected time is an estimate to check consistency with previous versions. It's not consistent with distance/theoretical speed
    // This is mainly due to the way we travel from block to block instead of from start to goal directly
    float expected_time_s = 0.0f;

    SECTION("no speed")
    {
        speed_effect = 0;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 7.67f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 6.46f;
            bot->SyncAction(Botcraft::StartSprinting);
        }
    }
    SECTION("speed I")
    {
        speed_effect = 1;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 7.18f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 6.02f;
            bot->SyncAction(Botcraft::StartSprinting);
        }
    }
    SECTION("speed II")
    {
        speed_effect = 2;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 6.1f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 4.9f;
            bot->SyncAction(Botcraft::StartSprinting);
        }
    }

    if (speed_effect > 0)
    {
        // Speed N is given using N-1
#if PROTOCOL_VERSION > 340
        MinecraftServer::GetInstance().SendLine("effect give " + botname + " speed 99999 " + std::to_string(speed_effect - 1));
#else
        MinecraftServer::GetInstance().SendLine("effect " + botname + " speed 99999 " + std::to_string(speed_effect - 1));
#endif
        MinecraftServer::GetInstance().WaitLine(".*?: (?:Applied effect Speed|Given Speed \\(ID [0-9]+\\)(?: \\* [0-9]+)?) to " + botname + ".*", 5000);

        CHECK(Botcraft::Utilities::WaitForCondition([&]() {
            std::lock_guard<std::mutex> lock(bot->GetEntityManager()->GetMutex());
            for (const Botcraft::EntityEffect& effect : local_player->GetEffects())
            {
                if (effect.type == Botcraft::EntityEffectType::Speed)
                {
                    return true;
                }
            }
            return false;
            }, 5000));
    }

    const Botcraft::Position delta(0, 0, 24);

    Botcraft::Vector3<double> init_position;
    {
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        init_position = local_player->GetPosition();
    }

    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 0.0f, true);
    {
        const float time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
        std::lock_guard<std::mutex> lock(local_player->GetMutex());
        CHECK_THAT(local_player->GetPosition().SqrDist(init_position + delta), Catch::Matchers::WithinAbs(0.0, 0.1));
        CHECK_THAT(time_taken, Catch::Matchers::WithinAbs(expected_time_s, 0.5));
    }
}
