#pragma once

#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ChunkPos : public NetworkType
    {
    public:
        virtual ~ChunkPos() override
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


        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const long long int xz = ReadData<long long int>(iter, length);
            x = static_cast<int>(xz & 0xFFFFFFFFL);
            z = static_cast<int>((xz >> 32) & 0xFFFFFFFFL);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            const long long int xz = (static_cast<long long int>(x) & 0xFFFFFFFFL) | ((static_cast<long long int>(z) & 0xFFFFFFFFL) << 32);
            WriteData<long long int>(xz, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["z"] = z;

            return output;
        }

    private:
        int x = 0;
        int z = 0;
    };
}
#endif
