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

    return Botcraft::AssetsManager::getInstance().GetItem(slot.GetItemID())->GetName();
}

TEST_CASE("receive item")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 1));
    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 1));

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    REQUIRE_FALSE(inventory_manager->GetHotbarSelected().IsEmptySlot());
}

TEST_CASE("swap slots")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));
    CHECK(GiveItem(bot, "minecraft:diamond_pickaxe", "Diamond Pickaxe", 1));

    bot->SyncAction(5000, Botcraft::SwapItemsInContainer, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, Botcraft::Window::INVENTORY_HOTBAR_START + 1);

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START)) == "minecraft:diamond_pickaxe");
    CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + 1)) == "minecraft:stick");
    CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + 1).GetItemCount() == 5);
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
        bot->SyncAction(5000, Botcraft::DropItemsFromContainer, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, 4);

        // We still have 4 sticks
        CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START)) == "minecraft:stick");
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START).GetItemCount() == 4);
        // There is a stick entity on the floor
        CHECK(Botcraft::Utilities::WaitForCondition([&]()
            {
                auto entities = entity_manager->GetEntities();
                for (const auto& [id, e] : *entities)
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
            }, 5000));
    }
    SECTION("drop all")
    {
        // Drop all sticks
        bot->SyncAction(5000, Botcraft::DropItemsFromContainer, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, 0);

        // We have nothing now
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START).IsEmptySlot());
        // There is a stick entity on the floor
        CHECK(Botcraft::Utilities::WaitForCondition([&]()
            {
                auto entities = entity_manager->GetEntities();
                for (const auto& [id, e] : *entities)
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
            }, 5000));
    }
}

TEST_CASE("put one item")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    for (int i = 1; i < 5; ++i)
    {
        bot->SyncAction(5000, Botcraft::PutOneItemInContainerSlot, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, Botcraft::Window::INVENTORY_HOTBAR_START + i);
    }

    for (int i = 0; i < 5; ++i)
    {
        CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + i)) == "minecraft:stick");
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + i).GetItemCount() == 1);
    }
}

TEST_CASE("set in hand")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 1));
    CHECK(GiveItem(bot, "minecraft:diamond_pickaxe", "Diamond Pickaxe", 1));

    bot->SyncAction(5000, Botcraft::SetItemInHand, "minecraft:diamond_pickaxe", Botcraft::Hand::Right);

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    {
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
        bot->SyncAction(5000, Botcraft::PlaceBlock, "minecraft:diamond_block", pos, Botcraft::PlayerDiggingFace::Up, true, false);
    }
    SECTION("mid air")
    {
        pos = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 1, 1);
        bot->SyncAction(5000, Botcraft::PlaceBlock, "minecraft:diamond_block", pos, Botcraft::PlayerDiggingFace::Up, true, true);
    }
    SECTION("automatic face detection")
    {
        pos = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1);
        bot->SyncAction(5000, Botcraft::PlaceBlock, "minecraft:diamond_block", pos, std::nullopt, true, false);
    }

    const Botcraft::Blockstate* block = world->GetBlock(pos);
    REQUIRE(block != nullptr);
    REQUIRE(block->GetName() == "minecraft:diamond_block");
}

TEST_CASE("eat")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

    CHECK(GiveItem(bot, "minecraft:golden_apple", "Golden Apple", 1));

    bot->SyncAction(5000, Botcraft::Eat, "minecraft:golden_apple", true);

    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    // Check we don't have a golden apple in main or off hand
    REQUIRE(inventory_manager->GetHotbarSelected().IsEmptySlot());
    REQUIRE(inventory_manager->GetOffHand().IsEmptySlot());
}

TEST_CASE("container")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const Botcraft::Position chest = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1);

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    bot->SyncAction(5000, Botcraft::OpenContainer, chest);
    short container_id = inventory_manager->GetFirstOpenedWindowId();
    std::shared_ptr<Botcraft::Window> container = inventory_manager->GetWindow(container_id);
    REQUIRE(container_id != -1);

    SECTION("put 1")
    {
        bot->SyncAction(5000, Botcraft::PutOneItemInContainerSlot, container_id, container->GetFirstPlayerInventorySlot() + Botcraft::Window::INVENTORY_HOTBAR_START - Botcraft::Window::INVENTORY_STORAGE_START, 0);
        bot->SyncAction(5000, Botcraft::CloseContainer, container_id);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        // If <1.17 we need to wait for the server to send the
        // updated player inventory content after closing the container
        REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
            {
                if (GetItemName(inventory_manager->GetHotbarSelected()) == "minecraft:stick" &&
                    inventory_manager->GetHotbarSelected().GetItemCount() == 4)
                {
                    return true;
                }
                return false;
            }, 5000));
#else
        REQUIRE(GetItemName(inventory_manager->GetHotbarSelected()) == "minecraft:stick");
        REQUIRE(inventory_manager->GetHotbarSelected().GetItemCount() == 4);
#endif
        container_id = -1;
        bot->SyncAction(5000, Botcraft::OpenContainer, chest);
        container_id = inventory_manager->GetFirstOpenedWindowId();
        container = inventory_manager->GetWindow(container_id);
        REQUIRE(container_id != -1);
        REQUIRE(GetItemName(container->GetSlot(0)) == "minecraft:stick");
        REQUIRE(container->GetSlot(0).GetItemCount() == 1);
    }
    SECTION("put all")
    {
        bot->SyncAction(5000, Botcraft::SwapItemsInContainer, container_id, container->GetFirstPlayerInventorySlot() + Botcraft::Window::INVENTORY_HOTBAR_START - Botcraft::Window::INVENTORY_STORAGE_START, 0);
        bot->SyncAction(5000, Botcraft::CloseContainer, container_id);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        // If <1.17 we need to wait for the server to send the
        // updated player inventory content after closing the container
        REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
            {
                if (inventory_manager->GetHotbarSelected().IsEmptySlot())
                {
                    return true;
                }
                return false;
            }, 5000));
#else
        REQUIRE(inventory_manager->GetHotbarSelected().IsEmptySlot());
#endif
        container_id = -1;
        bot->SyncAction(5000, Botcraft::OpenContainer, chest);
        container_id = inventory_manager->GetFirstOpenedWindowId();
        container = inventory_manager->GetWindow(container_id);
        REQUIRE(container_id != -1);
        REQUIRE(GetItemName(container->GetSlot(0)) == "minecraft:stick");
        REQUIRE(container->GetSlot(0).GetItemCount() == 5);
    }

    bot->SyncAction(5000, Botcraft::CloseContainer, container_id);
    REQUIRE(inventory_manager->GetFirstOpenedWindowId() == -1);
}

#if PROTOCOL_VERSION > 451 /* > 1.13.2 */
TEST_CASE("trade")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();
    const std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();

    const Botcraft::Vector3<double> pos = Botcraft::Vector3<double>(1.5, 0, 1.5) + TestManager::GetInstance().GetCurrentOffset();

    std::shared_ptr<Botcraft::Entity> entity;
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            auto entities = entity_manager->GetEntities();
            for (const auto& [k, v] : *entities)
            {
                if (v->GetPosition().SqrDist(pos) < 0.2 &&
                    v->GetType() == Botcraft::VillagerEntity::GetClassType())
                {
                    entity = v;
                    return true;
                }
            }
            return false;
        }, 5000));
    REQUIRE(entity != nullptr);
    REQUIRE(GiveItem(bot, "minecraft:stick", "Stick", 1));

    bot->SyncAction(5000, Botcraft::InteractEntity, entity->GetEntityID(), Botcraft::Hand::Right, true);
    bot->SyncAction(5000, Botcraft::TradeName, "minecraft:stick", false, -1);
    bot->SyncAction(5000, Botcraft::TradeName, "minecraft:enchanted_book", true, -1);
    bot->SyncAction(5000, Botcraft::CloseContainer, -1);

    // Wait for the player inventory to update
    CHECK(Botcraft::Utilities::WaitForCondition([&]()
        {
            return !inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).IsEmptySlot();
        }, 5000));

    bot->SyncAction(5000, Botcraft::SetItemInHand, "minecraft:enchanted_book", Botcraft::Hand::Right);
    REQUIRE(GetItemName(inventory_manager->GetHotbarSelected()) == "minecraft:enchanted_book");
    REQUIRE(inventory_manager->GetHotbarSelected().GetItemCount() == 1);
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

    bot->SyncAction(5000, Botcraft::CraftNamed, decraft_recipe, true);
    REQUIRE(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START)) == "minecraft:diamond");
    REQUIRE(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).GetItemCount() == 9);

    bot->SyncAction(5000, Botcraft::OpenContainer, table);
    short container_id = inventory_manager->GetFirstOpenedWindowId();
    std::shared_ptr<Botcraft::Window> container = inventory_manager->GetWindow(container_id);

    REQUIRE(container_id != -1);

    const std::array<std::string, 3> diamond_line = { "minecraft:diamond", "minecraft:diamond", "minecraft:diamond" };
    const std::array<std::array<std::string, 3>, 3> craft_recipe = {
        diamond_line,
        diamond_line,
        diamond_line
    };

    bot->SyncAction(5000, Botcraft::CraftNamed, craft_recipe, false);
    bot->SyncAction(5000, Botcraft::CloseContainer, -1);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
    // If <1.17 we need to wait for the server to send the
    // updated player inventory content after closing the container
    REQUIRE(Botcraft::Utilities::WaitForCondition([&]()
        {
            if (GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START)) == "minecraft:diamond_block" &&
                inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).GetItemCount() == 1)
            {
                return true;
            }
            return false;
        }, 5000));
#else
    REQUIRE(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START)) == "minecraft:diamond_block");
    REQUIRE(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_STORAGE_START).GetItemCount() == 1);
#endif
}

TEST_CASE("sort inventory")
{
    std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
    const std::shared_ptr<Botcraft::InventoryManager> inventory_manager = bot->GetInventoryManager();

    CHECK(GiveItem(bot, "minecraft:stick", "Stick", 5));

    for (int i = 1; i < 5; ++i)
    {
        bot->SyncAction(5000, Botcraft::PutOneItemInContainerSlot, Botcraft::Window::PLAYER_INVENTORY_INDEX, Botcraft::Window::INVENTORY_HOTBAR_START, Botcraft::Window::INVENTORY_HOTBAR_START + i);
    }

    bot->SyncAction(5000, Botcraft::SortInventory);

    CHECK(GetItemName(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START)) == "minecraft:stick");
    CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START).GetItemCount() == 5);

    for (int i = 1; i < 5; ++i)
    {
        CHECK(inventory_manager->GetPlayerInventory()->GetSlot(Botcraft::Window::INVENTORY_HOTBAR_START + i).IsEmptySlot());
    }
}
