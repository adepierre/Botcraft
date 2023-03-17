#pragma once

#if PROTOCOL_VERSION > 761
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ChunkBiomeData : public NetworkType
    {
    public:
        virtual ~ChunkBiomeData() override
        {

        }

        void SetZ(const int z_)
        {
            z = z_;
        }

        void SetX(const int x_)
        {
            x = x_;
        }

        void SetBuffer(const std::vector<unsigned char>& buffer_)
        {
            buffer = buffer_;
        }


        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }

        const std::vector<unsigned char>& GetBuffer() const
        {
            return buffer;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            const long long int xz = ReadData<long long int>(iter, length);
            x = static_cast<int>(xz & 0xFFFFFFFFL);
            z = static_cast<int>((xz >> 32) & 0xFFFFFFFFL);
            buffer = ReadVector<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            const long long int xz = (static_cast<long long int>(x) & 0xFFFFFFFFL) | ((static_cast<long long int>(z) & 0xFFFFFFFFL) << 32);
            WriteData<long long int>(xz, container);
            WriteVector<unsigned char>(buffer, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["z"] = z;
            output["buffer"] = "Vector of " + std::to_string(buffer.size()) + " unsigned char";

            return output;
        }

    private:
        int x;
        int z;
        std::vector<unsigned char> buffer;
    };
}
#endif
