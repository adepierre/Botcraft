#include "botcraft/Game/Chunk.hpp"
#include "botcraft/Game/Section.hpp"

namespace Botcraft
{
    Chunk::Chunk(const Dimension &dim)
    {
        dimension = dim;
#if PROTOCOL_VERSION < 358
        biomes = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH);
#else
        biomes = std::vector<int>(CHUNK_WIDTH * CHUNK_WIDTH);
#endif
        sections = std::vector<std::shared_ptr<Section> >(CHUNK_HEIGHT / SECTION_HEIGHT);
    }

    const Block *Chunk::GetBlock(const Position &pos) const
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return nullptr;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            return nullptr;
        }

        return sections[pos.y / SECTION_HEIGHT]->data_blocks.data() + ((pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x);
    }

#if PROTOCOL_VERSION < 347
    void Chunk::SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id)
#else
    void Chunk::SetBlock(const Position &pos, const unsigned int id, const int model_id)
#endif
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            AddSection(pos.y / SECTION_HEIGHT);
        }
        Block *block = sections[pos.y / SECTION_HEIGHT]->data_blocks.data() + ((pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x);

#if PROTOCOL_VERSION < 347
        block->ChangeBlockstate(id, metadata, model_id);
#else
        block->ChangeBlockstate(id, model_id);
#endif
    }

    const unsigned char Chunk::GetBlockLight(const Position &pos) const
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return 0;
        }
        
        if (!sections[pos.y / SECTION_HEIGHT])
        {
            return 0;
        }

        return sections[pos.y / SECTION_HEIGHT]->block_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x];
    }

    void Chunk::SetBlockLight(const Position &pos, const unsigned char v)
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            AddSection(pos.y / SECTION_HEIGHT);
        }

        sections[pos.y / SECTION_HEIGHT]->block_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x] = v;
    }

    const unsigned char Chunk::GetSkyLight(const Position &pos) const
    {
        if (dimension != Dimension::Overworld || pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return 0;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            return 0;
        }

        return sections[pos.y / SECTION_HEIGHT]->sky_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x];
    }

    void Chunk::SetSkyLight(const Position &pos, const unsigned char v)
    {
        if (dimension != Dimension::Overworld || pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            AddSection(pos.y / SECTION_HEIGHT);
        }

        sections[pos.y / SECTION_HEIGHT]->block_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x] = v;
}

#if PROTOCOL_VERSION < 358
    const unsigned char Chunk::GetBiome(const int x, const int z) const
#else
    const int Chunk::GetBiome(const int x, const int z) const
#endif
    {
        if (x < 0 || x > CHUNK_WIDTH - 1 || z < 0 || z > CHUNK_WIDTH - 1)
        {
            return 0;
        }

        return biomes[z * CHUNK_WIDTH + x];
    }

#if PROTOCOL_VERSION < 358
    void Chunk::SetBiome(const int x, const int z, const unsigned char b)
#else
    void Chunk::SetBiome(const int x, const int z, const int b)
#endif
    {
        if (x < 0 || x > CHUNK_WIDTH - 1 || z < 0 || z > CHUNK_WIDTH - 1)
        {
            return;
        }

        biomes[z * CHUNK_WIDTH + x] = b;
    }

    std::shared_ptr<NBT> Chunk::GetBlockEntityData(const Position &pos)
    {
        auto it = block_entities_data.find(pos);
        if (it == block_entities_data.end())
        {
            return nullptr;
        }

        return it->second;
    }

    const Dimension Chunk::GetDimension() const
    {
        return dimension;
    }

    std::map<Position, std::shared_ptr<NBT> >& Chunk::GetBlockEntitiesData()
    {
        return block_entities_data;
    }

    const std::map<Position, std::shared_ptr<NBT> >& Chunk::GetBlockEntitiesData() const
    {
        return block_entities_data;
    }

    const bool Chunk::HasSection(const int y) const
    {
        return sections[y] != nullptr;
    }

    void Chunk::AddSection(const int y)
    {
        sections[y] = std::shared_ptr<Section>(new Section(dimension == Dimension::Overworld));
    }

} //Botcraft