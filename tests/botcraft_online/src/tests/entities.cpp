#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/entities/Entity.hpp>
#include <botcraft/Game/Entities/entities/monster/CreeperEntity.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>

#include <botcraft/AI/Tasks/EntitiesTasks.hpp>

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
#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
            MinecraftServer::GetInstance().WaitLine(".*?: Summoned new.*", 5000);
#else
            MinecraftServer::GetInstance().WaitLine(".*?: Object successfully summoned.*", 5000);
#endif
            std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
            std::shared_ptr<Botcraft::Entity> entity;
            // Wait for the entity to be registered on bot side
            REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
                {
                    auto entities = entity_manager->GetEntities();
                    for (const auto& [k, v] : *entities)
                    {
                        if (v->GetPosition().SqrDist(pos) < 0.2)
                        {
                            entity = v;
                            return true;
                        }
                    }
                    return false;
                }, 5000));
            REQUIRE(entity != nullptr);
            CHECK(entity->GetName() == t);
        }
    }
}

TEST_CASE("entity interact")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::string& botname = bot->GetNetworkManager()->GetMyName();
    const Botcraft::Vector3<double> pos = Botcraft::Vector3<double>(1.5, 0, 1.5) + TestManager::GetInstance().GetCurrentOffset();

    // Give flint and steel to bot
    MinecraftServer::GetInstance().SendLine("give " + botname + " flint_and_steel");
    MinecraftServer::GetInstance().WaitLine(".*?: (?:Given|Gave 1) \\[Flint and Steel\\](?: \\* 1)? to " + botname + ".*", 5000);
    Botcraft::Utilities::WaitForCondition([&]()
        {
            return !bot->GetInventoryManager()->GetHotbarSelected().IsEmptySlot();
        }, 5000);

    // Wait for the entity to be registered on bot side
    std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
    std::shared_ptr<Botcraft::Entity> entity;
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            auto entities = entity_manager->GetEntities();
            for (const auto& [k, v] : *entities)
            {
                if (v->GetPosition().SqrDist(pos) < 0.2)
                {
                    entity = v;
                    return true;
                }
            }
            return false;
        }, 5000));
    REQUIRE(entity != nullptr);
    CHECK(entity->GetName() == "creeper");

    bot->SyncAction(5000, Botcraft::InteractEntity, entity->GetEntityID(), Botcraft::Hand::Main, true);

    // Wait for the creeper to be ignited
    std::shared_ptr<Botcraft::CreeperEntity> creeper = std::dynamic_pointer_cast<Botcraft::CreeperEntity>(entity);
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            return creeper->GetDataIsIgnited();
        }, 5000));

    // Wait for the creeper to explode
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            return entity_manager->GetEntity(creeper->GetEntityID()) == nullptr;
        }, 5000));
}

TEST_CASE("player names")
{
    // Setup two bots and check their names are present in the "tab list"
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();
    std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
    CHECK(bot->GetNetworkManager()->GetMyName() == bot->GetPlayerName(entity_manager->GetLocalPlayer()->GetUUID()));

    const Botcraft::Vector3<double> bot_pos = entity_manager->GetLocalPlayer()->GetPosition();
    std::unique_ptr<Botcraft::ManagersClient> bot2 = SetupTestBot();
    std::shared_ptr<Botcraft::Entity> bot2_entity;
    // Find bot2 in bot entities
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            for (const auto& [id, e] : *entity_manager->GetEntities())
            {
                if (id == bot2->GetLocalPlayer()->GetEntityID())
                {
                    bot2_entity = e;
                    return true;
                }
            }
            return false;
        }, 5000));
    // Check bot sees bot2 with it's name
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            return bot->GetPlayerName(bot2_entity->GetUUID()) == bot2->GetNetworkManager()->GetMyName();
        }, 5000));

    bot2->Disconnect();
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            return bot->GetPlayerName(bot2_entity->GetUUID()) == "";
        }, 5000));
}
