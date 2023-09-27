#include <catch2/catch_test_macros.hpp>

#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/World/Biome.hpp>

using namespace Botcraft;

TEST_CASE("Add/Remove chunks")
{
    World world = World(false);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world.SetDimensionMinY(dimension, 0);
    world.SetDimensionHeight(dimension, 256);
    world.SetCurrentDimension(dimension);
#endif

    REQUIRE(world.GetTerrain()->size() == 0);

    world.AddChunk(0, 0, dimension);
    REQUIRE(world.GetTerrain()->size() == 1);

    world.UnloadChunk(0, 0);
    REQUIRE(world.GetTerrain()->size() == 0);

    world.AddChunk(0, 0, dimension);
    world.AddChunk(0, 1, dimension);
    REQUIRE(world.GetTerrain()->size() == 2);

    world.UnloadAllChunks();
    REQUIRE(world.GetTerrain()->size() == 0);
}

TEST_CASE("Set/Get blocks")
{
    World world = World(false);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world.SetDimensionMinY(dimension, 0);
    world.SetDimensionHeight(dimension, 256);
    world.SetCurrentDimension(dimension);
#endif

    // Does nothing: chunk not loaded
    world.SetBlock(Position(0, 0, 0), 0);
    REQUIRE(world.GetBlock(Position(0, 0, 0)) == nullptr);

    world.AddChunk(0, 0, dimension);
#if PROTOCOL_VERSION < 347 /* < 1.13 */
    world.SetBlock(Position(0, 0, 0), { 0,0 });
#else
    world.SetBlock(Position(0, 0, 0), 0);
#endif
    REQUIRE(world.GetBlock(Position(0, 0, 0)) != nullptr);
    REQUIRE(world.GetBlock(Position(0, 0, 0))->GetName() == "minecraft:air");
}

TEST_CASE("Set/Get biomes")
{
    World world = World(false);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world.SetDimensionMinY(dimension, 0);
    world.SetDimensionHeight(dimension, 256);
    world.SetCurrentDimension(dimension);
#endif

    // Does nothing: chunk not loaded
#if PROTOCOL_VERSION < 552 /* < 1.15 */
    world.SetBiome(0, 0, 0);
#else
    world.SetBiome(0, 0, 0, 0);
#endif
    REQUIRE(world.GetBiome(Position(0, 0, 0)) == nullptr);

    world.AddChunk(0, 0, dimension);
#if PROTOCOL_VERSION < 552 /* < 1.15 */
    world.SetBiome(0, 0, 0);
#else
    world.SetBiome(0, 0, 0, 0);
#endif
    REQUIRE(world.GetBiome(Position(0, 0, 0)) != nullptr);
    REQUIRE(world.GetBiome(Position(0, 0, 0))->GetName() == AssetsManager::getInstance().GetBiome(0)->GetName());
}

#if USE_GUI
TEST_CASE("Neighbour chunk update")
{
    World world = World(false);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world.SetDimensionMinY(dimension, 0);
    world.SetDimensionHeight(dimension, 256);
    world.SetCurrentDimension(dimension);
#endif

    world.AddChunk(0, 0, dimension);
    world.AddChunk(0, 1, dimension);
#if PROTOCOL_VERSION < 347 /* < 1.13 */
    const BlockstateId id = { 1,0 };
#else
    const BlockstateId id = 1;
#endif
    world.SetBlock(Position(0, 0, CHUNK_WIDTH - 1), id);
    {
        auto world_terrain = world.GetTerrain();
        REQUIRE(world_terrain->at({ 0,0 }).GetBlock(Position(0, 0, CHUNK_WIDTH - 1)) != nullptr);
        REQUIRE(world_terrain->at({ 0,0 }).GetBlock(Position(0, 0, CHUNK_WIDTH - 1))->GetId() == id);
        REQUIRE(world_terrain->at({ 0,1 }).GetBlock(Position(0, 0, -1)) != nullptr);
        REQUIRE(world_terrain->at({ 0,1 }).GetBlock(Position(0, 0, -1))->GetId() == id);
    }
}
#endif
