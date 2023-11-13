#pragma once

#include <memory>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/World/Blockstate.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/BlockEntityInfo.hpp"

namespace Botcraft
{
    class Biome;
    class Section;

    //We assume that a chunk is 16*256*16 in versions before 1.18 and 16*N*16 after
    //And a section is 16*16*16
    static constexpr int CHUNK_WIDTH = 16;
    static constexpr int SECTION_HEIGHT = 16;

    class Chunk
    {
    public:
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        Chunk(const size_t dim_index, const bool has_sky_light_);
#else
        Chunk(const int min_y_, const unsigned int height_, const size_t dim_index, const bool has_sky_light_);
#endif
        Chunk(const Chunk& c);

        static Position BlockCoordsToChunkCoords(const Position& pos);

        int GetMinY() const;
        int GetHeight() const;

#if USE_GUI
        bool GetModifiedSinceLastRender() const;
        void SetModifiedSinceLastRender(const bool b);
#endif

#if PROTOCOL_VERSION < 552 /* < 1.15 */
        void LoadChunkData(const std::vector<unsigned char>& data, const int primary_bit_mask, const bool ground_up_continuous);
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        void LoadChunkData(const std::vector<unsigned char>& data, const int primary_bit_mask);
#elif PROTOCOL_VERSION < 757 /* < 1.18 */
        void LoadChunkData(const std::vector<unsigned char>& data, const std::vector<unsigned long long int>& primary_bit_mask);
#else
        void LoadChunkData(const std::vector<unsigned char>& data);
#endif
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        void LoadChunkBlockEntitiesData(const std::vector<ProtocolCraft::NBT::Value>& block_entities);
#else
        void LoadChunkBlockEntitiesData(const std::vector<ProtocolCraft::BlockEntityInfo>& block_entities);
#endif
        void SetBlockEntityData(const Position& pos, const ProtocolCraft::NBT::Value& block_entity);
        void RemoveBlockEntityData(const Position& pos);
        ProtocolCraft::NBT::Value GetBlockEntityData(const Position& pos) const;

        const Blockstate* GetBlock(const Position& pos) const;

        void SetBlock(const Position& pos, const Blockstate* block);
        void SetBlock(const Position& pos, const BlockstateId id);

        unsigned char GetBlockLight(const Position& pos) const;
        void SetBlockLight(const Position& pos, const unsigned char v);

        unsigned char GetSkyLight(const Position& pos) const;
        void SetSkyLight(const Position& pos, const unsigned char v);

        size_t GetDimensionIndex() const;
        bool GetHasSkyLight() const;

        bool HasSection(const int y) const;
        void AddSection(const int y);

#if PROTOCOL_VERSION < 552 /* < 1.15 */
        const Biome* GetBiome(const int x, const int z) const;
        void SetBiome(const int x, const int z, const int b);
#else
        const Biome* GetBiome(const int x, const int y, const int z) const;
        const Biome* GetBiome(const int i) const;
        void SetBiomes(const std::vector<int>& new_biomes);
        void SetBiome(const int x, const int y, const int z, const int new_biome);
        void SetBiome(const int i, const int new_biome);
#endif
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        void LoadBiomesData(const std::vector<unsigned char>& data);
#endif
        void UpdateNeighbour(Chunk* const neighbour, const Orientation direction);

        /// @brief Add a thread to the loaders list
        /// @param thread_id Id of the thread
        void AddLoader(const std::thread::id& thread_id);
        /// @brief Remove a thread from the loaders list
        /// @param thread_id Id of the thread
        /// @return Number of remaining loaders
        size_t RemoveLoader(const std::thread::id& thread_id);
        
    private:
        bool IsInsideChunk(const Position& pos, const bool ignore_gui_borders) const;
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        void LoadSectionBiomeData(const int section_y, ProtocolCraft::ReadIterator& iter, size_t& length);
#endif
    private:
        std::vector<std::shared_ptr<Section> > sections;
        std::vector<unsigned char> biomes;

        std::unordered_map<Position, ProtocolCraft::NBT::Value> block_entities_data;

        size_t dimension_index;
        bool has_sky_light;

#if PROTOCOL_VERSION < 757 /* < 1.18 */
        static constexpr int min_y = 0;
        static constexpr int height = 256;
#else
        int min_y;
        int height;
#endif
#if USE_GUI
        bool modified_since_last_rendered;
#endif
        std::unordered_set<std::thread::id> loaded_from;
    };
} // Botcraft
