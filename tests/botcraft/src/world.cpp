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
#endif
    world.SetCurrentDimension(dimension);

    REQUIRE(world.GetChunks()->size() == 0);

    world.LoadChunk(0, 0, dimension);
    REQUIRE(world.GetChunks()->size() == 1);

    world.UnloadChunk(0, 0);
    REQUIRE(world.GetChunks()->size() == 0);

    world.LoadChunk(0, 0, dimension);
    world.LoadChunk(0, 1, dimension);
    REQUIRE(world.GetChunks()->size() == 2);

    world.UnloadAllChunks();
    REQUIRE(world.GetChunks()->size() == 0);
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
#endif
    world.SetCurrentDimension(dimension);
#if PROTOCOL_VERSION < 347 /* < 1.13 */
    const BlockstateId id = { 1,0 };
#else
    const BlockstateId id = 1;
#endif

    // Does nothing: chunk not loaded
    world.SetBlock(Position(0, 0, 0), id);
    REQUIRE(world.GetBlock(Position(0, 0, 0)) == nullptr);

    world.LoadChunk(0, 0, dimension);
    world.SetBlock(Position(0, 0, 0), id);
    REQUIRE(world.GetBlock(Position(0, 0, 0)) != nullptr);
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
#endif
    world.SetCurrentDimension(dimension);

    // Does nothing: chunk not loaded
#if PROTOCOL_VERSION < 552 /* < 1.15 */
    world.SetBiome(0, 0, 0);
#else
    world.SetBiome(0, 0, 0, 0);
#endif
    REQUIRE(world.GetBiome(Position(0, 0, 0)) == nullptr);

    world.LoadChunk(0, 0, dimension);
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
#endif
    world.SetCurrentDimension(dimension);

    world.LoadChunk(0, 0, dimension);
    world.LoadChunk(0, 1, dimension);
#if PROTOCOL_VERSION < 347 /* < 1.13 */
    const BlockstateId id = { 1,0 };
#else
    const BlockstateId id = 1;
#endif
    world.SetBlock(Position(0, 0, CHUNK_WIDTH - 1), id);
    {
        auto world_terrain = world.GetChunks();
        REQUIRE(world_terrain->at({ 0,0 }).GetBlock(Position(0, 0, CHUNK_WIDTH - 1)) != nullptr);
        REQUIRE(world_terrain->at({ 0,0 }).GetBlock(Position(0, 0, CHUNK_WIDTH - 1))->GetId() == id);
        REQUIRE(world_terrain->at({ 0,1 }).GetBlock(Position(0, 0, -1)) != nullptr);
        REQUIRE(world_terrain->at({ 0,1 }).GetBlock(Position(0, 0, -1))->GetId() == id);
    }
}
#endif

TEST_CASE("Shared world")
{
    std::thread thread1 = std::thread([]() {});
    std::thread thread2 = std::thread([]() {});
    const std::thread::id thread_id1 = thread1.get_id();
    const std::thread::id thread_id2 = thread2.get_id();
    thread1.join();
    thread2.join();

    World world = World(true);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world.SetDimensionMinY(dimension, 0);
    world.SetDimensionHeight(dimension, 256);
#endif
    world.SetCurrentDimension(dimension);
    REQUIRE(world.GetChunks()->size() == 0);

    SECTION("Load same chunk")
    {
        world.LoadChunk(0, 0, dimension, thread_id1);
        world.LoadChunk(0, 0, dimension, thread_id2);
        REQUIRE(world.GetChunks()->size() == 1);

        world.UnloadChunk(0, 0, thread_id1);
        REQUIRE(world.GetChunks()->size() == 1);
        world.UnloadChunk(0, 0, thread_id1);
        REQUIRE(world.GetChunks()->size() == 1);
        world.UnloadChunk(0, 0, thread_id2);
        REQUIRE(world.GetChunks()->size() == 0);
    }

    SECTION("Load different chunks")
    {
        world.LoadChunk(0, 0, dimension, thread_id1);
        world.LoadChunk(0, 1, dimension, thread_id2);
        REQUIRE(world.GetChunks()->size() == 2);

        world.UnloadAllChunks(thread_id1);
        REQUIRE(world.GetChunks()->size() == 1);
        world.UnloadAllChunks(thread_id1);
        REQUIRE(world.GetChunks()->size() == 1);
        world.UnloadAllChunks(thread_id2);
        REQUIRE(world.GetChunks()->size() == 0);
    }
}


TEST_CASE("Set/Get lights")
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
#endif
    world.SetCurrentDimension(dimension);

    // Does nothing: chunk not loaded
    world.SetBlockLight(Position(0, 0, 0), 12);
    CHECK(world.GetBlockLight(Position(0, 0, 0)) == 0);
    world.SetSkyLight(Position(0, 0, 0), 6);
    CHECK(world.GetSkyLight(Position(0, 0, 0)) == 0);

    world.LoadChunk(0, 0, dimension);
    world.SetBlockLight(Position(0, 0, 0), 12);
    CHECK(world.GetBlockLight(Position(0, 0, 0)) == 12);
    world.SetBlockLight(Position(1, 0, 0), 6);
    CHECK(world.GetBlockLight(Position(0, 0, 0)) == 12);
    CHECK(world.GetBlockLight(Position(1, 0, 0)) == 6);

    world.SetSkyLight(Position(0, 0, 0), 12);
    CHECK(world.GetSkyLight(Position(0, 0, 0)) == 12);
    world.SetSkyLight(Position(1, 0, 0), 6);
    CHECK(world.GetSkyLight(Position(0, 0, 0)) == 12);
    CHECK(world.GetSkyLight(Position(1, 0, 0)) == 6);
}
