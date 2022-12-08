#if PROTOCOL_VERSION > 760
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <bitset>

namespace ProtocolCraft
{
    // We need this wrapper because we can't create partially specialized function
    // template<N>
    // ReadData<std::bitset<N>>
    template<size_t N>
    class Bitset : public NetworkType
    {
    public:
        virtual ~Bitset() override
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            bitset.reset();
            const std::vector<unsigned char> bytes = ReadByteArray(iter, length, N / 8 + (N % 8 != 0));
            for (size_t i = 0; i < N; ++i)
            {
                bitset.set(i, (bytes[i / 8] << (i % 8)) & 0x01);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::vector<unsigned char> bytes(N / 8 + (N % 8 != 0), 0);
            for (size_t i = 0; i < N; ++i)
            {
                if (bitset[i])
                {
                    bytes[i / 8] |= 1 << (i % 8);
                }
            }
            WriteByteArray(bytes, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            return bitset.to_string();
        }

    public:
        std::bitset<N> bitset;
    };
} // ProtocolCraft
#endif
