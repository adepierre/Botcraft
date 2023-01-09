#pragma once

#include <string>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class NetworkPosition : public NetworkType
    {
    public:
        virtual ~NetworkPosition() override
        {

        }

        void SetX(const int x_)
        {
            x = x_;
        }

        void SetY(const int y_)
        {
            y = y_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }

        int GetX() const
        {
            return x;
        }

        int GetY() const
        {
            return y;
        }

        int GetZ() const
        {
            return z;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const unsigned long long int value = ReadData<unsigned long long int>(iter, length);

            x = value >> 38;
            if (x >= 33554432)
            {
                x -= 67108864;
            }

#if PROTOCOL_VERSION < 442
            y = (value >> 26) & 0xFFF;
            if (y >= 2048)
            {
                y -= 4096;
            }
            z = value << 38 >> 38;
            if (z >= 33554432)
            {
                z -= 67108864;
            }
#else
            y = value & 0xFFF;
            if (y >= 2048)
            {
                y -= 4096;
            }

            z = value << 26 >> 38;
            if (z >= 33554432)
            {
                z -= 67108864;
            }
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

#if PROTOCOL_VERSION < 442
            const unsigned long long int value = (((long long int)x & 0x3FFFFFF) << 38) | (((long long int)y & 0xFFF) << 26) | ((long long int)z & 0x3FFFFFF);
#else
            const unsigned long long int value = (((long long int)x & 0x3FFFFFF) << 38) | (((long long int)z & 0x3FFFFFF) << 12) | ((long long int)y & 0xFFF);
#endif
            WriteData<unsigned long long int>(value, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["x"] = x;
            output["y"] = y;
            output["z"] = z;

            return output;
        }

    private:
        int x;
        int y;
        int z;
    };
}
