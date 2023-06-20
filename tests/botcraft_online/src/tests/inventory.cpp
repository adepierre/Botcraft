#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include <botcraft/AI/Tasks/InventoryTasks.hpp>
#include <botcraft/AI/Tasks/EntitiesTasks.hpp>

#include <botcraft/Game/Inventory/InventoryManager.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/entities/Entity.hpp>
#include <botcraft/Game/Entities/entities/item/ItemEntity.hpp>
#include <botcraft/Game/Entities/entities/npc/VillagerEntity.hpp>

#include <array>


std::string GetItemName(const ProtocolCraft::Slot& slot)
{
    if (slot.IsEmptySlot())
    {
        return "";
    }

#if PROTOCOL_VERSION < 347
    return Botcraft::AssetsManager::getInstance().GetItem({ slot.GetBlockID(), slot.GetItemDamage() })->GetName();
#else
    return Botcraft::AssetsManager::getInstance().GetItem(slot.GetItemID())->GetName();
#endif
}

TEST_CASE("receive item")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 1));
    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 1));

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE_FALSE(inventory_manager->GetHotbarSelected().IsEmptySlot());
    }
}

TEST_CASE("swap slots")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));
    CHECK(GiveItem(bot, "minecraft:diamond_pickaxe", "Diamond Pickaxe", 1));

    bot->SyncAction(Botcraft::SwapItemsInContainer, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, Botcraft::Window::INVENTORY_HOTBAR_START + 1);

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START)) == "minecraft:diamond_pickaxe");
        CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + 1)) == "minecraft:stick");
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + 1).GetItemCount() == 5);
    }
}

TEST_CASE("drop items")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
    const Botcraft::Vector3<double> position = Botcraft::Vector3<double>(0.5, 0.0, 0.5) + TestManager::GetInstance().GetCurrentOffset();

    SECTION("drop 1")
    {
        // Drop 1 stick
        bot->SyncAction(Botcraft::DropItemsFromContainer, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, 4);

        // We still have 4 sticks
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START)) == "minecraft:stick");
            CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START).GetItemCount() == 4);
        }
        // There is a stick entity on the floor
        CHECK(Botcraft::WaitForCondition([&]()
            {
                std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
                for (const auto& [id, e] : entity_manager->GetEntities())
                {
                    // If this is an item entity and closer than 3.5 blocks
                    if (e->GetType() == Botcraft::ItemEntity::GetClassType() &&
                        e->GetPosition().SqrDist(position) < 12.25)
                    {
                        std::shared_ptr<Botcraft::ItemEntity> floor_items = std::dynamic_pointer_cast<Botcraft::ItemEntity>(e);
                        return
                            GetItemName(floor_items->GetDataItem()) == "minecraft:stick" &&
                            floor_items->GetDataItem().GetItemCount() == 1;
                    }
                }
                return false;
            }, 2000));
    }
    SECTION("drop all")
    {
        // Drop all sticks
        bot->SyncAction(Botcraft::DropItemsFromContainer, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, 0);

        // We have nothing now
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START).IsEmptySlot());
        }
        // There is a stick entity on the floor
        CHECK(Botcraft::WaitForCondition([&]()
            {
                std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
                for (const auto& [id, e] : entity_manager->GetEntities())
                {
                    // If this is an item entity and closer than 3.5 blocks
                    if (e->GetType() == Botcraft::ItemEntity::GetClassType() &&
                        e->GetPosition().SqrDist(position) < 12.25)
                    {
                        std::shared_ptr<Botcraft::ItemEntity> floor_items = std::dynamic_pointer_cast<Botcraft::ItemEntity>(e);
                        return
                            GetItemName(floor_items->GetDataItem()) == "minecraft:stick" &&
                            floor_items->GetDataItem().GetItemCount() == 5;
                    }
                }
                return false;
            }, 2000));
    }
}

TEST_CASE("put one item")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    for (int i = 1; i < 5; ++i)
    {
        bot->SyncAction(Botcraft::PutOneItemInContainerSlot, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, Botcraft::Window::INVENTORY_HOTBAR_START + i);
    }

    for (int i = 0; i < 5; ++i)
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + i)) == "minecraft:stick");
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + i).GetItemCount() == 1);
    }
}

TEST_CASE("set in hand")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 1));
    CHECK(GiveItem(bot, "minecraft:diamond_pickaxe", "Diamond Pickaxe", 1));

    bot->SyncAction(Botcraft::SetItemInHand, "minecraft:diamond_pickaxe", Botcraft::Hand::Right);

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE(GetItemName(inventory_manager->GetHotbarSelected()) == "minecraft:diamond_pickaxe");
    }
}

TEST_CASE("place block")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::World> world = bot->GetWorld();

    CHECK(GiveItem(bot, "minecraft:diamond_block", "Block of Diamond", 1));
    Botcraft::Position pos;

    SECTION("no mid air")
    {
        pos = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1);
        bot->SyncAction(Botcraft::PlaceBlock, "minecraft:diamond_block", pos, Botcraft::PlayerDiggingFace::Up, true, false);
    }
    SECTION("mid air")
    {
        pos = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 1, 1);
        bot->SyncAction(Botcraft::PlaceBlock, "minecraft:diamond_block", pos, Botcraft::PlayerDiggingFace::Up, true, true);
    }

    {
        std::lock_guard<std::mutex> lock(world->GetMutex());
        const Botcraft::Block* block = world->GetBlock(pos);
        REQUIRE(block);
        REQUIRE(block->GetBlockstate()->GetName() == "minecraft:diamond_block");
    }
}

TEST_CASE("eat")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:golden_apple", "Golden Apple", 1));

    bot->SyncAction(Botcraft::Eat, "minecraft:golden_apple", true);

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    // Check we don't have a golden apple in main or off hand
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE(inventory_manager->GetHotbarSelected().IsEmptySlot());
        REQUIRE(inventory_manager->GetOffHand().IsEmptySlot());
    }
}

TEST_CASE("container")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const Botcraft::Position chest = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1);

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    short container_id = -1;
    std::shared_ptr<Botcraft::Window> container;
    bot->SyncAction(Botcraft::OpenContainer, chest);
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        container_id = inventory_manager->GetFirstOpenedWindowId();
        container = inventory_manager->GetWindow(container_id);
    }
    REQUIRE(container_id != -1);

    SECTION("put 1")
    {
        bot->SyncAction(Botcraft::PutOneItemInContainerSlot, container_id, container->GetFirstPlayerInventorySlot() + Botcraft::Window::INVENTORY_HOTBAR_START - Botcraft::Window::INVENTORY_STORAGE_START, 0);
        bot->SyncAction(Botcraft::CloseContainer, container_id);
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            REQUIRE(GetItemName(inventory_manager->GetHotbarSelected()) == "minecraft:stick");
            REQUIRE(inventory_manager->GetHotbarSelected().GetItemCount() == 4);
        }
        container_id = -1;
        bot->SyncAction(Botcraft::OpenContainer, chest);
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            container_id = inventory_manager->GetFirstOpenedWindowId();
            container = inventory_manager->GetWindow(container_id);
        }
        REQUIRE(container_id != -1);
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            REQUIRE(GetItemName(container->GetSlot(0)) == "minecraft:stick");
            REQUIRE(container->GetSlot(0).GetItemCount() == 1);
        }
    }
    SECTION("put all")
    {
        bot->SyncAction(Botcraft::SwapItemsInContainer, container_id, container->GetFirstPlayerInventorySlot() + Botcraft::Window::INVENTORY_HOTBAR_START - Botcraft::Window::INVENTORY_STORAGE_START, 0);
        bot->SyncAction(Botcraft::CloseContainer, container_id);
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            REQUIRE(inventory_manager->GetHotbarSelected().IsEmptySlot());
        }
        container_id = -1;
        bot->SyncAction(Botcraft::OpenContainer, chest);
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            container_id = inventory_manager->GetFirstOpenedWindowId();
            container = inventory_manager->GetWindow(container_id);
        }
        REQUIRE(container_id != -1);
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            REQUIRE(GetItemName(container->GetSlot(0)) == "minecraft:stick");
            REQUIRE(container->GetSlot(0).GetItemCount() == 5);
        }
    }

    bot->SyncAction(Botcraft::CloseContainer, container_id);
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE(inventory_manager->GetFirstOpenedWindowId() == -1);
    }
}

#if PROTOCOL_VERSION > 451
TEST_CASE("trade")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();

    const Botcraft::Vector3<double> pos = Botcraft::Vector3<double>(1.5, 0, 1.5) + TestManager::GetInstance().GetCurrentOffset();

    std::shared_ptr<Botcraft::Entity> entity;
    REQUIRE(Botcraft::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
            for (const auto& [k, v] : entity_manager->GetEntities())
            {
                if (v->GetPosition().SqrDist(pos) < 0.2 &&
                    v->GetType() == Botcraft::VillagerEntity::GetClassType())
                {
                    entity = v;
                    return true;
                }
            }
            return false;
        }, 2000));
    REQUIRE(entity != nullptr);
    REQUIRE(GiveItem(bot, "minecraft:stick", "Stick", 1));

    bot->SyncAction(Botcraft::InteractEntity, entity->GetEntityID(), Botcraft::Hand::Right, true);
    bot->SyncAction(Botcraft::TradeName, "minecraft:stick", false, -1);
    bot->SyncAction(Botcraft::TradeName, "minecraft:enchanted_book", true, -1);
    bot->SyncAction(Botcraft::CloseContainer, -1);

    // Wait for the player inventory to update
    CHECK(Botcraft::WaitForCondition([&]()
        {
            std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
            return !inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).IsEmptySlot();
        }, 2000));

    bot->SyncAction(Botcraft::SetItemInHand, "minecraft:enchanted_book", Botcraft::Hand::Right);
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE(GetItemName(inventory_manager->GetHotbarSelected()) == "minecraft:enchanted_book");
        REQUIRE(inventory_manager->GetHotbarSelected().GetItemCount() == 1);
    }
}
#endif

TEST_CASE("craft")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const Botcraft::Position table = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1);

    CHECK(GiveItem(bot, "minecraft:diamond_block", "Block of Diamond", 1));

    const std::array<std::string, 3> empty = { "", "", "" };
    const std::array<std::array<std::string, 3>, 3> decraft_recipe = {
        empty,
        empty,
        {"minecraft:diamond_block", "", ""}
    };

    bot->SyncAction(Botcraft::CraftNamed, decraft_recipe, true);
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START)) == "minecraft:diamond");
        REQUIRE(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).GetItemCount() == 9);
    }

    short container_id = -1;
    std::shared_ptr<Botcraft::Window> container;
    bot->SyncAction(Botcraft::OpenContainer, table);
    {
        container_id = inventory_manager->GetFirstOpenedWindowId();
        container = inventory_manager->GetWindow(container_id);
    }
    REQUIRE(container_id != -1);

    const std::array<std::string, 3> diamond_line = { "minecraft:diamond", "minecraft:diamond", "minecraft:diamond" };
    const std::array<std::array<std::string, 3>, 3> craft_recipe = {
        diamond_line,
        diamond_line,
        diamond_line
    };

    bot->SyncAction(Botcraft::CraftNamed, craft_recipe, false);
    bot->SyncAction(Botcraft::CloseContainer, -1);

    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        REQUIRE(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START)) == "minecraft:diamond_block");
        REQUIRE(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).GetItemCount() == 1);
    }
}

TEST_CASE("sort inventory")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    for (int i = 1; i < 5; ++i)
    {
        bot->SyncAction(Botcraft::PutOneItemInContainerSlot, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, Botcraft::Window::INVENTORY_HOTBAR_START + i);
    }

    bot->SyncAction(Botcraft::SortInventory);

    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START)) == "minecraft:stick");
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START).GetItemCount() == 5);
    }

    for (int i = 1; i < 5; ++i)
    {
        std::lock_guard<std::mutex> lock(inventory_manager->GetMutex());
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + i).IsEmptySlot());
    }
}
