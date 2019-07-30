#pragma once

#include <vector>
#include "botcraft/Network/BinaryReadWrite.hpp"

namespace Botcraft
{
    class NetworkType
    {
    public:
        virtual void Read(ReadIterator &iter, size_t &length)
        {
            return ReadImpl(iter, length);
        }

        virtual void Write(WriteContainer &container) const
        {
            return WriteImpl(container);
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) = 0;
        virtual void WriteImpl(WriteContainer &container) const = 0;
    };
} // Botcraft