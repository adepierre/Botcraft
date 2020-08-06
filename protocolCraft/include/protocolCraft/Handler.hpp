#pragma once

#include "protocolCraft/GenericHandler.hpp"
#include "protocolCraft/Message.hpp"
#include "protocolCraft/AllMessages.hpp"

namespace ProtocolCraft
{
    class Handler : public GenericHandler<Message, AllMessages> {};
} //ProtocolCraft