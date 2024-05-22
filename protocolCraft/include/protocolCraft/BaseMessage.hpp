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

        virtual int GetId() const override { return TDerived::packet_id; }
        virtual std::string_view GetName() const override { return TDerived::packet_name; }
        virtual std::shared_ptr<Message> Clone() const override { return std::make_shared<TDerived>(*reinterpret_cast<const TDerived*>(this)); }
    protected:
        // We can't have definition in hpp file as Handler is still an incomplete class at this point
        virtual void DispatchImpl(Handler* handler) override;
    };
}
