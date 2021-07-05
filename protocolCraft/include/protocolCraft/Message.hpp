#pragma once

#include <vector>
#include <memory>

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class Handler;

    class Message : public NetworkType
    {
    public:
        virtual ~Message()
        {

        }

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

        virtual const std::shared_ptr<Message> Clone() const = 0;

    protected:
        virtual void DispatchImpl(Handler *handler) = 0;
    };
} // Botcraft