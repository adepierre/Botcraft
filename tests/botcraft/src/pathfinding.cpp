#include <catch2/catch_test_macros.hpp>

#include <botcraft/Game/World/World.hpp>
#include <botcraft/Game/AssetsManager.hpp>
#include <botcraft/AI/Tasks/PathfindingTask.hpp>


using namespace Botcraft;

std::shared_ptr<World> BuildWorld(const std::map<Position, std::string>& blocks)
{
    AssetsManager& assets_manager = AssetsManager::getInstance();
    std::shared_ptr<World> world = std::make_shared<World>(false);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    const Dimension dimension = Dimension::Overworld;
#else
    const std::string dimension = "minecraft:overworld";
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    world->SetDimensionMinY(dimension, 0);
    world->SetDimensionHeight(dimension, 256);
    world->SetCurrentDimension(dimension);
#endif

    for (const auto& [k, v] : blocks)
    {
        if (!world->IsLoaded(k))
        {
            world->LoadChunk(
                static_cast<int>(std::floor(k.x / static_cast<double>(CHUNK_WIDTH))),
                static_cast<int>(std::floor(k.z / static_cast<double>(CHUNK_WIDTH))),
                dimension
            );
        }
        world->SetBlock(k, assets_manager.GetBlockstate("minecraft:" + v)->GetId());
    }

    return world;
}

TEST_CASE("1 block")
{
    std::shared_ptr<World> world = BuildWorld({
        { Position(0, 0, 0), "stone" },
        { Position(1, 0, 0), "stone" },
    });

    std::vector<std::pair<Position, float>> path = FindPath(world, Position(0, 1, 0), Position(1, 0, 0), 0, 0, 0, false, true);

    REQUIRE(path.size() == 1);
    REQUIRE(path[0].first == Position(1, 1, 0));
}
