#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ChunkPos : public NetworkType
    {
        DECLARE_FIELDS_TYPES(int, int);
        DECLARE_FIELDS_NAMES(X,   Z);
        DECLARE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Z);

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const long long int xz = ReadData<long long int>(iter, length);
            SetX(static_cast<int>(xz & 0xFFFFFFFFL));
            SetZ(static_cast<int>((xz >> 32) & 0xFFFFFFFFL));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            const long long int xz = (static_cast<long long int>(GetX()) & 0xFFFFFFFFL) | ((static_cast<long long int>(GetZ()) & 0xFFFFFFFFL) << 32);
            WriteData<long long int>(xz, container);
        }
    };
}
#endif
