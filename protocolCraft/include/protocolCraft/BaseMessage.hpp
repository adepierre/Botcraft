#pragma once

#include "protocolCraft/Message.hpp"

namespace ProtocolCraft
{
    class Handler;

    template<typename TDerived>
    class BaseMessage : public Message
    {
    public:
        virtual ~BaseMessage() override {};
    protected:
        virtual void DispatchImpl(Handler* handler) override;
    };
}