#pragma once

#include <vector>
#include <map>
#include <memory>

#include "botcraft/Game/World/Block.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    struct Section;
    class NBT;

    //We assume that a chunk is 16*256*16
    //And a section is 16*16*16
    static const int CHUNK_WIDTH = 16;
    static const int SECTION_HEIGHT = 16;
    static const int CHUNK_HEIGHT = 256;

#if PROTOCOL_VERSION > 551
	static const unsigned int BIOMES_SIZE = 1024;
#endif

    class Chunk
    {
    public:
        Chunk(const Dimension &dim = Dimension::Overworld);
        Chunk(const Chunk& c);

        static const Position BlockCoordsToChunkCoords(const Position& pos);

#if USE_GUI
        const bool GetModifiedSinceLastRender() const;
        void SetModifiedSinceLastRender(const bool b);
#endif

        void LoadChunkData(const std::vector<unsigned char>& data, const int primary_bit_mask, const bool ground_up_continuous);
        void LoadChunkBlockEntitiesData(const std::vector<unsigned char>& data, const int number_block_entities);

        const Block *GetBlock(const Position &pos) const;
#if PROTOCOL_VERSION < 347
        void SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id = -1);
#else
        void SetBlock(const Position &pos, const unsigned int id, const int model_id = -1);
#endif
        void SetBlock(const Position& pos, const Block* block);

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
#elif PROTOCOL_VERSION < 552
        const int GetBiome(const int x, const int z) const;
        void SetBiome(const int x, const int z, const int b);
#else
		const int GetBiome(const int x, const int y, const int z) const;
		const int GetBiome(const int i) const;
		void SetBiomes(const std::vector<int>& new_biomes);
		void SetBiome(const int x, const int y, const int z, const int new_biome);
		void SetBiome(const int i, const int new_biome);
#endif
        std::shared_ptr<NBT> GetBlockEntityData(const Position &pos);
        void UpdateNeighbour(const std::shared_ptr<Chunk> neighbour, const Orientation direction);
        
    private:
        std::vector<std::shared_ptr<Section> > sections;
#if PROTOCOL_VERSION < 358
        std::vector<unsigned char> biomes;
#else
        std::vector<int> biomes;
#endif
        std::map<Position, std::shared_ptr<NBT> > block_entities_data;
        Dimension dimension;

#if USE_GUI
        bool modified_since_last_rendered;
#endif
    };
} // Botcraft