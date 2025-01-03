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

        virtual int GetId() const override;
        virtual std::string_view GetName() const override { return TDerived::packet_name; }
#ifdef PROTOCOLCRAFT_DETAILED_PARSING
        virtual std::shared_ptr<Message> CopyTypeOnly() const override { return std::make_shared<TDerived>(); }
#endif

    protected:
        // We can't have definition in hpp file as Handler is still an incomplete class at this point
        virtual void DispatchImpl(Handler* handler) override;

        // Convenience to access "current" class when implementing TDerived
        using THIS = TDerived;
    };
}
