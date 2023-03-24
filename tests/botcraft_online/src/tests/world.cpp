#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>

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
