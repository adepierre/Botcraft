#pragma once

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/ChunkPos.hpp"

namespace ProtocolCraft
{
    class ChunkBiomeData : public NetworkType
    {
    public:
        virtual ~ChunkBiomeData() override
        {

        }

        void SetPos(const ChunkPos& pos_)
        {
            pos = pos_;
        }

        void SetBuffer(const std::vector<unsigned char>& buffer_)
        {
            buffer = buffer_;
        }


        const ChunkPos& GetPos() const
        {
            return pos;
        }

        const std::vector<unsigned char>& GetBuffer() const
        {
            return buffer;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos = ReadData<ChunkPos>(iter, length);
            buffer = ReadData<std::vector<unsigned char>>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<ChunkPos>(pos, container);
            WriteData<std::vector<unsigned char>>(buffer, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["pos"] = pos;
            output["buffer"] = "Vector of " + std::to_string(buffer.size()) + " unsigned char";

            return output;
        }

    private:
        ChunkPos pos;
        std::vector<unsigned char> buffer;
    };
}
#endif
