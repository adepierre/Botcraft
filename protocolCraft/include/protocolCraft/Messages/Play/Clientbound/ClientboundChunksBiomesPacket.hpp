#if PROTOCOL_VERSION > 761

#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/ChunkBiomeData.hpp"

namespace ProtocolCraft
{
    class ClientboundChunksBiomesPacket : public BaseMessage<ClientboundChunksBiomesPacket>
    {
    public:
#if PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x0D;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Chunks Biome";

        virtual ~ClientboundChunksBiomesPacket() override
        {

        }

        void SetChunkBiomeData(const std::vector<ChunkBiomeData>& chunk_biome_data_)
        {
            chunk_biome_data = chunk_biome_data_;
        }


        const std::vector<ChunkBiomeData>& GetChunkBiomeData() const
        {
            return chunk_biome_data;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            chunk_biome_data = ReadVector<ChunkBiomeData>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVector<ChunkBiomeData>(chunk_biome_data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["chunk_biome_data"] = chunk_biome_data;

            return output;
        }

    private:
        std::vector<ChunkBiomeData> chunk_biome_data;

    };
} //ProtocolCraft
#endif
