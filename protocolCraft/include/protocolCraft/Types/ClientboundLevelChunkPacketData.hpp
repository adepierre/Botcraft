#pragma once

#if PROTOCOL_VERSION > 756
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/BlockEntityInfo.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelChunkPacketData : public NetworkType
    {
    public:
        virtual ~ClientboundLevelChunkPacketData() override
        {

        }

        void SetHeightmaps(const NBT& heightmaps_)
        {
            heightmaps = heightmaps_;
        }

        void SetBuffer(const std::vector<unsigned char>& buffer_)
        {
            buffer = buffer_;
        }

        void SetBlockEntitiesData(const std::vector<BlockEntityInfo>& block_entities_data_)
        {
            block_entities_data = block_entities_data_;
        }


        const NBT& GetHeightmaps() const
        {
            return heightmaps;
        }

        const std::vector<unsigned char>& GetBuffer() const
        {
            return buffer;
        }

        const std::vector<BlockEntityInfo>& GetBlockEntitiesData() const
        {
            return block_entities_data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            heightmaps = ReadData<NBT>(iter, length);

            const int buffer_size = ReadData<VarInt>(iter, length);
            buffer = ReadByteArray(iter, length, buffer_size);

            const int num_block_entities_data = ReadData<VarInt>(iter, length);
            block_entities_data = std::vector<BlockEntityInfo>(num_block_entities_data);
            for (int i = 0; i < num_block_entities_data; ++i)
            {
                block_entities_data[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<NBT>(heightmaps, container);
            WriteData<VarInt>(static_cast<int>(buffer.size()), container);
            WriteByteArray(buffer, container);
            WriteData<VarInt>(static_cast<int>(block_entities_data.size()), container);
            for (int i = 0; i < block_entities_data.size(); ++i)
            {
                block_entities_data[i].Write(container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["heightmaps"] = heightmaps.Serialize();

            output["buffer"] = "Vector of " + std::to_string(buffer.size()) + " unsigned char";

            output["block_entities_data"] = nlohmann::json::array();
            for (int i = 0; i < block_entities_data.size(); ++i)
            {
                output["block_entities_data"].push_back(block_entities_data[i].Serialize());
            }

            return output;
        }

    private:
        NBT heightmaps;
        std::vector<unsigned char> buffer;
        std::vector<BlockEntityInfo> block_entities_data;
    };
}
#endif
