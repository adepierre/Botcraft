#pragma once
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Handler.hpp"

namespace ProtocolCraft
{
    template <typename TDerived>
    void BaseMessage<TDerived>::DispatchImpl(Handler* handler)
    {
        handler->Handle(static_cast<TDerived&>(*this));
    }
}
