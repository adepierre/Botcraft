#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/Block.hpp"
#include "botcraft/NBT/NBT.hpp"
#include "botcraft/Game/Enums.hpp"

#include <iostream>
#include <fstream>
namespace Botcraft
{
    World::World()
    {

    }

    bool World::AddChunk(const int x, const int z, const Dimension dim)
    {
        if (RemoveChunk(x, z))
        {
            std::cerr << "Warning, trying to add a new chunk over an existing one. Deleting previous chunk." << std::endl;
        }

        terrain[{x, z}] = std::shared_ptr<Chunk>(new Chunk(dim));

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

            return true;
        }

        return false;
    }

#if PROTOCOL_VERSION < 347
    bool World::SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id)
#else
    bool World::SetBlock(const Position &pos, const unsigned int id, const int model_id)
#endif
    {
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

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

#if PROTOCOL_VERSION < 347
        cached->SetBlock(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH), id, metadata, model_id);
#else
        cached->SetBlock(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH), id, model_id);
#endif
        return true;
    }

    bool World::SetBlockEntityData(const Position &pos, const std::shared_ptr<NBT> data)
    {
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

        if (!cached || cached_x != chunk_x || !cached_z == chunk_z)
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

        if (data && data->HasData())
        {
            cached->GetBlockEntitiesData()[pos] = data;
        }
        else
        {
            cached->GetBlockEntitiesData().erase(pos);
        }
        return true;
    }

#if PROTOCOL_VERSION < 358
    bool World::SetBiome(const int x, const int z, const unsigned char biome)
#else
    bool World::SetBiome(const int x, const int z, const int biome)
#endif
    {
        auto it = terrain.find({ floor(x / (double)CHUNK_WIDTH), floor(z / (double)CHUNK_WIDTH) });

        if (it != terrain.end())
        {
            it->second->SetBiome((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, biome);
            return true;
        }

        return false;
    }

    bool World::SetSkyLight(const Position &pos, const unsigned char skylight)
    {
        auto it = terrain.find({ floor(pos.x / (double)CHUNK_WIDTH), floor(pos.z / (double)CHUNK_WIDTH) });

        if (it != terrain.end() && it->second->GetDimension() == Dimension::Overworld)
        {
            it->second->SetSkyLight(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH), skylight);
            return true;
        }

        return false;
    }

    bool World::SetBlockLight(const Position &pos, const unsigned char blocklight)
    {
        auto it = terrain.find({ floor(pos.x / (double)CHUNK_WIDTH), floor(pos.z / (double)CHUNK_WIDTH) });

        if (it != terrain.end())
        {
            it->second->SetBlockLight(Position((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, pos.y, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH), blocklight);
            return true;
        }

        return false;
    }

    const Block* World::GetBlock(const Position &pos)
    {
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

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

    std::shared_ptr<NBT> World::GetBlockEntityData(const Position &pos)
    {
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

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
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

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
        return cached->GetBiome((pos.x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, (pos.z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH);
    }

    const unsigned char World::GetSkyLight(const Position &pos)
    {
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

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
        int chunk_x = (int)floor(pos.x / (double)CHUNK_WIDTH);
        int chunk_z = (int)floor(pos.z / (double)CHUNK_WIDTH);

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

    const Dimension World::GetDimension(const int x, const int z)
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
                return Dimension::Overworld;
            }
        }
        return cached->GetDimension();
    }


    const std::map<std::pair<int, int>, std::shared_ptr<Chunk> >& World::GetAllChunks() const
    {
        return terrain;
    }

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

    std::shared_ptr<Blockstate> World::Raycast(const Vector3<double> &origin, const Vector3<double> &direction,
        const float max_radius, Position &out_pos, Position &out_normal)
    {
        // Inspired from https://gist.github.com/dogfuntom/cc881c8fc86ad43d55d8
        // Searching along origin + t * direction line

        // Position of the current cube examined
        out_pos = Position(std::floor(origin.x), std::floor(origin.y), std::floor(origin.z));

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
            throw(std::runtime_error("Raycasting with null direction"));
        }

        const float radius = max_radius / std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

        while (true)
        {
            const Block* block = GetBlock(out_pos);

            if (block)
            {
                std::shared_ptr<Blockstate> blockstate = block->GetBlockstate();
                if (!block->GetBlockstate()->IsAir())
                {
                    const auto &cubes = blockstate->GetModel(block->GetModelId()).GetColliders();
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

                out_pos.x += step.x;
                tMax.x += tDelta.x;
                out_normal.x = -step.x;
                out_normal.y = 0;
                out_normal.z = 0;
            }
            else if (tMax.y < tMax.x && tMax.y < tMax.z)
            {
                if (tMax.y > radius)
                {
                    return nullptr;
                }
                out_pos.y += step.y;
                tMax.y += tDelta.y;
                out_normal[0] = 0;
                out_normal[1] = -step.y;
                out_normal[2] = 0;
            }
            else // tMax.z < tMax.x && tMax.z < tMax.y
            {
                if (tMax.z > radius)
                {
                    return nullptr;
                }

                out_pos.z += step.z;
                tMax.z += tDelta.z;
                out_normal.x = 0;
                out_normal.x = 0;
                out_normal.x = -step.z;
            }
        }
    }

    void World::AddPlayer(const OtherPlayer &p)
    {
        all_players[p.GetUUID()] = p;
    }

    std::map<std::string, OtherPlayer>::iterator World::GetPlayer(const std::string &uuid)
    {
        return all_players.find(uuid);
    }

    const std::map<std::string, OtherPlayer>& World::GetAllPlayers() const
    {
        return all_players;
    }

    void World::RemovePlayer(const std::string &uuid)
    {
        all_players.erase(uuid);
    }

} // Botcraft