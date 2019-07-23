#pragma once

#include <vector>
#include <map>
#include <memory>

#include "botcraft/Game/Block.hpp"
#include "botcraft/NBT/NBT.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    struct Section;

    //We assume that a chunk is 16*256*16
    //And a section is 16*16*16
    static const unsigned int CHUNK_WIDTH = 16;
    static const unsigned int SECTION_HEIGHT = 16;
    static const unsigned int CHUNK_HEIGHT = 256;

    class Chunk
    {
    public:
        Chunk(const Dimension &dim = Dimension::Overworld);

        const Block *GetBlock(const Position &pos) const;
#if PROTOCOL_VERSION < 347
        void SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id = -1);
#else
        void SetBlock(const Position &pos, const unsigned int id, const int model_id = -1);
#endif
        const unsigned char GetBlockLight(const Position &pos) const;
        void SetBlockLight(const Position &pos, const unsigned char v);
        const unsigned char GetSkyLight(const Position &pos) const;
        void SetSkyLight(const Position &pos, const unsigned char v);
        const Dimension GetDimension() const;

        std::map<Position, std::shared_ptr<NBT> >& GetBlockEntitiesData();
        const std::map<Position, std::shared_ptr<NBT> >& GetBlockEntitiesData() const;

        const bool HasSection(const int y) const;
        void AddSection(const int y);

#if PROTOCOL_VERSION < 358
        const unsigned char GetBiome(const int x, const int z) const;
        void SetBiome(const int x, const int z, const unsigned char b);
#else
        const int GetBiome(const int x, const int z) const;
        void SetBiome(const int x, const int z, const int b);
#endif
        std::shared_ptr<NBT> GetBlockEntityData(const Position &pos);
        
    private:
        std::vector<std::shared_ptr<Section> > sections;
#if PROTOCOL_VERSION < 358
        std::vector<unsigned char> biomes;
#else
        std::vector<int> biomes;
#endif
        std::map<Position, std::shared_ptr<NBT> > block_entities_data;
        Dimension dimension;
    };
} // Botcraft