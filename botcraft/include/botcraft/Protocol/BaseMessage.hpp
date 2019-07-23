#pragma once

#include "botcraft/Protocol/Message.hpp"

namespace Botcraft
{
    class Handler;

    template<typename TDerived>
    class BaseMessage : public Message
    {
    protected:
        virtual void DispatchImpl(Handler *handler) override
        {
            handler->Handle(static_cast<TDerived&>(*this));
        }
    };
}