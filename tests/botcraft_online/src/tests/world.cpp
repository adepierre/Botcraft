#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include <botcraft/Game/AssetsManager.hpp>

#if PROTOCOL_VERSION > 760
#include <sstream>
#endif


TEST_CASE("block names")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();

    std::vector<std::pair<Botcraft::Position, std::string> > pos_names = {
#if PROTOCOL_VERSION < 393
        {Botcraft::Position(0, 0, 1), "minecraft:stained_glass"},
        {Botcraft::Position(1, 0, 0), "minecraft:magma"},
        {Botcraft::Position(1, 0, 1), "minecraft:wool"},
        {Botcraft::Position(1, 0, 2), "minecraft:melon_block"},
#else
        {Botcraft::Position(0, 0, 1), "minecraft:white_stained_glass"},
        {Botcraft::Position(1, 0, 0), "minecraft:magma_block"},
        {Botcraft::Position(1, 0, 1), "minecraft:pink_wool"},
        {Botcraft::Position(1, 0, 2), "minecraft:melon"},
#endif
        {Botcraft::Position(0, 0, 0), "minecraft:cobblestone"},
        {Botcraft::Position(0, 0, 2), "minecraft:bedrock"},
        {Botcraft::Position(0, 0, 3), "minecraft:bookshelf"},
        {Botcraft::Position(1, 0, 3), "minecraft:glass"}
    };
    const Botcraft::Position base_position = TestManager::GetInstance().GetCurrentOffset();
    for (size_t i = 0; i < pos_names.size(); ++i)
    {
        std::lock_guard<std::mutex> lock(bot->GetWorld()->GetMutex());
        const Botcraft::Block* block;
        block = bot->GetWorld()->GetBlock(base_position + pos_names[i].first);
        CHECK(block != nullptr);
        if (block)
        {
            CHECK(block->GetBlockstate()->GetName() == pos_names[i].second);
        }
    }
}

TEST_CASE("block states")
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();

        std::vector<std::tuple<Botcraft::Position, std::string, std::string, std::string> > pos_block_variables_values = {
#if PROTOCOL_VERSION < 393
        {Botcraft::Position(0, 0, 0), "minecraft:stone_slab", "half", "bottom"},
        {Botcraft::Position(0, 0, 1), "minecraft:stone_slab", "half", "top"},
#elif PROTOCOL_VERSION < 477
        {Botcraft::Position(0, 0, 0), "minecraft:stone_slab", "type", "bottom"},
        {Botcraft::Position(0, 0, 1), "minecraft:stone_slab", "type", "top"},
#else
        {Botcraft::Position(0, 0, 0), "minecraft:smooth_stone_slab", "type", "bottom"},
        {Botcraft::Position(0, 0, 1), "minecraft:smooth_stone_slab", "type", "top"},
#endif
#if PROTOCOL_VERSION < 393
        {Botcraft::Position(0, 0, 2), "minecraft:redstone_torch", "facing", "up"},
        {Botcraft::Position(1, 0, 1), "minecraft:unlit_redstone_torch", "facing", "south"}
#else
        {Botcraft::Position(0, 0, 2), "minecraft:redstone_torch", "lit", "true"},
        {Botcraft::Position(1, 0, 1), "minecraft:redstone_wall_torch", "facing", "south"},
        {Botcraft::Position(1, 0, 1), "minecraft:redstone_wall_torch", "lit", "false"}
#endif
    };
    const Botcraft::Position base_position = TestManager::GetInstance().GetCurrentOffset();
    for (size_t i = 0; i < pos_block_variables_values.size(); ++i)
    {
        std::lock_guard<std::mutex> lock(bot->GetWorld()->GetMutex());
        const Botcraft::Block* block;
        block = bot->GetWorld()->GetBlock(base_position + std::get<0>(pos_block_variables_values[i]));
        CHECK(block != nullptr);
        if (block)
        {
            CHECK(block->GetBlockstate()->GetName() == std::get<1>(pos_block_variables_values[i]));
            CHECK(block->GetBlockstate()->GetVariableValue(std::get<2>(pos_block_variables_values[i])) == std::get<3>(pos_block_variables_values[i]));
        }
    }
}

// Botcraft biome data extraction is bugged for 1.19.3+
#if PROTOCOL_VERSION > 760
TEST_CASE("biomes", "[!mayfail]")
#else
TEST_CASE("biomes")
#endif
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();

    SECTION("base biome")
    {
        int biome_id;
        std::lock_guard<std::mutex> lock(bot->GetWorld()->GetMutex());
        REQUIRE_NOTHROW(biome_id = bot->GetWorld()->GetBiome(TestManager::GetInstance().GetCurrentOffset()));
        const Botcraft::Biome* biome = Botcraft::AssetsManager::getInstance().GetBiome(biome_id);
        CHECK(biome->GetName() == "plains");
    }
#if PROTOCOL_VERSION > 760
    SECTION("changed biome")
    {
        const Botcraft::Position start_pos = TestManager::GetInstance().GetCurrentOffset();
        const Botcraft::Position end_pos = start_pos + Botcraft::Position(2, 2, 2);
        std::stringstream command;
        command
            << "fillbiome" << " "
            << start_pos.x << " "
            << start_pos.y << " "
            << start_pos.z << " "
            << end_pos.x << " "
            << end_pos.y << " "
            << end_pos.z << " "
            << "desert";
        MinecraftServer::GetInstance().SendLine(command.str());
        MinecraftServer::GetInstance().WaitLine(".* biome (?:entry/)?entries set between .*", 2000);

        int biome_id;
        const Botcraft::Biome* biome;
        std::lock_guard<std::mutex> lock(bot->GetWorld()->GetMutex());
        REQUIRE_NOTHROW(biome_id = bot->GetWorld()->GetBiome(start_pos));
        biome = Botcraft::AssetsManager::getInstance().GetBiome(biome_id);
        CHECK(biome->GetName() == "desert");
        REQUIRE_NOTHROW(biome_id = bot->GetWorld()->GetBiome(end_pos));
        biome = Botcraft::AssetsManager::getInstance().GetBiome(biome_id);
        CHECK(biome->GetName() == "desert");
    }
#endif
}

#if PROTOCOL_VERSION < 763
TEST_CASE("block entity")
#else
TEST_CASE("block entity 1_20")
#endif
{
    std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();

    std::shared_ptr<ProtocolCraft::NBT::Value> nbt;

    std::lock_guard<std::mutex> lock(bot->GetWorld()->GetMutex());
    REQUIRE_NOTHROW(nbt = bot->GetWorld()->GetBlockEntityData(TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 0, 1)));

    std::vector<std::string> expected_lines = { "Hello", "world", "", "!" };
#if PROTOCOL_VERSION > 762
    std::vector<std::string> expected_lines_back = { "Hello", "back", "", "!" };
#endif

    for (size_t i = 0; i < expected_lines.size(); ++i)
    {
#if PROTOCOL_VERSION < 763
        const std::string& line = (*nbt)["Text" + std::to_string(i+1)].get<std::string>();
        const ProtocolCraft::Json::Value content = ProtocolCraft::Json::Parse(line);
        CHECK(content["text"].get_string() == expected_lines[i]);
#else
        const std::string& front_line = (*nbt)["front_text"]["messages"].as_list_of<std::string>()[i];
        const std::string& back_line = (*nbt)["back_text"]["messages"].as_list_of<std::string>()[i];
        const ProtocolCraft::Json::Value front_content = ProtocolCraft::Json::Parse(front_line);
        const ProtocolCraft::Json::Value back_content = ProtocolCraft::Json::Parse(back_line);
        CHECK(front_content["text"].get_string() == expected_lines[i]);
        CHECK(back_content["text"].get_string() == expected_lines_back[i]);
#endif
    }
}
