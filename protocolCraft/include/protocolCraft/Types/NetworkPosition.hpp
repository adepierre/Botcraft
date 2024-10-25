#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class NetworkPosition : public NetworkType
    {
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Y, int);
        SERIALIZED_FIELD(Z, int);

        DEFINE_UTILITIES;
        DECLARE_SERIALIZE;

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const unsigned long long int value = ReadData<unsigned long long int>(iter, length);

            const int x = value >> 38;
            SetX(x >= 33554432 ? (x - 67108864) : x);

#if PROTOCOL_VERSION < 442 /* < 1.14 */
            const int y = (value >> 26) & 0xFFF;
            const int z = value << 38 >> 38;
#else
            const int y = value & 0xFFF;
            const int z = value << 26 >> 38;
#endif
            SetY(y >= 2048 ? (y - 4096) : y);
            SetZ(z >= 33554432 ? (z - 67108864) : z);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {

#if PROTOCOL_VERSION < 442 /* < 1.14 */
            const unsigned long long int value = (((long long int)GetX() & 0x3FFFFFF) << 38) | (((long long int)GetY() & 0xFFF) << 26) | ((long long int)GetZ() & 0x3FFFFFF);
#else
            const unsigned long long int value = (((long long int)GetX() & 0x3FFFFFF) << 38) | (((long long int)GetZ() & 0x3FFFFFF) << 12) | ((long long int)GetY() & 0xFFF);
#endif
            WriteData<unsigned long long int>(value, container);
        }
    };
}
