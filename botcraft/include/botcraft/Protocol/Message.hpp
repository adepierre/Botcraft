#pragma once

#include <vector>

#include "botcraft/Protocol/Type.hpp"

namespace Botcraft
{
    class Handler;

    class Message : public Type
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