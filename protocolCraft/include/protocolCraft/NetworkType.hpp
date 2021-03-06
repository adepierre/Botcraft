#pragma once

#include <vector>

#include <picojson/picojson.h>

#include "protocolCraft/BinaryReadWrite.hpp"

namespace ProtocolCraft
{
    class NetworkType
    {
    public:
        virtual ~NetworkType()
        {

        }

        virtual void Read(ReadIterator &iter, size_t &length)
        {
            return ReadImpl(iter, length);
        }

        virtual void Write(WriteContainer &container) const
        {
            return WriteImpl(container);
        }

        virtual const picojson::value Serialize() const
        {
            return SerializeImpl();
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) = 0;
        virtual void WriteImpl(WriteContainer &container) const = 0;
        virtual const picojson::value SerializeImpl() const = 0;
    };
} // ProtocolCraft