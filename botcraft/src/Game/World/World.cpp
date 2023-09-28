#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/World.hpp"

#include "botcraft/Utilities/AsyncHandler.hpp"
#include "botcraft/Utilities/Logger.hpp"

#include <memory>

namespace Botcraft
{
    World::World(const bool is_shared_, const bool async_handler_) : is_shared(is_shared_)
    {
#if PROTOCOL_VERSION < 719 /* < 1.16 */
        current_dimension = Dimension::None;
#else
        current_dimension = "";
#endif

        if (async_handler_)
        {
            async_handler = std::make_unique<AsyncHandler>(this);
        }
        else
        {
            async_handler = nullptr;
        }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        world_interaction_sequence_id = 0;
#endif
    }

    World::~World()
    {

    }

    ProtocolCraft::Handler* World::GetHandler()
    {
        if (async_handler != nullptr)
        {
            return async_handler.get();
        }
        else
        {
            return this;
        }
    }

    bool World::IsLoaded(const Position& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);

        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        return terrain.find({ chunk_x, chunk_z }) != terrain.end();
    }

    bool World::IsShared() const
    {
        return is_shared;
    }

    int World::GetHeight() const
    {
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        return 256;
#else
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        return GetHeightImpl();
#endif
    }

    int World::GetMinY() const
    {
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        return 0;
#else
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        return GetMinYImpl();
#endif
    }

    bool World::HasChunkBeenModified(const int x, const int z)
    {
#if USE_GUI
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        Chunk* chunk = GetChunk(x, z);
        if (chunk == nullptr)
        {
            return true;
        }
        return chunk->GetModifiedSinceLastRender();
#else
        return false;
#endif
    }

    std::optional<Chunk> World::ResetChunkModificationState(const int x, const int z)
    {
#if USE_GUI
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        Chunk* chunk = GetChunk(x, z);
        if (chunk == nullptr)
        {
            return std::optional<Chunk>();
        }
        chunk->SetModifiedSinceLastRender(false);
        return std::optional<Chunk>(*chunk);
#else
        return std::optional<Chunk>();
#endif
    }

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    void World::LoadChunk(const int x, const int z, const Dimension dim)
#else
    void World::LoadChunk(const int x, const int z, const std::string& dim)
#endif
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        LoadChunkImpl(x, z, dim);
    }

    void World::UnloadChunk(const int x, const int z)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        UnloadChunkImpl(x, z);
    }

    void World::UnloadAllChunks()
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        for (auto it = terrain.begin(); it != terrain.end();)
        {
            const int load_count = it->second.DecrementLoadCounter();
            if (load_count == 0)
            {
                terrain.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }

    void World::SetBlock(const Position& pos, const BlockstateId id)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        SetBlockImpl(pos, id);
    }

    const Blockstate* World::GetBlock(const Position& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        return GetBlockImpl(pos);
    }

    std::vector<const Blockstate*> World::GetBlocks(const std::vector<Position>& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        std::vector<const Blockstate*> output(pos.size());
        for (size_t i = 0; i < pos.size(); ++i)
        {
            output[i] = GetBlockImpl(pos[i]);
        }

        return output;
    }

    Utilities::ScopeLockedWrapper<const std::unordered_map<std::pair<int, int>, Chunk>, std::shared_mutex, std::shared_lock> World::GetTerrain() const
    {
        return Utilities::ScopeLockedWrapper<const std::unordered_map<std::pair<int, int>, Chunk>, std::shared_mutex, std::shared_lock>(terrain, world_mutex);
    }

#if PROTOCOL_VERSION < 358 /* < 1.13 */
    void World::SetBiome(const int x, const int z, const unsigned char biome)
#elif PROTOCOL_VERSION < 552 /* < 1.15 */
    void World::SetBiome(const int x, const int z, const int biome)
#else
    void World::SetBiome(const int x, const int y, const int z, const int biome)
#endif
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION < 552 /* < 1.15 */
        SetBiomeImpl(x, z, biome);
#else
        SetBiomeImpl(x, y, z, biome);
#endif
    }

    const Biome* World::GetBiome(const Position& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });
        if (it == terrain.end())
        {
            return nullptr;
        }

        const int in_chunk_x = (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
        const int in_chunk_z = (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;

#if PROTOCOL_VERSION < 552 /* < 1.15 */
        return it->second.GetBiome(in_chunk_x, in_chunk_z);
#else
        return it->second.GetBiome(in_chunk_x, pos.y, in_chunk_z);
#endif
    }

    void World::SetSkyLight(const Position& pos, const unsigned char skylight)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        auto it = terrain.find({
            static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)))
            });

        if (it != terrain.end() &&
#if PROTOCOL_VERSION < 719 /* < 1.16 */
            it->second.GetDimension() == Dimension::Overworld)
#else
            it->second.GetDimension() == "minecraft:overworld")
#endif
        {
            const int in_chunk_x = (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
            const int in_chunk_z = (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
            it->second.SetSkyLight(Position(in_chunk_x, pos.y, in_chunk_z), skylight);
        }
    }

    void World::SetBlockLight(const Position& pos, const unsigned char blocklight)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        auto it = terrain.find({
            static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)))
        });

        if (it != terrain.end())
        {
            const int in_chunk_x = (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
            const int in_chunk_z = (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
            it->second.SetBlockLight(Position(in_chunk_x, pos.y, in_chunk_z), blocklight);
        }
    }

    unsigned char World::GetSkyLight(const Position& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });
        if (it == terrain.end())
        {
            return 0;
        }

        const int in_chunk_x = (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
        const int in_chunk_z = (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
        return it->second.GetSkyLight(Position(in_chunk_x, pos.y, in_chunk_z));
    }

    unsigned char World::GetBlockLight(const Position& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });
        if (it == terrain.end())
        {
            return 0;
        }

        const int in_chunk_x = (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
        const int in_chunk_z = (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
        return it->second.GetBlockLight(Position(in_chunk_x, pos.y, in_chunk_z));
    }

    void World::SetBlockEntityData(const Position& pos, const ProtocolCraft::NBT::Value& data)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);

        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });
        if (it != terrain.end())
        {
            return;
        }

        const Position chunk_pos(
            (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH,
            pos.y,
            (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH
        );

        if (data.HasData())
        {
            it->second.SetBlockEntityData(chunk_pos, data);
        }
        else
        {
            it->second.RemoveBlockEntityData(chunk_pos);
        }
    }

    ProtocolCraft::NBT::Value World::GetBlockEntityData(const Position& pos) const
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);

        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });

        if (it == terrain.end())
        {
            return ProtocolCraft::NBT::Value();
        }

        const Position chunk_pos(
            (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH,
            pos.y,
            (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH
        );

        return it->second.GetBlockEntityData(chunk_pos);
    }

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    Dimension World::GetDimension(const int x, const int z) const
#else
    std::string World::GetDimension(const int x, const int z) const
#endif
    {
        std::shared_lock<std::shared_mutex> lock(world_mutex);
        auto it = terrain.find({ x, z });
        if (it == terrain.end())
        {
#if PROTOCOL_VERSION < 719 /* < 1.16 */
            return Dimension::None;
#else
            return "";
#endif
        }

        return it->second.GetDimension();
    }

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    void World::SetCurrentDimension(const Dimension dimension)
#else
    void World::SetCurrentDimension(const std::string& dimension)
#endif
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        SetCurrentDimensionImpl(dimension);
    }

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
    void World::SetDimensionHeight(const std::string& dimension, const int height)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        dimension_height[dimension] = height;
    }

    void World::SetDimensionMinY(const std::string& dimension, const int min_y)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        dimension_min_y[dimension] = min_y;
    }
#endif

    const Blockstate* World::Raycast(const Vector3<double>& origin, const Vector3<double>& direction, const float max_radius, Position& out_pos, Position& out_normal)
    {
        // Inspired from https://gist.github.com/dogfuntom/cc881c8fc86ad43d55d8
        // Searching along origin + t * direction line

        // Position of the current cube examined
        out_pos = Position(
            static_cast<int>(std::floor(origin.x)),
            static_cast<int>(std::floor(origin.y)),
            static_cast<int>(std::floor(origin.z))
        );

        // Increment on each axis
        Vector3<double> step((0.0 < direction.x) - (direction.x < 0.0), (0.0 < direction.y) - (direction.y < 0.0), (0.0 < direction.z) - (direction.z < 0.0));

        // tMax is the t-value to cross a cube boundary
        // for each axis. The axis with the least tMax
        // value is the one the ray crosses in first
        // tDelta is the increment of t for each step
        Vector3<double> tMax, tDelta;

        for (int i = 0; i < 3; ++i)
        {
            bool isInteger = std::round(origin[i]) == origin[i];
            if (direction[i] < 0 && isInteger)
            {
                tMax[i] = 0.0;
            }
            else
            {
                if (direction[i] > 0)
                {
                    tMax[i] = ((origin[i] == 0.0f) ? 1.0f : std::ceil(origin[i]) - origin[i]) / std::abs(direction[i]);
                }
                else if (direction[i] < 0)
                {
                    tMax[i] = (origin[i] - std::floor(origin[i])) / std::abs(direction[i]);
                }
                else
                {
                    tMax[i] = std::numeric_limits<double>::max();
                }
            }

            if (direction[i] == 0)
            {
                tDelta[i] = std::numeric_limits<double>::max();
            }
            else
            {
                tDelta[i] = step[i] / direction[i];
            }
        }

        if (direction.x == 0 && direction.y == 0 && direction.z == 0)
        {
            throw std::runtime_error("Raycasting with null direction");
        }

        const float radius = max_radius / static_cast<float>(std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z));

        while (true)
        {
            const Blockstate* block = GetBlock(out_pos);

            if (block != nullptr && !block->IsAir())
            {
                const auto& cubes = block->GetModel(block->GetModelId(out_pos)).GetColliders();
                for (int i = 0; i < cubes.size(); ++i)
                {
                    const AABB current_cube = cubes[i] + out_pos;
                    if (current_cube.Intersect(origin, direction))
                    {
                        return block;
                    }
                }
            }

            // select the direction in which the next face is
            // the closest
            if (tMax.x < tMax.y && tMax.x < tMax.z)
            {
                if (tMax.x > radius)
                {
                    return nullptr;
                }

                out_pos.x += static_cast<int>(std::round(step.x));
                tMax.x += tDelta.x;
                out_normal.x = -static_cast<int>(std::round(step.x));
                out_normal.y = 0;
                out_normal.z = 0;
            }
            else if (tMax.y < tMax.x && tMax.y < tMax.z)
            {
                if (tMax.y > radius)
                {
                    return nullptr;
                }
                out_pos.y += static_cast<int>(std::round(step.y));
                tMax.y += tDelta.y;
                out_normal[0] = 0;
                out_normal[1] = -static_cast<int>(std::round(step.y));
                out_normal[2] = 0;
            }
            else // tMax.z < tMax.x && tMax.z < tMax.y
            {
                if (tMax.z > radius)
                {
                    return nullptr;
                }

                out_pos.z += static_cast<int>(std::round(step.z));
                tMax.z += tDelta.z;
                out_normal.x = 0;
                out_normal.x = 0;
                out_normal.x = -static_cast<int>(std::round(step.z));
            }
        }
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    int World::GetNextWorldInteractionSequenceId()
    {
        return ++world_interaction_sequence_id;
    }
#endif

    void World::Handle(ProtocolCraft::ClientboundLoginPacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION < 719 /* < 1.16 */
        SetCurrentDimensionImpl(static_cast<Dimension>(msg.GetDimension()));
#else
        SetCurrentDimensionImpl(msg.GetDimension().GetFull());
#endif
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#if PROTOCOL_VERSION < 759 /* < 1.19 */
        dimension_height[current_dimension] = msg.GetDimensionType()["height"].get<int>();
        dimension_min_y[current_dimension] = msg.GetDimensionType()["min_y"].get<int>();
#else
        for (const auto& d : msg.GetRegistryHolder()["minecraft:dimension_type"]["value"].as_list_of<ProtocolCraft::NBT::TagCompound>())
        {
            const std::string& dim_name = d["name"].get<std::string>();
            dimension_height[dim_name] = static_cast<unsigned int>(d["element"]["height"].get<int>());
            dimension_min_y[dim_name] = d["element"]["min_y"].get<int>();
        }
#endif
#endif
    }

    void World::Handle(ProtocolCraft::ClientboundRespawnPacket& msg)
    {
        UnloadAllChunks();

        std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION < 719 /* < 1.16 */
        SetCurrentDimensionImpl(static_cast<Dimension>(msg.GetDimension()));
#else
        SetCurrentDimensionImpl(msg.GetDimension().GetFull());
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
        dimension_height[current_dimension] = msg.GetDimensionType()["height"].get<int>();
        dimension_min_y[current_dimension] = msg.GetDimensionType()["min_y"].get<int>();
#endif
    }

    void World::Handle(ProtocolCraft::ClientboundBlockUpdatePacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION < 347 /* < 1.13 */
        unsigned int id;
        unsigned char metadata;
        Blockstate::IdToIdMetadata(msg.GetBlockstate(), id, metadata);
        SetBlockImpl(msg.GetPos(), { id, metadata });
#else
        SetBlockImpl(msg.GetPos(), msg.GetBlockstate());
#endif
    }

    void World::Handle(ProtocolCraft::ClientboundSectionBlocksUpdatePacket& msg)
    {
#if PROTOCOL_VERSION < 739 /* < 1.16.2 */
        for (int i = 0; i < msg.GetRecordCount(); ++i)
        {
            unsigned char x = (msg.GetRecords()[i].GetHorizontalPosition() >> 4) & 0x0F;
            unsigned char z = msg.GetRecords()[i].GetHorizontalPosition() & 0x0F;

            const int x_pos = CHUNK_WIDTH * msg.GetChunkX() + x;
            const int y_pos = msg.GetRecords()[i].GetYCoordinate();
            const int z_pos = CHUNK_WIDTH * msg.GetChunkZ() + z;
#else
        const int chunk_x = CHUNK_WIDTH * (msg.GetSectionPos() >> 42); // 22 bits
        const int chunk_z = CHUNK_WIDTH * (msg.GetSectionPos() << 22 >> 42); // 22 bits
        const int chunk_y = SECTION_HEIGHT * (msg.GetSectionPos() << 44 >> 44); // 20 bits

        const size_t data_size = msg.GetPositions().size();
        for (int i = 0; i < data_size; ++i)
        {
            const unsigned int block_id = msg.GetStates()[i];

            const int x_pos = chunk_x + ((msg.GetPositions()[i] >> 8) & 0xF);
            const int z_pos = chunk_z + ((msg.GetPositions()[i] >> 4) & 0xF);
            const int y_pos = chunk_y + ((msg.GetPositions()[i] >> 0) & 0xF);
#endif
            Position cube_pos(x_pos, y_pos, z_pos);

            {
                std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION < 347 /* < 1.13 */
                unsigned int id;
                unsigned char metadata;
                Blockstate::IdToIdMetadata(msg.GetRecords()[i].GetBlockId(), id, metadata);

                SetBlockImpl(cube_pos, { id, metadata });
#elif PROTOCOL_VERSION < 739 /* < 1.16.2 */
                SetBlockImpl(cube_pos, msg.GetRecords()[i].GetBlockId());
#else
                SetBlockImpl(cube_pos, block_id);
#endif
            }
        }
    }

    void World::Handle(ProtocolCraft::ClientboundForgetLevelChunkPacket& msg)
    {
        UnloadChunk(msg.GetX(), msg.GetZ());
    }

#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
    void World::Handle(ProtocolCraft::ClientboundLevelChunkPacket& msg)
    {

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        if (msg.GetFullChunk())
        {
#endif
            LoadChunk(msg.GetX(), msg.GetZ(), current_dimension);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        }
#endif

        { // lock scope
            std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
            if (auto it = delayed_light_updates.find({ msg.GetX(), msg.GetZ() }); it != delayed_light_updates.end())
            {
                UpdateChunkLight(it->second.GetX(), it->second.GetZ(), current_dimension,
                    it->second.GetSkyYMask(), it->second.GetEmptySkyYMask(), it->second.GetSkyUpdates(), true);
                UpdateChunkLight(it->second.GetX(), it->second.GetZ(), current_dimension,
                    it->second.GetBlockYMask(), it->second.GetEmptyBlockYMask(), it->second.GetBlockUpdates(), false);
                delayed_light_updates.erase(it);
            }
#endif
#if PROTOCOL_VERSION < 552 /* < 1.15 */
            LoadDataInChunk(msg.GetX(), msg.GetZ(), msg.GetBuffer(), msg.GetAvailableSections(), msg.GetFullChunk());
#else
            LoadDataInChunk(msg.GetX(), msg.GetZ(), msg.GetBuffer(), msg.GetAvailableSections());
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            if (msg.GetFullChunk())
            {
                LoadBiomesInChunk(msg.GetX(), msg.GetZ(), msg.GetBiomes());
            }
#else
            LoadBiomesInChunk(msg.GetX(), msg.GetZ(), msg.GetBiomes());
#endif
#endif
            LoadBlockEntityDataInChunk(msg.GetX(), msg.GetZ(), msg.GetBlockEntitiesTags());
        }
    }
#else
    void World::Handle(ProtocolCraft::ClientboundLevelChunkWithLightPacket& msg)
    {
        LoadChunk(msg.GetX(), msg.GetZ(), current_dimension);

        {
            // lock scope
            std::scoped_lock<std::shared_mutex> lock(world_mutex);
            LoadDataInChunk(msg.GetX(), msg.GetZ(), msg.GetChunkData().GetBuffer());
            LoadBlockEntityDataInChunk(msg.GetX(), msg.GetZ(), msg.GetChunkData().GetBlockEntitiesData());
            UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
                msg.GetLightData().GetSkyYMask(), msg.GetLightData().GetEmptySkyYMask(), msg.GetLightData().GetSkyUpdates(), true);
            UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
                msg.GetLightData().GetBlockYMask(), msg.GetLightData().GetEmptyBlockYMask(), msg.GetLightData().GetBlockUpdates(), false);
        }
    }
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
    void World::Handle(ProtocolCraft::ClientboundLightUpdatePacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        if (GetChunk(msg.GetX(), msg.GetZ()) == nullptr)
        {
            delayed_light_updates[{msg.GetX(), msg.GetZ()}] = msg;
            return;
        }
        UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
            msg.GetSkyYMask(), msg.GetEmptySkyYMask(), msg.GetSkyUpdates(), true);
        UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
            msg.GetBlockYMask(), msg.GetEmptyBlockYMask(), msg.GetBlockUpdates(), false);
#else
        UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
            msg.GetLightData().GetSkyYMask(), msg.GetLightData().GetEmptySkyYMask(), msg.GetLightData().GetSkyUpdates(), true);
        UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
            msg.GetLightData().GetBlockYMask(), msg.GetLightData().GetEmptyBlockYMask(), msg.GetLightData().GetBlockUpdates(), false);
#endif
    }
#endif

    void World::Handle(ProtocolCraft::ClientboundBlockEntityDataPacket& msg)
    {
        SetBlockEntityData(msg.GetPos(), msg.GetTag());
    }

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    void World::Handle(ProtocolCraft::ClientboundChunksBiomesPacket& msg)
    {
        std::scoped_lock<std::shared_mutex> lock(world_mutex);
        for (const auto& chunk_data : msg.GetChunkBiomeData())
        {
            auto it = terrain.find({ chunk_data.GetX(), chunk_data.GetZ() });
            if (it != terrain.end())
            {
                it->second.LoadBiomesData(chunk_data.GetBuffer());
            }
            else
            {
                LOG_WARNING("Trying to load biomes data in non loaded chunk (" << chunk_data.GetX() << ", " << chunk_data.GetZ() << ")");
            }
        }
    }
#endif

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    void World::LoadChunkImpl(const int x, const int z, const Dimension dim)
#else
    void World::LoadChunkImpl(const int x, const int z, const std::string& dim)
#endif
    {
        auto it = terrain.find({ x,z });
        if (it == terrain.end())
        {
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
            auto inserted = terrain.insert({ {x, z}, Chunk(dim) });
#else
            auto inserted = terrain.insert({ { x, z }, Chunk(dimension_min_y.at(dim), dimension_height.at(dim), dim) });
#endif
            inserted.first->second.IncrementLoadCounter();
        }
        // This may already exists in this dimension if this is a shared world
        else if (it->second.GetDimension() != dim)
        {
            if (is_shared)
            {
                LOG_WARNING("Changing dimension with a shared world is not supported and can lead to wrong world data");
            }
            UnloadChunkImpl(x, z);
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
            it->second = Chunk(dim);
#else
            it->second = Chunk(dimension_min_y.at(dim), dimension_height.at(dim), dim);
#endif
            it->second.IncrementLoadCounter();
        }
        else
        {
            it->second.IncrementLoadCounter();
        }

        //Not necessary, from void to air, there is no difference
        //UpdateChunk(x, z);
    }

    void World::UnloadChunkImpl(const int x, const int z)
    {
        auto it = terrain.find({ x, z });
        if (it != terrain.end())
        {
            const int load_counter = it->second.DecrementLoadCounter();
            if (load_counter == 0)
            {
                terrain.erase(it);
#if USE_GUI
                UpdateChunk(x, z);
#endif
            }
        }
    }

    void World::SetBlockImpl(const Position& pos, const BlockstateId id)
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });

        // Can't set block in unloaded chunk
        if (it == terrain.end())
        {
            return;
        }

        const Position set_pos(
            (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH,
            pos.y,
            (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH
        );

        it->second.SetBlock(set_pos, id);

#if USE_GUI
        // If this block is on the edge, update neighbours chunks
        UpdateChunk(chunk_x, chunk_z, pos);
#endif
    }

    const Blockstate* World::GetBlockImpl(const Position& pos) const
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        auto it = terrain.find({ chunk_x, chunk_z });

        // Can't get block in unloaded chunk
        if (it == terrain.end())
        {
            return nullptr;
        }

        const Position chunk_pos(
            (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH,
            pos.y,
            (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH
        );

        return it->second.GetBlock(chunk_pos);
    }

#if PROTOCOL_VERSION < 719 /* < 1.16 */
    void World::SetCurrentDimensionImpl(const Dimension dimension)
#else
    void World::SetCurrentDimensionImpl(const std::string& dimension)
#endif
    {
        current_dimension = dimension;
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        delayed_light_updates.clear();
#endif
    }

    int World::GetHeightImpl() const
    {
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        return 256;
#else
        return dimension_height.at(current_dimension);
#endif
    }

    int World::GetMinYImpl() const
    {
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        return 0;
#else
        return dimension_min_y.at(current_dimension);
#endif
    }

#if PROTOCOL_VERSION < 358 /* < 1.13 */
    void World::SetBiomeImpl(const int x, const int z, const unsigned char biome)
#elif PROTOCOL_VERSION < 552 /* < 1.15 */
    void World::SetBiomeImpl(const int x, const int z, const int biome)
#else
    void World::SetBiomeImpl(const int x, const int y, const int z, const int biome)
#endif
    {
        auto it = terrain.find({
            static_cast<int>(std::floor(x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(z / static_cast<double>(CHUNK_WIDTH)))
            });

        if (it != terrain.end())
        {
#if PROTOCOL_VERSION < 552 /* < 1.15 */
            it->second.SetBiome((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, biome);
#else
            it->second.SetBiome((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, y, (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, biome);
#endif
        }
    }

    void World::UpdateChunk(const int x, const int z, const Position& pos)
    {
#if USE_GUI
        const Position this_chunk_position(
            (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH,
            pos.y,
            (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH
        );

        if (this_chunk_position.x > 0 && this_chunk_position.x < CHUNK_WIDTH - 1 &&
            this_chunk_position.z > 0 && this_chunk_position.z < CHUNK_WIDTH - 1)
        {
            return;
        }

        Chunk* chunk = GetChunk(x, z);

        if (chunk == nullptr)
        {
            // This should not happen
            LOG_WARNING("Trying to propagate chunk updates from a non loaded chunk");
            return;
        }

        const Blockstate* blockstate = chunk->GetBlock(this_chunk_position);

        if (this_chunk_position.x == 0)
        {
            Chunk* neighbour_chunk = GetChunk(x - 1, z);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->SetBlock(Position(CHUNK_WIDTH, this_chunk_position.y, this_chunk_position.z), blockstate);
            }
        }

        if (this_chunk_position.x == CHUNK_WIDTH - 1)
        {
            Chunk* neighbour_chunk = GetChunk(x + 1, z);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->SetBlock(Position(-1, this_chunk_position.y, this_chunk_position.z), blockstate);
            }
        }

        if (this_chunk_position.z == 0)
        {
            Chunk* neighbour_chunk = GetChunk(x, z - 1);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->SetBlock(Position(this_chunk_position.x, this_chunk_position.y, CHUNK_WIDTH), blockstate);
            }
        }

        if (this_chunk_position.z == CHUNK_WIDTH - 1)
        {
            Chunk* neighbour_chunk = GetChunk(x, z + 1);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->SetBlock(Position(this_chunk_position.x, this_chunk_position.y, -1), blockstate);
            }
        }
#endif
    }

    void World::UpdateChunk(const int x, const int z)
    {
#if USE_GUI
        Chunk* chunk = GetChunk(x, z);
        // This means this chunk has just beend added
        // Copy data for all edges between its neighbours
        if (chunk != nullptr)
        {
            chunk->UpdateNeighbour(GetChunk(x - 1, z), Orientation::West);
            chunk->UpdateNeighbour(GetChunk(x + 1, z), Orientation::East);
            chunk->UpdateNeighbour(GetChunk(x, z - 1), Orientation::North);
            chunk->UpdateNeighbour(GetChunk(x, z + 1), Orientation::South);
        }
        // This means this chunk has just been removed
        // Update all existing neighbours to let them know
        else
        {
            Chunk* neighbour_chunk;
            neighbour_chunk = GetChunk(x - 1, z);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::East);
            }
            neighbour_chunk = GetChunk(x + 1, z);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::West);
            }
            neighbour_chunk = GetChunk(x, z - 1);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::South);
            }
            neighbour_chunk = GetChunk(x, z + 1);
            if (neighbour_chunk != nullptr)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::North);
            }
        }
#endif
    }

    Chunk* World::GetChunk(const int x, const int z)
    {
        auto it = terrain.find({ x,z });
        if (it == terrain.end())
        {
            return nullptr;
        }
        return &it->second;
    }

#if PROTOCOL_VERSION < 552 /* < 1.15 */
    void World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
        const int primary_bit_mask, const bool ground_up_continuous)
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
    void World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
        const int primary_bit_mask)
#elif PROTOCOL_VERSION < 757 /* < 1.18/.1 */
    void World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
        const std::vector<unsigned long long int>& primary_bit_mask)
#else
    void World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data)
#endif
    {
        Chunk* chunk = GetChunk(x, z);
        if (chunk != nullptr)
        {
#if PROTOCOL_VERSION < 552 /* < 1.15 */
            chunk->LoadChunkData(data, primary_bit_mask, ground_up_continuous);
#elif PROTOCOL_VERSION < 757 /* < 1.18/.1 */
            chunk->LoadChunkData(data, primary_bit_mask);
#else
            chunk->LoadChunkData(data);
#endif
#if USE_GUI
            UpdateChunk(x, z);
#endif
        }
    }

#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
    void World::LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::NBT::Value>& block_entities)
#else
    void World::LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::BlockEntityInfo>& block_entities)
#endif
    {
        Chunk* chunk = GetChunk(x, z);
        if (chunk != nullptr)
        {
            chunk->LoadChunkBlockEntitiesData(block_entities);
        }
    }

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 757 /* < 1.18/.1 */
    void World::LoadBiomesInChunk(const int x, const int z, const std::vector<int>& biomes)
    {
        Chunk* chunk = GetChunk(x, z);
        if (chunk != nullptr)
        {
            chunk->SetBiomes(biomes);
        }
    }
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
#if PROTOCOL_VERSION < 719 /* < 1.16 */
    void World::UpdateChunkLight(const int x, const int z, const Dimension dim, const int light_mask, const int empty_light_mask,
        const std::vector<std::vector<char>>& data, const bool sky)
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
    void World::UpdateChunkLight(const int x, const int z, const std::string& dim, const int light_mask, const int empty_light_mask,
        const std::vector<std::vector<char>>& data, const bool sky)
#else
    void World::UpdateChunkLight(const int x, const int z, const std::string& dim,
        const std::vector<unsigned long long int>& light_mask, const std::vector<unsigned long long int>& empty_light_mask,
        const std::vector<std::vector<char>>& data, const bool sky)
#endif
    {
        Chunk* chunk = GetChunk(x, z);

        if (chunk == nullptr)
        {
            LOG_WARNING("Trying to update lights in an unloaded chunk");
            return;
        }

        int counter_arrays = 0;
        Position pos1, pos2;

        const int num_sections = GetHeightImpl() / 16 + 2;

        for (int i = 0; i < num_sections; ++i)
        {
            const int section_Y = i - 1;

            // Sky light
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            if ((light_mask >> i) & 1)
#else
            if ((light_mask.size() > i / 64) && (light_mask[i / 64] >> (i % 64)) & 1)
#endif
            {
                if (i > 0 && i < num_sections - 1)
                {
                    for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                    {
                        pos1.y = block_y + section_Y * SECTION_HEIGHT + GetMinYImpl();
                        pos2.y = pos1.y;
                        for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                        {
                            pos1.z = block_z;
                            pos2.z = block_z;
                            for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                            {
                                pos1.x = block_x;
                                pos2.x = block_x + 1;
                                const char two_light_values = data[counter_arrays][(block_y * CHUNK_WIDTH * CHUNK_WIDTH + block_z * CHUNK_WIDTH + block_x) / 2];

                                if (sky)
                                {
                                    chunk->SetSkyLight(pos1, two_light_values & 0x0F);
                                    chunk->SetSkyLight(pos2, (two_light_values >> 4) & 0x0F);
                                }
                                else
                                {
                                    chunk->SetBlockLight(pos1, two_light_values & 0x0F);
                                    chunk->SetBlockLight(pos2, (two_light_values >> 4) & 0x0F);
                                }
                            }
                        }
                    }
                }
                counter_arrays++;
            }
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            else if ((empty_light_mask >> i) & 1)
#else
            else if ((empty_light_mask.size() > i / 64) && (empty_light_mask[i / 64] >> (i % 64)) & 1)
#endif
            {
                if (i > 0 && i < num_sections - 1)
                {
                    for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                    {
                        pos1.y = block_y + section_Y * SECTION_HEIGHT + GetMinYImpl();
                        pos2.y = pos1.y;
                        for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                        {
                            pos1.z = block_z;
                            pos2.z = block_z;
                            for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                            {
                                pos1.x = block_x;
                                pos2.x = block_x + 1;
                                if (sky)
                                {
                                    chunk->SetSkyLight(pos1, 0);
                                    chunk->SetSkyLight(pos2, 0);
                                }
                                else
                                {
                                    chunk->SetBlockLight(pos1, 0);
                                    chunk->SetBlockLight(pos2, 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#endif

} // Botcraft
