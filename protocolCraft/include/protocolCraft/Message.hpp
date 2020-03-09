#pragma once

#include <vector>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Handler;

    class Message : public NetworkType
    {
    public:
        virtual void Write(WriteContainer &container) const override
        {
            WriteVarInt(GetId(), container);
            return WriteImpl(container);
        }

        void Dispatch(Handler *handler)
        {
            return DispatchImpl(handler);
        }

        virtual const int GetId() const = 0;

        virtual const std::string GetName() const = 0;

    protected:
        virtual void DispatchImpl(Handler *handler) = 0;
    };
} // Botcraft