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
        virtual const std::shared_ptr<Message> Clone() const override
        {
            return std::shared_ptr<TDerived>(new TDerived(static_cast<const TDerived&>(*this)));
        }
    protected:
        virtual void DispatchImpl(Handler* handler) override;
    };
}