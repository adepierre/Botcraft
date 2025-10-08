#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class LpVec3 : public NetworkType
    {
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);

        DEFINE_UTILITIES;
        DECLARE_SERIALIZE;

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            const short s = ReadData<short, unsigned char>(iter, length);
            if (s == 0)
            {
                X = 0.0;
                Y = 0.0;
                Z = 0.0;
                return;
            }
            const short s2 = ReadData<short, unsigned char>(iter, length);
            const long long int l = ReadData<long long int, unsigned int>(iter, length);
            const long long int l2 = (l << 16) | (static_cast<long long int>(s2) << 8) | static_cast<long long int>(s);
            long long int l3 = s & 0b11;
            if ((s & 0b100) == 4)
            {
                l3 |= (ReadData<long long int, VarInt>(iter, length) & 0xFFFFFFFFL) << 2;
            }
            auto unpack = [](const long long int l) { return std::min(static_cast<double>(l & 0x7FFFL), 32766.0) * 2.0 / 32766.0 - 1.0; };
            X = unpack(l2 >> 3) * l3;
            Y = unpack(l2 >> 18) * l3;
            Z = unpack(l2 >> 33) * l3;
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            auto sanitize = [](const double d) { return std::isnan(d) ? 0.0 : std::clamp(d, -1.7179869183E10, 1.7179869183E10); };
            const double d3 = sanitize(X);
            const double d2 = sanitize(Y);
            const double d = sanitize(Z);

            const double max = std::max(std::abs(d3), std::max(std::abs(d2), std::abs(d)));
            if (max < 3.051944088384301E-5)
            {
                WriteData<unsigned char>(0, container);
                return;
            }

            const long long int l = static_cast<long long int>(std::ceil(max));
            const bool has_extra_data = (l & 0b11) != l;
            const long long int l2 = has_extra_data ? (l & 0b11L) | 0b100L : l;
            auto pack = [](const double d) { return static_cast<long long int>(std::round((d * 0.5 + 0.5) * 32766.0)); };
            const long long int l3 = pack(d3 / l) << 3;
            const long long int l4 = pack(d2 / l) << 18;
            const long long int l5 = pack(d / l) << 33;
            const long long int l6 = l2 | l3 | l4 | l5;
            WriteData<long long int, unsigned char>(l6, container);
            WriteData<long long int, unsigned char>(l6 >> 8, container);
            WriteData<long long int, unsigned int>(l6 >> 16, container);
            if (has_extra_data)
            {
                WriteData<long long int, VarInt>(l >> 2, container);
            }
        }
    };
}
#endif
