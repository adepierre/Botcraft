#include "TestManager.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/AI/Tasks/PathfindingTask.hpp>

bool SameBlock(const Botcraft::Vector3<double>& p1, const Botcraft::Vector3<double>& p2)
{
    return std::floor(p1.x) == std::floor(p2.x) &&
        std::floor(p1.y) == std::floor(p2.y) &&
        std::floor(p1.z) == std::floor(p2.z);
}

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
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    for (size_t i = 0; i < directions.size(); ++i)
    {
        SECTION(directions[i].first)
        {
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0, false, false, 1.0f);
            CHECK(SameBlock(local_player->GetPosition(), init_position + directions[i].second));
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
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    for (size_t i = 0; i < directions.size(); ++i)
    {
        SECTION(directions[i].first)
        {
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0, true, false, 1.0f);
            CHECK(SameBlock(local_player->GetPosition(), init_position + directions[i].second));
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
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    for (size_t i = 0; i < directions.size(); ++i)
    {
        SECTION(directions[i].first)
        {
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0, true, false, 1.0f);
            CHECK(SameBlock(local_player->GetPosition(), init_position + directions[i].second));
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
            const Botcraft::Vector3<double> init_position = local_player->GetPosition();

            REQUIRE(Botcraft::Utilities::WaitForCondition([&]() -> bool
                {
                    return local_player->GetOnGround();
                }, 2000));

            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0, true, false, 1.0f);
            CHECK(SameBlock(local_player->GetPosition(), init_position + directions[i].second));
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
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    for (size_t i = 0; i < directions.size(); ++i)
    {
        SECTION(directions[i].first)
        {
            bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + directions[i].second, 0, 0, 0, true, false, 1.0f);
            CHECK(SameBlock(local_player->GetPosition(), init_position + directions[i].second));
        }
    }
}

TEST_CASE("full pathfinding", "[!mayfail]") // Creative pathfinding is not yet well-supported
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
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 0, true, false, 1.0f);
    CHECK(SameBlock(local_player->GetPosition(), init_position + delta));
    CHECK_THAT(local_player->GetHealth(), Catch::Matchers::WithinAbs(20.0, 0.01));
}

TEST_CASE("hazardous pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(1.0, 1.01, 0.0));
    const Botcraft::Position delta(0, 4, 2);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 0, true, false, 1.0f);

    CHECK(SameBlock(local_player->GetPosition(), init_position + delta));
    CHECK_THAT(local_player->GetHealth(), Catch::Matchers::WithinAbs(20.0, 0.01));
}

TEST_CASE("water walking pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.0, 2.01, 0.0));
    const Botcraft::Position delta(0, 0, 6);
    const Botcraft::Position string_control_check_delta(0, 2, 3);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<Botcraft::World> world = bot->GetWorld();

    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    Botcraft::Position init_position_int = Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z));

    bot->SyncAction(Botcraft::GoTo, init_position_int + delta, 0, 0, 0, true, false, 1.0f);
    CHECK(SameBlock(local_player->GetPosition(), init_position + delta));
    const Botcraft::Blockstate* should_not_be_air = world->GetBlock(init_position_int + string_control_check_delta);
    REQUIRE_FALSE(should_not_be_air == nullptr);
    CHECK_FALSE(should_not_be_air->IsAir());
}

TEST_CASE("ladder walking pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(2.0, 2.01, 0.0));
    const Botcraft::Position delta(0, 0, 6);
    const Botcraft::Position string_control_check_delta(0, 2, 3);

    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    std::shared_ptr<Botcraft::World> world = bot->GetWorld();

    const Botcraft::Vector3<double> init_position = local_player->GetPosition();
    const Botcraft::Position init_position_int = Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z));

    bot->SyncAction(Botcraft::GoTo, init_position_int + delta, 0, 0, 0, true, false, 1.0f);
    CHECK(SameBlock(local_player->GetPosition(), init_position + delta));
    const Botcraft::Blockstate* should_not_be_air = world->GetBlock(init_position_int + string_control_check_delta);
    REQUIRE_FALSE(should_not_be_air == nullptr);
    CHECK_FALSE(should_not_be_air->IsAir());
}

TEST_CASE("speed pathfinding")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(0.0, 1.01, 0.0));
    std::shared_ptr<Botcraft::LocalPlayer> local_player = bot->GetEntityManager()->GetLocalPlayer();
    const std::string& botname = bot->GetNetworkManager()->GetMyName();

    bool sprint = false;
    int speed_effect = 0;
    float botcraft_speed_factor = 1.0f;
    // Expected time is an estimate to check consistency with previous versions. It's not consistent with distance/theoretical speed
    // This is mainly due to the way we travel from block to block instead of from start to goal directly
    float expected_time_s = 0.0f;

    SECTION("no speed")
    {
        speed_effect = 0;
        botcraft_speed_factor = 1.0f;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 5.7f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 4.5f;
        }
    }
    SECTION("botcraft cheaty speed")
    {
        speed_effect = 0;
        botcraft_speed_factor = 1.5f;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 3.9f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 3.1f;
        }
    }
    SECTION("speed I")
    {
        speed_effect = 1;
        botcraft_speed_factor = 1.0f;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 4.8f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 3.8f;
        }
    }
    SECTION("speed II")
    {
        speed_effect = 2;
        botcraft_speed_factor = 1.0f;
        SECTION("walk")
        {
            sprint = false;
            expected_time_s = 4.1f;
        }
        SECTION("sprint")
        {
            sprint = true;
            expected_time_s = 3.2f;
        }
    }

    if (speed_effect > 0)
    {
        // Speed N is given using N-1
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
        MinecraftServer::GetInstance().SendLine("effect give " + botname + " speed 99999 " + std::to_string(speed_effect - 1));
#else
        MinecraftServer::GetInstance().SendLine("effect " + botname + " speed 99999 " + std::to_string(speed_effect - 1));
#endif
        MinecraftServer::GetInstance().WaitLine(".*?: (?:Applied effect Speed|Given Speed \\(ID [0-9]+\\)(?: \\* [0-9]+)?) to " + botname + ".*", 5000);

        CHECK(Botcraft::Utilities::WaitForCondition([&]() {
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

    const Botcraft::Vector3<double> init_position = local_player->GetPosition();

    const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bot->SyncAction(Botcraft::GoTo, Botcraft::Position(std::floor(init_position.x), std::floor(init_position.y), std::floor(init_position.z)) + delta, 0, 0, 0, true, sprint, botcraft_speed_factor);
    CHECK(SameBlock(local_player->GetPosition(), init_position + delta));
    const float time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.0f;
    CHECK_THAT(time_taken, Catch::Matchers::WithinAbs(expected_time_s, 0.2));
}
