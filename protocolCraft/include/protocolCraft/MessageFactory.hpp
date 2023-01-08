#pragma once

#include <memory>

#include "protocolCraft/enums.hpp"

namespace ProtocolCraft
{
    class Message;

    std::shared_ptr<Message> CreateClientboundMessage(const ConnectionState state, const int id);
    std::shared_ptr<Message> CreateServerboundMessage(const ConnectionState state, const int id);
} //ProtocolCraft
