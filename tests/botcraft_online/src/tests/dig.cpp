#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/AI/Tasks/DigTask.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>

void TestDig(std::unique_ptr<Botcraft::SimpleBehaviourClient>& bot, const Botcraft::Position& pos, const double time_s)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bot->SyncAction(Botcraft::Dig, pos, true, Botcraft::PlayerDiggingFace::North);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Check the block is now air
    std::shared_ptr<Botcraft::World> world = bot->GetWorld();
    CHECK(Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(world->GetMutex());
            const Botcraft::Block* block = world->GetBlock(pos);
            return block == nullptr || block->GetBlockstate()->IsAir();
        }, 5000));

    const double elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;
    // We are rather large here to compensate lags from delays in tree swapping/executing
    CHECK_THAT(elapsed_time, Catch::Matchers::WithinAbs(time_s, 0.2));
}

TEST_CASE("dig pickaxe")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(1,0,1));
    // Wait to be on ground
    Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(bot->GetEntityManager()->GetLocalPlayer()->GetMutex());
            return bot->GetEntityManager()->GetLocalPlayer()->GetOnGround();
        }, 5000);

    const std::string& botname = bot->GetNetworkManager()->GetMyName();

    const Botcraft::Position chest = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(0, 0, 2);
    const Botcraft::Position stone = chest + Botcraft::Position(1, 0, 0);
    const Botcraft::Position iron = stone + Botcraft::Position(1, 0, 0);

    SECTION("no haste")
    {
        SECTION("golden pick")
        {
            GiveItem(bot, "golden_pickaxe", "Golden Pickaxe");
            TestDig(bot, chest, 3.75);
            TestDig(bot, stone, 0.2);
            TestDig(bot, iron, 2.1);
        }

        SECTION("diamond pick")
        {
            GiveItem(bot, "diamond_pickaxe", "Diamond Pickaxe");
            TestDig(bot, chest, 3.75);
            TestDig(bot, stone, 0.3);
            TestDig(bot, iron, 0.95);
        }
    }

    SECTION("haste")
    {
#if PROTOCOL_VERSION > 340
        MinecraftServer::GetInstance().SendLine("effect give " + botname + " haste 99999 2");
#else
        MinecraftServer::GetInstance().SendLine("effect " + botname + " haste 99999 2");
#endif
        MinecraftServer::GetInstance().WaitLine(".*?: (?:Applied effect Haste|Given Haste \\(ID [0-9]+\\)(?: \\* [0-9]+)?) to " + botname + ".*", 5000);

        SECTION("golden pick")
        {
            GiveItem(bot, "golden_pickaxe", "Golden Pickaxe");
            TestDig(bot, chest, 2.35);
            TestDig(bot, stone, 0.15);
            TestDig(bot, iron, 1.35);
        }

        SECTION("diamond pick")
        {
            GiveItem(bot, "diamond_pickaxe", "Diamond Pickaxe");
            TestDig(bot, chest, 2.35);
            TestDig(bot, stone, 0.2);
            TestDig(bot, iron, 0.6);
        }
    }
}

TEST_CASE("dig underwater")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(1, 0, 1));
    Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(bot->GetEntityManager()->GetLocalPlayer()->GetMutex());
            return bot->GetEntityManager()->GetLocalPlayer()->GetOnGround();
        }, 5000);
    const std::string& botname = bot->GetNetworkManager()->GetMyName();

    const Botcraft::Position dirt = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(0, 0, 2);
    const Botcraft::Position stone = dirt + Botcraft::Position(1, 0, 0);
    const Botcraft::Position iron = stone + Botcraft::Position(1, 0, 0);

    SECTION("haste")
    {
#if PROTOCOL_VERSION > 340
        MinecraftServer::GetInstance().SendLine("effect give " + botname + " haste 99999 2");
#else
        MinecraftServer::GetInstance().SendLine("effect " + botname + " haste 99999 2");
#endif
        MinecraftServer::GetInstance().WaitLine(".*?: (?:Applied effect Haste|Given Haste \\(ID [0-9]+\\)(?: \\* [0-9]+)?) to " + botname + ".*", 5000);

        SECTION("golden pick")
        {
            GiveItem(bot, "golden_pickaxe", "Golden Pickaxe");
            TestDig(bot, dirt, 2.35);
            TestDig(bot, stone, 0.6);
            TestDig(bot, iron, 6.55);
        }

        SECTION("diamond pick")
        {
            GiveItem(bot, "diamond_pickaxe", "Diamond Pickaxe");
            TestDig(bot, dirt, 2.35);
            TestDig(bot, stone, 0.9);
            TestDig(bot, iron, 2.95);
        }
    }
}

TEST_CASE("dig shears")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>(Botcraft::Vector3<double>(1, 0, 1));
    Botcraft::Utilities::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(bot->GetEntityManager()->GetLocalPlayer()->GetMutex());
            return bot->GetEntityManager()->GetLocalPlayer()->GetOnGround();
        }, 5000);

    const Botcraft::Position dirt = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(0, 0, 2);
    const Botcraft::Position leaves = dirt + Botcraft::Position(1, 0, 0);
    const Botcraft::Position cobweb = leaves + Botcraft::Position(1, 0, 0);

    SECTION("shears")
    {
        GiveItem(bot, "shears", "Shears");
        TestDig(bot, dirt, 0.75);
        TestDig(bot, leaves, 0.0);
        TestDig(bot, cobweb, 0.4);
    }

    SECTION("sword")
    {
        GiveItem(bot, "iron_sword", "Iron Sword");
        TestDig(bot, dirt, 0.75);
        TestDig(bot, leaves, 0.2);
        TestDig(bot, cobweb, 0.4);
    }
}
