#pragma once

#include <map>
#include <array>
#include <memory>
#include <mutex>

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/Game/Enums.hpp"

#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Handler.hpp"

namespace Botcraft
{
    class Chunk;
    class Block;
    class Blockstate;

    class World : public ProtocolCraft::Handler
    {
    public:
        World(const bool is_shared_);

        std::mutex& GetMutex();
        const bool IsShared() const;

#if PROTOCOL_VERSION < 719
        bool AddChunk(const int x, const int z, const Dimension dim);
#else
        bool AddChunk(const int x, const int z, const std::string& dim);
#endif
        bool RemoveChunk(const int x, const int z);

#if USE_GUI
        const bool HasChunkBeenModified(const int x, const int z);
        void ResetChunkModificationState(const int x, const int z);
#endif

        bool LoadDataInChunk(const int x, const int z, const std::vector<unsigned char>& data,
            const int primary_bit_mask, const bool ground_up_continuous);
        bool LoadBlockEntityDataInChunk(const int x, const int z, const std::vector<ProtocolCraft::NBT>& block_entities);

        // Update the neighbour blocks of this chunk and the
        // one in the specified direction, if direction is 0,0,0
        // then update all neighbours chunks
        void UpdateChunk(const int x, const int z, const Position& pos = Position());

        const std::shared_ptr<const Chunk> GetChunkCopy(const int x, const int z);

#if PROTOCOL_VERSION < 347
        bool SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id = -1);
#else
        bool SetBlock(const Position &pos, const unsigned int id, const int model_id = -1);
#endif
        //Get the block at a given position
        const Block* GetBlock(const Position& pos);
        const bool IsLoaded(const Position& pos) const;

        bool SetBlockEntityData(const Position &pos, const ProtocolCraft::NBT& data);
        // Get the block entity data at a given position
        std::shared_ptr<ProtocolCraft::NBT> GetBlockEntityData(const Position& pos);

#if PROTOCOL_VERSION < 358
        bool SetBiome(const int x, const int z, const unsigned char biome);
#elif PROTOCOL_VERSION < 552
        bool SetBiome(const int x, const int z, const int biome);
#else
		bool SetBiome(const int x, const int y, const int z, const int biome);
#endif

#if PROTOCOL_VERSION < 358
        const unsigned char GetBiome(const Position & pos);
#else
        const int GetBiome(const Position& pos);
#endif

        bool SetSkyLight(const Position &pos, const unsigned char skylight);
        bool SetBlockLight(const Position &pos, const unsigned char blocklight);
#if PROTOCOL_VERSION > 404 && PROTOCOL_VERSION < 719
        void UpdateChunkLight(const int x, const int z, const Dimension dim, const int light_mask, const int empty_light_mask, const std::vector<std::vector<char> >& data, const bool sky);
#elif PROTOCOL_VERSION > 718
        void UpdateChunkLight(const int x, const int z, const std::string& dim, const int light_mask, const int empty_light_mask, const std::vector<std::vector<char> >& data, const bool sky);
#endif
        const unsigned char GetSkyLight(const Position& pos);
        const unsigned char GetBlockLight(const Position& pos);

#if PROTOCOL_VERSION < 719
        const Dimension GetDimension(const int x, const int z);
#else
        const std::string GetDimension(const int x, const int z);
#endif

        /**
        * Perform a raycast in the voxel world and return position, normal and blockstate which are hit
        *
        * @param[in] origin the origin of the ray
        * @param[in] direction the direction of the ray
        * @param[in] max_radius maximum distance of the search, must be > 0
        * @param[out] out_pos the position of the block hit
        * @param[out] out_normal the normal of the face hit
        * @return the blockstate of the hit cube (or null)
        */
        std::shared_ptr<Blockstate> Raycast(const Vector3<double> &origin, const Vector3<double> &direction,
            const float max_radius, Position &out_pos, Position &out_normal);

        // Get the list of chunks
        const std::map<std::pair<int, int>, std::shared_ptr<Chunk> >& GetAllChunks() const;

    private:
        std::shared_ptr<Chunk> GetChunk(const int x, const int z);

    protected:
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundBlockUpdatePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundSectionBlocksUpdatePacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundForgetLevelChunkPacket& msg) override;
        virtual void Handle(ProtocolCraft::ClientboundLevelChunkPacket& msg) override;
#if PROTOCOL_VERSION > 404
        virtual void Handle(ProtocolCraft::ClientboundLightUpdatePacket& msg) override;
#endif
        virtual void Handle(ProtocolCraft::ClientboundBlockEntityDataPacket& msg) override;

    private:
        int cached_x;
        int cached_z;
        std::mutex world_mutex;
        std::shared_ptr<Chunk> cached;

        std::map<std::pair<int, int>, std::shared_ptr<Chunk> > terrain;

        bool is_shared;
#if PROTOCOL_VERSION < 719
        Dimension current_dimension;
#else
        std::string current_dimension;
#endif
    };
} // Botcraft