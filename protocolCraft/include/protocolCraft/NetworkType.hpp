#pragma once

#include <vector>

#include <nlohmann/json.hpp>

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

        virtual const nlohmann::json Serialize() const
        {
            return SerializeImpl();
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) = 0;
        virtual void WriteImpl(WriteContainer &container) const = 0;
        virtual const nlohmann::json SerializeImpl() const = 0;
    };
} // ProtocolCraft
