#include <catch2/catch_test_macros.hpp>

#include <botcraft/Game/AssetsManager.hpp>

TEST_CASE("Items durability")
{
    REQUIRE(Botcraft::AssetsManager::getInstance().GetItem("minecraft:stone")->GetMaxDurability() == -1);
    REQUIRE(Botcraft::AssetsManager::getInstance().GetItem("minecraft:elytra")->GetMaxDurability() == 432);
    REQUIRE(Botcraft::AssetsManager::getInstance().GetItem("minecraft:chainmail_chestplate")->GetMaxDurability() == 240);
    REQUIRE(Botcraft::AssetsManager::getInstance().GetItem("minecraft:diamond_sword")->GetMaxDurability() == 1561);
}
