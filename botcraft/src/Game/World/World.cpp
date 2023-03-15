#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/Enums.hpp"
#include "botcraft/Utilities/AsyncHandler.hpp"
#include "botcraft/Utilities/Logger.hpp"

namespace Botcraft
{
    World::World(const bool is_shared_, const bool async_handler_)
    {
        is_shared = is_shared_;

#if PROTOCOL_VERSION < 719
        current_dimension = Dimension::None;
#else
        current_dimension = "";
#endif
        if (async_handler_)
        {
            async_handler = std::unique_ptr<AsyncHandler>(new AsyncHandler(this));
        }
        else
        {
            async_handler = nullptr;
        }

#if PROTOCOL_VERSION > 758
        world_interaction_sequence_id = 0;
#endif
    }

    World::~World()
    {

    }

    std::mutex& World::GetMutex()
    {
        return world_mutex;
    }

    const bool World::IsShared() const
    {
        return is_shared;
    }

    ProtocolCraft::Handler* World::GetAsyncHandler()
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

#if PROTOCOL_VERSION < 719
    bool World::AddChunk(const int x, const int z, const Dimension dim)
#else
    bool World::AddChunk(const int x, const int z, const std::string& dim)
#endif
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);

        if (!chunk)
        {
#if PROTOCOL_VERSION < 757
            terrain[{x, z}] = std::make_shared<Chunk>(dim);
#else
            terrain[{x, z}] = std::make_shared<Chunk>(dimension_min_y[dim], dimension_height[dim], dim);
#endif
        }
        else if (chunk->GetDimension() != dim)
        {
            RemoveChunk(x, z);
#if PROTOCOL_VERSION < 757
            terrain[{x, z}] = std::make_shared<Chunk>(dim);
#else
            terrain[{x, z}] = std::make_shared<Chunk>(dimension_min_y[dim], dimension_height[dim], dim);
#endif
        }
        
        //Not necessary, from void to air, there is no difference
        //UpdateChunk(x, z);

        return true;
    }

    bool World::RemoveChunk(const int x, const int z)
    {
        std::map<std::pair<int, int>, std::shared_ptr<Chunk> >::iterator it = terrain.find({ x, z });
        if (it != terrain.end())
        {
            terrain.erase(it);

            if (cached && cached_x == x && cached_z == z)
            {
                cached = nullptr;
            }

            UpdateChunk(x, z);
            return true;
        }

        return false;
    }

#if USE_GUI
    const bool World::HasChunkBeenModified(const int x, const int z)
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (chunk == nullptr)
        {
            return true;
        }

        return chunk->GetModifiedSinceLastRender();
    }

    void World::ResetChunkModificationState(const int x, const int z)
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (chunk == nullptr)
        {
            return;
        }

        chunk->SetModifiedSinceLastRender(false);
    }

#endif

#if PROTOCOL_VERSION < 552
    bool World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data, const int primary_bit_mask, const bool ground_up_continuous)
#elif PROTOCOL_VERSION < 755
    bool World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data, const int primary_bit_mask)
#elif PROTOCOL_VERSION < 757
    bool World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data, const std::vector<unsigned long long int>& primary_bit_mask)
#else
    bool World::LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data)
#endif
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (chunk)
        {
#if PROTOCOL_VERSION < 552
            chunk->LoadChunkData(data, primary_bit_mask, ground_up_continuous);
#elif PROTOCOL_VERSION < 757
            chunk->LoadChunkData(data, primary_bit_mask);
#else
            chunk->LoadChunkData(data);
#endif
            UpdateChunk(x, z);
            return true;
        }
        return false;
    }

#if PROTOCOL_VERSION < 757
    bool World::LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::NBT::Value>& block_entities)
#else
    bool World::LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::BlockEntityInfo>& block_entities)
#endif
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (chunk)
        {
            chunk->LoadChunkBlockEntitiesData(block_entities);
            UpdateChunk(x, z);
            return true;
        }
        return false;
    }

#if PROTOCOL_VERSION > 551 && PROTOCOL_VERSION < 757
    bool World::LoadBiomesInChunk(const int x, const int z, const std::vector<int>& biomes)
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (chunk)
        {
            chunk->SetBiomes(biomes);
            UpdateChunk(x, z);
            return true;
        }
        return false;
    }
#endif

#if PROTOCOL_VERSION < 347
    bool World::SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id)
#else
    bool World::SetBlock(const Position &pos, const unsigned int id, const int model_id)
#endif
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (!cached || cached_x != chunk_x || cached_z != chunk_z)
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;
            }
            else
            {
                return false;
            }
        }

        const int in_chunk_x = (pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
        const int in_chunk_z = (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH;
#if PROTOCOL_VERSION < 347
        cached->SetBlock(Position(in_chunk_x, pos.y, in_chunk_z), id, metadata, model_id);
#else
        cached->SetBlock(Position(in_chunk_x, pos.y, in_chunk_z), id, model_id);
#endif

        if (in_chunk_x > 0 && in_chunk_x < CHUNK_WIDTH - 1 &&
            in_chunk_z > 0 && in_chunk_z < CHUNK_WIDTH - 1)
        {
            return true;
        }

        Position update_pos;
        if (in_chunk_x == 0)
        {
            update_pos.x = -1;
        }
        else if (in_chunk_x == CHUNK_WIDTH - 1)
        {
            update_pos.x = 1;
        }

        if (in_chunk_z == 0)
        {
            update_pos.z = -1;
        }
        else if (in_chunk_z == CHUNK_WIDTH - 1)
        {
            update_pos.z = 1;
        }

        UpdateChunk(chunk_x, chunk_z, update_pos);

        return true;
    }

    bool World::SetBlockEntityData(const Position &pos, const ProtocolCraft::NBT::Value& data)
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (!cached || cached_x != chunk_x || cached_z != chunk_z)
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;
            }
            else
            {
                return false;
            }
        }

        const Position chunk_pos((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH);
        if (data.HasData())
        {
            cached->SetBlockEntityData(chunk_pos, data);
        }
        else
        {
            cached->RemoveBlockEntityData(chunk_pos);
        }
        UpdateChunk(chunk_x, chunk_z, chunk_pos);

        return true;
    }

#if PROTOCOL_VERSION < 358
    bool World::SetBiome(const int x, const int z, const unsigned char biome)
    {
        auto it = terrain.find({
            static_cast<int>(std::floor(x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(z / static_cast<double>(CHUNK_WIDTH)))
        });

        if (it != terrain.end())
        {
            it->second->SetBiome((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, biome);
            return true;
        }

        return false;
    }
#elif PROTOCOL_VERSION < 552
    bool World::SetBiome(const int x, const int z, const int biome)
    {
        auto it = terrain.find({
            static_cast<int>(std::floor(x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(z / static_cast<double>(CHUNK_WIDTH)))
        });

        if (it != terrain.end())
        {
            it->second->SetBiome((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, biome);
            return true;
        }

        return false;
    }
#else
    bool World::SetBiome(const int x, const int y, const int z, const int biome)
    {
        auto it = terrain.find({
            static_cast<int>(std::floor(x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(z / static_cast<double>(CHUNK_WIDTH)))
        });

        if (it != terrain.end())
        {
            it->second->SetBiome((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, y, (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, biome);
            return true;
        }

        return false;
    }
#endif

    bool World::SetSkyLight(const Position &pos, const unsigned char skylight)
    {
        auto it = terrain.find({
            static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)))
        });

        if (it != terrain.end() &&
#if PROTOCOL_VERSION < 719
            it->second->GetDimension() == Dimension::Overworld)
#else
            it->second->GetDimension() == "minecraft:overworld")
#endif
        {
            it->second->SetSkyLight(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH), skylight);
            return true;
        }

        return false;
    }

    bool World::SetBlockLight(const Position &pos, const unsigned char blocklight)
    {
        auto it = terrain.find({
            static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH))),
            static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)))
        });

        if (it != terrain.end())
        {
            it->second->SetBlockLight(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH), blocklight);
            return true;
        }

        return false;
    }

#if PROTOCOL_VERSION > 404
#if PROTOCOL_VERSION < 719
    void World::UpdateChunkLight(const int x, const int z, const Dimension dim, const int light_mask, const int empty_light_mask,
        const std::vector<std::vector<char>>& data, const bool sky)
#elif PROTOCOL_VERSION < 755
    void World::UpdateChunkLight(const int x, const int z, const std::string& dim, const int light_mask, const int empty_light_mask,
        const std::vector<std::vector<char>>& data, const bool sky)
#else
    void World::UpdateChunkLight(const int x, const int z, const std::string& dim, 
        const std::vector<unsigned long long int>& light_mask, const std::vector<unsigned long long int>& empty_light_mask,
        const std::vector<std::vector<char>>& data, const bool sky)
#endif
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);

        if (chunk == nullptr)
        {
            AddChunk(x, z, dim);
            chunk = GetChunk(x, z);
        }

        int counter_arrays = 0;
        Position pos1, pos2;

        const int num_sections = GetHeight() / 16 + 2;

        for (int i = 0; i < num_sections; ++i)
        {
            const int section_Y = i - 1;

            // Sky light
#if PROTOCOL_VERSION < 755
            if ((light_mask >> i) & 1)
#else
            if ((light_mask.size() > i / 64) && (light_mask[i / 64] >> (i % 64)) & 1)
#endif
            {
                if (i > 0 && i < num_sections - 1)
                {
                    for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                    {
                        pos1.y = block_y + section_Y * SECTION_HEIGHT + GetMinY();
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
#if PROTOCOL_VERSION < 755
            else if ((empty_light_mask >> i) & 1)
#else
            else if ((empty_light_mask.size() > i / 64) && (empty_light_mask[i / 64] >> (i % 64)) & 1)
#endif
            {
                if (i > 0 && i < num_sections - 1)
                {
                    for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                    {
                        pos1.y = block_y + section_Y * SECTION_HEIGHT + GetMinY();
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

    void World::UpdateChunk(const int x, const int z, const Position& pos)
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (pos == Position())
        {
            if (chunk)
            {
                chunk->UpdateNeighbour(GetChunk(x - 1, z), Orientation::West);
                chunk->UpdateNeighbour(GetChunk(x + 1, z), Orientation::East);
                chunk->UpdateNeighbour(GetChunk(x, z - 1), Orientation::North);
                chunk->UpdateNeighbour(GetChunk(x, z + 1), Orientation::South);
            }
            else
            {
                std::shared_ptr<Chunk> neighbour_chunk;
                neighbour_chunk = GetChunk(x - 1, z);
                if (neighbour_chunk)
                {
                    neighbour_chunk->UpdateNeighbour(nullptr, Orientation::East);
                }
                neighbour_chunk = GetChunk(x + 1, z);
                if (neighbour_chunk)
                {
                    neighbour_chunk->UpdateNeighbour(nullptr, Orientation::West);
                }
                neighbour_chunk = GetChunk(x, z - 1);
                if (neighbour_chunk)
                {
                    neighbour_chunk->UpdateNeighbour(nullptr, Orientation::South);
                }
                neighbour_chunk = GetChunk(x, z + 1);
                if (neighbour_chunk)
                {
                    neighbour_chunk->UpdateNeighbour(nullptr, Orientation::North);
                }
            }
            return;
        }
        
        if (pos.x == -1)
        {
            std::shared_ptr<Chunk> neighbour_chunk = GetChunk(x - 1, z);
            if (chunk)
            {
                chunk->UpdateNeighbour(neighbour_chunk, Orientation::West);
            }
            else if (neighbour_chunk)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::East);
            }
        }
        else if (pos.x == 1)
        {
            std::shared_ptr<Chunk> neighbour_chunk = GetChunk(x + 1, z);
            if (chunk)
            {
                chunk->UpdateNeighbour(neighbour_chunk, Orientation::East);
            }
            else if (neighbour_chunk)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::West);
            }
        }

        if (pos.z == -1)
        {
            std::shared_ptr<Chunk> neighbour_chunk = GetChunk(x, z - 1);
            if (chunk)
            {
                chunk->UpdateNeighbour(neighbour_chunk, Orientation::North);
            }
            else if (neighbour_chunk)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::South);
            }
        }
        else if (pos.z == 1)
        {
            std::shared_ptr<Chunk> neighbour_chunk = GetChunk(x, z + 1);
            if (chunk)
            {
                chunk->UpdateNeighbour(neighbour_chunk, Orientation::South);
            }
            else if (neighbour_chunk)
            {
                neighbour_chunk->UpdateNeighbour(nullptr, Orientation::North);
            }
        }
    }

    const std::shared_ptr<const Chunk> World::GetChunkCopy(const int x, const int z)
    {
        std::shared_ptr<Chunk> chunk = GetChunk(x, z);
        if (chunk == nullptr)
        {
            return nullptr;
        }

        return std::shared_ptr<const Chunk>(new Chunk(*chunk));
    }

    const Block* World::GetBlock(const Position &pos)
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (!cached || cached_x != chunk_x || cached_z != chunk_z)
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;
            }
            else
            {
                return nullptr;
            }
        }
        return cached->GetBlock(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH));
    }

    const bool World::IsLoaded(const Position& pos) const
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        return terrain.find({ chunk_x, chunk_z }) != terrain.end();
    }

    const int World::GetHeight() const
    {
#if PROTOCOL_VERSION < 757
        return 256;
#else
        return dimension_height.at(current_dimension);
#endif
    }

    const int World::GetMinY() const
    {
#if PROTOCOL_VERSION < 757
        return 0;
#else
        return dimension_min_y.at(current_dimension);
#endif
    }

    std::shared_ptr<ProtocolCraft::NBT::Value> World::GetBlockEntityData(const Position &pos)
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (cached && cached_x == chunk_x && cached_z == chunk_z)
        {
            return cached->GetBlockEntityData(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH));
        }
        else
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;

                return cached->GetBlockEntityData(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH));
            }
        }

        return nullptr;
    }

#if PROTOCOL_VERSION < 358
    const unsigned char World::GetBiome(const Position &pos)
#else
    const int World::GetBiome(const Position &pos)
#endif
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (!cached || cached_x != chunk_x || cached_z != chunk_z)
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;
            }
            else
            {
                return 0;
            }
        }
#if PROTOCOL_VERSION < 552
        return cached->GetBiome((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH);
#else
        return cached->GetBiome((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH);
#endif
    }

    const unsigned char World::GetSkyLight(const Position &pos)
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (!cached || cached_x != chunk_x || cached_z != chunk_z)
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;
            }
            else
            {
                return 0;
            }
        }

        return cached->GetSkyLight(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH));
    }

    const unsigned char World::GetBlockLight(const Position &pos)
    {
        const int chunk_x = static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH)));
        const int chunk_z = static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)));

        if (!cached || cached_x != chunk_x || cached_z != chunk_z)
        {
            auto it = terrain.find({ chunk_x, chunk_z });

            if (it != terrain.end())
            {
                cached_x = chunk_x;
                cached_z = chunk_z;
                cached = it->second;
            }
            else
            {
                return 0;
            }
        }

        return cached->GetBlockLight(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH));
    }

#if PROTOCOL_VERSION < 719
    const Dimension World::GetDimension(const int x, const int z)
#else
    const std::string World::GetDimension(const int x, const int z)
#endif
    {
        if (!cached || cached_x != x || cached_z != z)
        {
            auto it = terrain.find({ x, z });

            if (it != terrain.end())
            {
                cached_x = x;
                cached_z = z;
                cached = it->second;
            }
            else
            {
#if PROTOCOL_VERSION < 719
                return Dimension::None;
#else
                return "";
#endif
            }
        }
        return cached->GetDimension();
    }

#if PROTOCOL_VERSION > 756
    void World::SetDimensionHeight(const std::string& dimension, const int height)
    {
        dimension_height[dimension] = height;
    }

    void World::SetDimensionMinY(const std::string& dimension, const int min_y)
    {
        dimension_min_y[dimension] = min_y;
    }

    void World::SetCurrentDimension(const std::string& dimension)
    {
        current_dimension = dimension;
    }
#endif


    const std::map<std::pair<int, int>, std::shared_ptr<Chunk> >& World::GetAllChunks() const
    {
        return terrain;
    }

#if PROTOCOL_VERSION > 758
    const int World::GetNextWorldInteractionSequenceId()
    {
        return ++world_interaction_sequence_id;
    }
#endif

    std::shared_ptr<Chunk> World::GetChunk(const int x, const int z)
    {
        if (!cached || cached_x != x || cached_z != z)
        {
            auto it = terrain.find({ x, z });

            if (it != terrain.end())
            {
                cached_x = x;
                cached_z = z;
                cached = it->second;
            }
            else
            {
                return nullptr;
            }
        }

        return cached;
    }

    void World::Handle(ProtocolCraft::ClientboundLoginPacket& msg)
    {
#if PROTOCOL_VERSION < 719
        current_dimension = (Dimension)msg.GetDimension();
#else
        current_dimension = msg.GetDimension().GetFull();
#endif
#if PROTOCOL_VERSION > 756
#if PROTOCOL_VERSION < 759
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
        std::lock_guard<std::mutex> world_guard(world_mutex);
        terrain = std::map<std::pair<int, int>, std::shared_ptr<Chunk> >();

#if PROTOCOL_VERSION < 719
        current_dimension = (Dimension)msg.GetDimension();
#else
        current_dimension = msg.GetDimension().GetFull();
#endif

#if PROTOCOL_VERSION > 756 && PROTOCOL_VERSION < 759
        dimension_height[current_dimension] = msg.GetDimensionType()["height"].get<int>();
        dimension_min_y[current_dimension] = msg.GetDimensionType()["min_y"].get<int>();
#endif
    }

    void World::Handle(ProtocolCraft::ClientboundBlockUpdatePacket& msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);
#if PROTOCOL_VERSION < 347
        unsigned int id;
        unsigned char metadata;
        Blockstate::IdToIdMetadata(msg.GetBlockstate(), id, metadata);
        SetBlock(msg.GetPos(), id, metadata);
#else
        SetBlock(msg.GetPos(), msg.GetBlockstate());
#endif
    }

    void World::Handle(ProtocolCraft::ClientboundSectionBlocksUpdatePacket& msg)
    {
#if PROTOCOL_VERSION < 739
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
                std::lock_guard<std::mutex> world_guard(world_mutex);
#if PROTOCOL_VERSION < 347
                unsigned int id;
                unsigned char metadata;
                Blockstate::IdToIdMetadata(msg.GetRecords()[i].GetBlockId(), id, metadata);

                SetBlock(cube_pos, id, metadata);
#elif PROTOCOL_VERSION < 739
                SetBlock(cube_pos, msg.GetRecords()[i].GetBlockId());
#else
                SetBlock(cube_pos, block_id);
#endif
            }
        }
    }

    void World::Handle(ProtocolCraft::ClientboundForgetLevelChunkPacket& msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);
        RemoveChunk(msg.GetX(), msg.GetZ());
    }

#if PROTOCOL_VERSION < 757
    void World::Handle(ProtocolCraft::ClientboundLevelChunkPacket& msg)
    {
#if PROTOCOL_VERSION < 719
        Dimension chunk_dim;
#else
        std::string chunk_dim;
#endif
        {
            std::lock_guard<std::mutex> world_guard(world_mutex);
            chunk_dim = GetDimension(msg.GetX(), msg.GetZ());
        }

#if PROTOCOL_VERSION < 755
        if (msg.GetFullChunk())
        {
#endif
            bool success = true;

            if (chunk_dim != current_dimension)
            {
                std::lock_guard<std::mutex> world_guard(world_mutex);
                success = AddChunk(msg.GetX(), msg.GetZ(), current_dimension);
            }

            if (!success)
            {
#if PROTOCOL_VERSION < 719
                LOG_ERROR("Error adding chunk in pos : " 
                    << msg.GetX() << ", "
                    << msg.GetZ() << " in dimension "
                    << static_cast<int>(current_dimension));
#else
                LOG_ERROR("Error adding chunk in pos : "
                    << msg.GetX() << ", "
                    << msg.GetZ() << " in dimension "
                    << current_dimension);
#endif
                return;
            }
#if PROTOCOL_VERSION < 755
        }
#endif

        { // lock guard scope
            std::lock_guard<std::mutex> world_guard(world_mutex);
#if PROTOCOL_VERSION < 552
            LoadDataInChunk(msg.GetX(), msg.GetZ(), msg.GetBuffer(), msg.GetAvailableSections(), msg.GetFullChunk());
#else
            LoadDataInChunk(msg.GetX(), msg.GetZ(), msg.GetBuffer(), msg.GetAvailableSections());
#if PROTOCOL_VERSION < 755
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
        std::string chunk_dim;
        {
            std::lock_guard<std::mutex> world_guard(world_mutex);
            chunk_dim = GetDimension(msg.GetX(), msg.GetZ());
        }

        bool success = true;

        if (chunk_dim != current_dimension)
        {
            std::lock_guard<std::mutex> world_guard(world_mutex);
            success = AddChunk(msg.GetX(), msg.GetZ(), current_dimension);
        }

        if (!success)
        {
            LOG_ERROR("Error adding chunk in pos : " << msg.GetX() << ", " << msg.GetZ() << " in dimension " << current_dimension);
            return;
        }

        {
            // lock guard scope
            std::lock_guard<std::mutex> world_guard(world_mutex);
            LoadDataInChunk(msg.GetX(), msg.GetZ(), msg.GetChunkData().GetBuffer());
            LoadBlockEntityDataInChunk(msg.GetX(), msg.GetZ(), msg.GetChunkData().GetBlockEntitiesData());
            UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
                msg.GetLightData().GetSkyYMask(), msg.GetLightData().GetEmptySkyYMask(), msg.GetLightData().GetSkyUpdates(), true);
            UpdateChunkLight(msg.GetX(), msg.GetZ(), current_dimension,
                msg.GetLightData().GetBlockYMask(), msg.GetLightData().GetEmptyBlockYMask(), msg.GetLightData().GetBlockUpdates(), false);
        }
    }
#endif

    const Blockstate* World::Raycast(const Vector3<double> &origin, const Vector3<double> &direction,
        const float max_radius, Position & out_pos, Position & out_normal)
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
            const Block* block = GetBlock(out_pos);

            if (block)
            {
                const Blockstate* blockstate = block->GetBlockstate();
                if (!block->GetBlockstate()->IsAir())
                {
                    const auto& cubes = blockstate->GetModel(block->GetModelId()).GetColliders();
                    for (int i = 0; i < cubes.size(); ++i)
                    {
                        const AABB current_cube = cubes[i] + out_pos;
                        if (current_cube.Intersect(origin, direction))
                        {
                            return blockstate;
                        }
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

#if PROTOCOL_VERSION > 404
    void World::Handle(ProtocolCraft::ClientboundLightUpdatePacket& msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);
#if PROTOCOL_VERSION < 757
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
        std::lock_guard<std::mutex> world_guard(world_mutex);
        SetBlockEntityData(msg.GetPos(), msg.GetTag());
    }

#if PROTOCOL_VERSION > 761
    void World::Handle(ProtocolCraft::ClientboundChunksBiomesPacket& msg)
    {
        std::lock_guard<std::mutex> world_guard(world_mutex);

        for (const auto& chunk_data : msg.GetChunkBiomeData())
        {
            std::shared_ptr<Chunk> chunk = GetChunk(chunk_data.GetX(), chunk_data.GetZ());
            if (chunk)
            {
                chunk->LoadBiomesData(chunk_data.GetBuffer());
            }
            else
            {
                LOG_WARNING("Trying to load biomes data in non loaded chunk (" << chunk_data.GetX() << ", " << chunk_data.GetZ() << ")");
            }
        }
    }
#endif

} // Botcraft
