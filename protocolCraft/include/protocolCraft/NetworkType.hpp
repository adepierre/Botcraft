#pragma once

#include <vector>

#include "protocolCraft/BinaryReadWrite.hpp"
#include "protocolCraft/Utilities/Json.hpp"

namespace ProtocolCraft
{
    class NetworkType
    {
    public:
        virtual ~NetworkType()
        {

        }

        virtual void Read(ReadIterator& iter, size_t& length)
        {
            return ReadImpl(iter, length);
        }

        virtual void Write(WriteContainer& container) const
        {
            return WriteImpl(container);
        }

        virtual Json::Value Serialize() const
        {
            return SerializeImpl();
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) = 0;
        virtual void WriteImpl(WriteContainer& container) const = 0;
        virtual Json::Value SerializeImpl() const = 0;
    };
} // ProtocolCraft
