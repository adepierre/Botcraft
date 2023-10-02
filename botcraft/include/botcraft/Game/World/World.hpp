#pragma once

#include <atomic>
#include <memory>
#include <shared_mutex>
#include <unordered_map>

#include "botcraft/Game/Enums.hpp"
#include "botcraft/Game/World/Blockstate.hpp"
#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Utilities/ScopeLockedWrapper.hpp"

#include "protocolCraft/Handler.hpp"

namespace std
{
    template<>
    struct hash<pair<int, int>>
    {
        inline size_t operator()(const pair<int, int>& p) const
        {
            hash<float> hasher;
            size_t value = hasher(p.first);
            value ^= hasher(p.second) + 0x9e3779b9 + (value << 6) + (value >> 2);
            return value;
        }
    };
}

namespace Botcraft
{
    class Biome;

    class World : public ProtocolCraft::Handler
    {
    public:
        /// @brief
        /// @param is_shared_ If true, this world can be shared by multiple bot
        /// instances (assuming they all are and stay in the **same dimension**)
        World(const bool is_shared_);

        ~World();

        /// @brief Check if a position is in a loaded chunk. Thread-safe
        /// @param pos Block position
        /// @return True if the chunk is loaded, false otherwise
        bool IsLoaded(const Position& pos) const;

        /// @brief is_shared getter
        /// @return True if world is a shared one, false otherwise
        bool IsShared() const;

        /// @brief Get height of the current dimension
        /// @return 256 for versions prior to 1.18, current dimension height otherwise
        int GetHeight() const;

        /// @brief Get min_y of the current dimension
        /// @return 0 for versions prior to 1.18, current dimension min_y otherwise
        int GetMinY() const;

        /// @brief Check if a chunk modification flag is set. Thread-safe
        /// @param x Chunk X coordinate
        /// @param z Chunk Z coordinate
        /// @return True if chunk flag is set, false otherwise
        bool HasChunkBeenModified(const int x, const int z);

        /// @brief Reset a chunk modification state. Thread-safe
        /// @param x Chunk X coordinate
        /// @param z Chunk Z coordinate
        /// @return A copy of the chunk, or nothing if chunk is not loaded
        std::optional<Chunk> ResetChunkModificationState(const int x, const int z);

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        /// @brief Add a chunk at given coordinates. If already exists in another dimension, will be erased first. Thread-safe
        /// @param x X chunk coordinate
        /// @param z Z chunk coordinate
        /// @param dim Dimension in which the chunk is added
        /// @param loader_id Id of the loader of this chunk (used for shared worlds), default: current thread id
        void LoadChunk(const int x, const int z, const Dimension dim, const std::thread::id& loader_id = std::this_thread::get_id());
#else
        /// @brief Add a chunk at given coordinates. If already exists in another dimension, will be erased first. Thread-safe
        /// @param x X chunk coordinate
        /// @param z Z chunk coordinate
        /// @param dim Dimension in which the chunk is added
        /// @param loader_id Id of the loader of this chunk (used for shared worlds), default: current thread id
        void LoadChunk(const int x, const int z, const std::string& dim, const std::thread::id& loader_id = std::this_thread::get_id());
#endif
        /// @brief Remove a chunk at given coordinates. Thread-safe
        /// @param x X chunk coordinate
        /// @param z Z chunk coordinate
        /// @param loader_id Id of the loader of this chunk (used for shared worlds), default: current thread id
        void UnloadChunk(const int x, const int z, const std::thread::id& loader_id = std::this_thread::get_id());

        /// @brief Remove all chunks from memory
        /// @param loader_id Id of the loader of this chunk (used for shared worlds), default: current thread id
        void UnloadAllChunks(const std::thread::id& loader_id = std::this_thread::get_id());


        /// @brief Set block at given pos. Does nothing if pos is not loaded. Thread-safe
        /// @param pos Position of the block to set
        /// @param id Id of the desired block
        void SetBlock(const Position& pos, const BlockstateId id);

        /// @brief Get the blockstate at a given position. Thread-safe
        /// @param pos Position of the block
        /// @return A const pointer to the blockstate at position, nullptr if not loaded
        const Blockstate* GetBlock(const Position& pos) const;

        /// @brief Get blockstates for a set of positions. More efficient than calling multiple times GetBlock. Thread-safe
        /// @param pos Positions of the blocks
        /// @return A vector of const pointer to the blockstate at each position, nullptr if not loaded
        std::vector<const Blockstate*> GetBlocks(const std::vector<Position>& pos) const;

        Utilities::ScopeLockedWrapper<const std::unordered_map<std::pair<int, int>, Chunk>, std::shared_mutex, std::shared_lock> GetTerrain() const;

#if PROTOCOL_VERSION < 358 /* < 1.13 */
        /// @brief Set biome of given block column. Does nothing if not loaded. Thread-safe
        /// @param x Column X coordinate
        /// @param z Column Z coordinate
        /// @param biome Id of the desired biome
        void SetBiome(const int x, const int z, const unsigned char biome);
#elif PROTOCOL_VERSION < 552 /* < 1.15 */
        /// @brief Set biome of given block column. Does nothing if not loaded. Thread-safe
        /// @param x Column X coordinate
        /// @param z Column Z coordinate
        /// @param biome Id of the desired biome
        void SetBiome(const int x, const int z, const int biome);
#else
        /// @brief Set biome of given block. Does nothing if not loaded. Thread-safe
        /// @param x X coordinate
        /// @param y Y coordinate
        /// @param z Z coordinate
        /// @param biome Id of the desired biome
        void SetBiome(const int x, const int y, const int z, const int biome);
#endif
        /// @brief Get the biome at a given position. Thread-safe
        /// @param pos Block position
        /// @return A pointer to the biome, nullptr if not loaded
        const Biome* GetBiome(const Position& pos) const;

        /// @brief Set sky light value. Thread-safe
        /// @param pos Block position
        /// @param skylight Desired sky light value
        void SetSkyLight(const Position& pos, const unsigned char skylight);
        /// @brief Set block light value. Thread-safe
        /// @param pos Block position
        /// @param blocklight Desired block light value
        void SetBlockLight(const Position& pos, const unsigned char blocklight);

        /// @brief Get sky light value. Thread-safe
        /// @param pos Block position
        /// @return Sky light value at pos, 0 if not loaded or in dimension with no sky light
        unsigned char GetSkyLight(const Position& pos) const;
        /// @brief Get block light value. Thread-safe
        /// @param pos Block position
        /// @return Block light value at pos, 0 if not loaded
        unsigned char GetBlockLight(const Position& pos) const;

        /// @brief Set block entity data at pos. Thread-safe
        /// @param pos Position of the block entity
        /// @param data Data to set
        void SetBlockEntityData(const Position& pos, const ProtocolCraft::NBT::Value& data);

        /// @brief Get the block entity data at a given position. Thread-safe
        /// @param pos Position of the block entity
        /// @return Copy of the data at pos
        ProtocolCraft::NBT::Value GetBlockEntityData(const Position& pos) const;

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        /// @brief Get dimension of chunk at given coordinates. Thread-safe
        /// @param x X chunk coordinate
        /// @param z Z chunk coordinate
        /// @return Dimension of the chunk, Dimension::None if chunk is not loaded
        Dimension GetDimension(const int x, const int z) const;
#else
        /// @brief Get dimension of chunk at given coordinates. Thread-safe
        /// @param x X chunk coordinate
        /// @param z Z chunk coordinate
        /// @return Dimension of the chunk, empty if chunk is not loaded
        std::string GetDimension(const int x, const int z) const;
#endif

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        /// @brief Set current world dimension. Thread-safe
        /// @param dimension Dimension to set
        void SetCurrentDimension(const Dimension dimension);
#else
        /// @brief Set current world dimension. Thread-safe
        /// @param dimension Dimension to set
        void SetCurrentDimension(const std::string& dimension);
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        /// @brief Set total height for given dimension. Thread-safe
        /// @param dimension Dimension to set height for
        /// @param height Total height of dimension
        void SetDimensionHeight(const std::string& dimension, const int height);
        /// @brief Set min block for given dimension. Thread-safe
        /// @param dimension Dimension to set min_y for
        /// @param min_y Min block of dimension
        void SetDimensionMinY(const std::string& dimension, const int min_y);
#endif

        /// @brief Perform a raycast in the voxel world and return position, normal and blockstate which are hit. Thread-safe
        /// @param origin origin the origin of the ray
        /// @param direction direction the direction of the ray
        /// @param max_radius max_radius maximum distance of the search, must be > 0
        /// @param out_pos out_pos the position of the block hit
        /// @param out_normal out_normal the normal of the face hit
        /// @return a pointer to the blockstate of the hit cube (nullptr if not hit)
        const Blockstate* Raycast(const Vector3<double>& origin, const Vector3<double>& direction,
            const float max_radius, Position& out_pos, Position& out_normal);

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        /// @brief Get a unique id used for server interactions. Thread-safe
        /// @return Unique id
        int GetNextWorldInteractionSequenceId();
#endif

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundBlockUpdatePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSectionBlocksUpdatePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundForgetLevelChunkPacket& msg) override;
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        virtual void Handle(ProtocolCraft::ClientboundLevelChunkPacket& msg) override;
#else
        virtual void Handle(ProtocolCraft::ClientboundLevelChunkWithLightPacket& msg) override;
#endif
#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
        virtual void Handle(ProtocolCraft::ClientboundLightUpdatePacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundBlockEntityDataPacket& msg) override;
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        virtual void Handle(ProtocolCraft::ClientboundChunksBiomesPacket& msg) override;
#endif
#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
        virtual void Handle(ProtocolCraft::ClientboundRegistryDataPacket& msg) override;
#endif

    private:
#if PROTOCOL_VERSION < 719 /* < 1.16 */
        void LoadChunkImpl(const int x, const int z, const Dimension dim, const std::thread::id& loader_id);
#else
        void LoadChunkImpl(const int x, const int z, const std::string& dim, const std::thread::id& loader_id);
#endif
        void UnloadChunkImpl(const int x, const int z, const std::thread::id& loader_id);

        void SetBlockImpl(const Position& pos, const BlockstateId id);
        const Blockstate* GetBlockImpl(const Position& pos) const;

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        void SetCurrentDimensionImpl(const Dimension dimension);
#else
        void SetCurrentDimensionImpl(const std::string& dimension);
#endif

        int GetHeightImpl() const;
        int GetMinYImpl() const;

#if PROTOCOL_VERSION < 358 /* < 1.13 */
        void SetBiomeImpl(const int x, const int z, const unsigned char biome);
#elif PROTOCOL_VERSION < 552 /* < 1.15 */
        void SetBiomeImpl(const int x, const int z, const int biome);
#else
        void SetBiomeImpl(const int x, const int y, const int z, const int biome);
#endif

        /// @brief Progagate chunk update at pos to neighbouring chunks
        /// @param chunk_x Chunk X
        /// @param chunk_z Chunk Z
        /// @param pos World coordinates of updated block
        void UpdateChunk(const int chunk_x, const int chunk_z, const Position& pos);

        /// @brief Progagate whole chunk update to neighbouring chunks
        /// @param chunk_x Chunk X
        /// @param chunk_z Chunk Z
        void UpdateChunk(const int chunk_x, const int chunk_z);

        /// @brief Get a pointer to a chunk. Not thread-safe
        /// @param x Chunk X
        /// @param z Chunk Z
        /// @return Pointer to the chunk, or nullptr if not loaded
        Chunk* GetChunk(const int x, const int z);

#if PROTOCOL_VERSION < 552 /* < 1.15 */
        void LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
            const int primary_bit_mask, const bool ground_up_continuous);
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        void LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
            const int primary_bit_mask);
#elif PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        void LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
            const std::vector<unsigned long long int>& primary_bit_mask);
#else
        void LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data);
#endif

#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        void LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::NBT::Value>& block_entities);
#else
        void LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::BlockEntityInfo>& block_entities);
#endif

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        void LoadBiomesInChunk(const int x, const int z, const std::vector<int>& biomes);
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 719 /* < 1.16 */
        void UpdateChunkLight(const int x, const int z, const Dimension dim, const int light_mask, const int empty_light_mask, const std::vector<std::vector<char> >& data, const bool sky);
#elif PROTOCOL_VERSION > 718 /* > 1.15.2 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        void UpdateChunkLight(const int x, const int z, const std::string& dim, const int light_mask, const int empty_light_mask, const std::vector<std::vector<char> >& data, const bool sky);
#elif PROTOCOL_VERSION > 754 /* > 1.16.4/5 */
        void UpdateChunkLight(const int x, const int z, const std::string& dim,
            const std::vector<unsigned long long int>& light_mask, const std::vector<unsigned long long int>& empty_light_mask,
            const std::vector<std::vector<char> >& data, const bool sky);
#endif

#if PROTOCOL_VERSION < 719 /* < 1.16 */
        size_t GetDimIndex(const Dimension dim);
#else
        size_t GetDimIndex(const std::string& dim);
#endif

    private:
        std::unordered_map<std::pair<int, int>, Chunk> terrain;
        mutable std::shared_mutex world_mutex;

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */ && PROTOCOL_VERSION < 757 /* < 1.18/.1 */
        std::unordered_map<std::pair<int, int>, ProtocolCraft::ClientboundLightUpdatePacket> delayed_light_updates;
#endif

        const bool is_shared;
#if PROTOCOL_VERSION < 719 /* < 1.16 */
        Dimension current_dimension;
        std::unordered_map<Dimension, size_t> dimension_index_map;
        std::unordered_map<size_t, Dimension> index_dimension_map;
#else
        std::string current_dimension;
        std::unordered_map<std::string, size_t> dimension_index_map;
        std::unordered_map<size_t, std::string> index_dimension_map;
#endif

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        std::atomic<int> world_interaction_sequence_id;
#endif

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
        /// @brief Height of the chunks in a given dimension
        std::unordered_map<std::string, unsigned int> dimension_height;
        /// @brief Height of the lowest block in a given dimension
        std::unordered_map<std::string, int> dimension_min_y;
#endif
    };
} // Botcraft
