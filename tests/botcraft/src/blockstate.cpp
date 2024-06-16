#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <botcraft/Game/World/Blockstate.hpp>

using namespace Botcraft;

TEST_CASE("Testing mining time calculation")
{
    BlockstateProperties blockstate_properties;

    SECTION("air")
    {
        blockstate_properties.hardness = -1.0f;
        blockstate_properties.any_tool_harvest = false;
        blockstate_properties.best_tools = {

        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(-1.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(-1.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(-1.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(-1.0, 0.04));
    }

    SECTION("water")
    {
        blockstate_properties.hardness = 100.0f;
        blockstate_properties.any_tool_harvest = false;
        blockstate_properties.water = true;
        blockstate_properties.best_tools = {

        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(-1.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(-1.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(-1.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(-1.0, 0.04));
    }

    SECTION("obsidian")
    {
        blockstate_properties.hardness = 50.0f;
        blockstate_properties.any_tool_harvest = false;
        blockstate_properties.best_tools = {
            BestTool {
                ToolType::Pickaxe, //tool_type
                ToolMaterial::Diamond, //tool_material
                1.0f //multiplier
            }
        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(250.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(250.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(250.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shovel, ToolMaterial::Gold), Catch::Matchers::WithinAbs(250.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(250.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(125.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Gold), Catch::Matchers::WithinAbs(20.85, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(9.4, 0.04));

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Diamond, 1.0f + 5.0f * 5.0f /*Efficiency 5*/), Catch::Matchers::WithinAbs(2.25, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Diamond, 0.0f, 2), Catch::Matchers::WithinAbs(6.7, 0.04));

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Diamond, 0.0f, 0, 0, false), Catch::Matchers::WithinAbs(46.9, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Diamond, 0.0f, 0, 0, true, 0.2f /*under water*/), Catch::Matchers::WithinAbs(46.9, 0.04));
    }

    SECTION("ender_chest")
    {
        BlockstateProperties blockstate_properties;
        blockstate_properties.hardness = 22.5f;
        blockstate_properties.any_tool_harvest = false;
        blockstate_properties.best_tools = {
            BestTool {
                ToolType::Pickaxe, //tool_type
                ToolMaterial::Wood, //tool_material
                1.0f //multiplier
            }
        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(112.5, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(112.5, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(112.5, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shovel, ToolMaterial::Stone), Catch::Matchers::WithinAbs(112.5, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Iron), Catch::Matchers::WithinAbs(112.5, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(16.9, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Gold), Catch::Matchers::WithinAbs(2.85, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(4.25, 0.04));
    }

    SECTION("chest")
    {
        BlockstateProperties blockstate_properties;
        blockstate_properties.hardness = 2.5f;
        blockstate_properties.any_tool_harvest = true;
        blockstate_properties.best_tools = {
            BestTool {
                ToolType::Axe, //tool_type
                ToolMaterial::Wood, //tool_material
                1.0f //multiplier
            }
        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(3.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(1.9, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Gold), Catch::Matchers::WithinAbs(0.35, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(3.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Gold), Catch::Matchers::WithinAbs(3.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shovel, ToolMaterial::Stone), Catch::Matchers::WithinAbs(3.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(3.75, 0.04));
    }

    SECTION("dirt")
    {
        BlockstateProperties blockstate_properties;
        blockstate_properties.hardness = 0.5f;
        blockstate_properties.any_tool_harvest = true;
        blockstate_properties.best_tools = {
            BestTool {
                ToolType::Shovel, //tool_type
                ToolMaterial::Wood, //tool_material
                1.0f //multiplier
            }
        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(0.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Axe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(0.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(0.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Gold), Catch::Matchers::WithinAbs(0.75, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Pickaxe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(0.75, 0.04));

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shovel, ToolMaterial::Wood), Catch::Matchers::WithinAbs(0.4, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shovel, ToolMaterial::Gold), Catch::Matchers::WithinAbs(0.1, 0.04));
#if PROTOCOL_VERSION > 578 /* > 1.15.2 */
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shovel, ToolMaterial::Netherite), Catch::Matchers::WithinAbs(0.1, 0.04));
#endif
    }

    SECTION("leaves")
    {
        BlockstateProperties blockstate_properties;
        blockstate_properties.hardness = 0.2f;
        blockstate_properties.any_tool_harvest = true;
        blockstate_properties.best_tools = {
            BestTool {
                ToolType::Shears, //tool_type
                ToolMaterial::None, //tool_material
                15.0f //multiplier
            },
            BestTool {
                ToolType::Sword, //tool_type
                ToolMaterial::None, //tool_material
                1.5f //multiplier
            },
            BestTool {
                ToolType::Hoe, //tool_type
                ToolMaterial::Wood, //tool_material
                1.0f //multiplier
            },
        };
        Blockstate blockstate(blockstate_properties);

        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::None, ToolMaterial::None), Catch::Matchers::WithinAbs(0.3, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Shears, ToolMaterial::None), Catch::Matchers::WithinAbs(0.0, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Gold), Catch::Matchers::WithinAbs(0.2, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Sword, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(0.2, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Hoe, ToolMaterial::Wood), Catch::Matchers::WithinAbs(0.15, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Hoe, ToolMaterial::Stone), Catch::Matchers::WithinAbs(0.1, 0.04));
        REQUIRE_THAT(blockstate.GetMiningTimeSeconds(ToolType::Hoe, ToolMaterial::Diamond), Catch::Matchers::WithinAbs(0.0, 0.04));
    }
}
