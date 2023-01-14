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

        void SetHeightmaps(const NBT::Value& heightmaps_)
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


        const NBT::Value& GetHeightmaps() const
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
            heightmaps = ReadData<NBT::Value>(iter, length);
            buffer = ReadVector<unsigned char>(iter, length);
            block_entities_data = ReadVector<BlockEntityInfo>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<NBT::Value>(heightmaps, container);
            WriteVector<unsigned char>(buffer, container);
            WriteVector<BlockEntityInfo>(block_entities_data, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["heightmaps"] = heightmaps.Serialize();
            output["buffer"] = "Vector of " + std::to_string(buffer.size()) + " unsigned char";
            output["block_entities_data"] = block_entities_data;

            return output;
        }

    private:
        NBT::Value heightmaps;
        std::vector<unsigned char> buffer;
        std::vector<BlockEntityInfo> block_entities_data;
    };
}
#endif
