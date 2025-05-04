#pragma once

#include <memory>

#include "protocolCraft/enums.hpp"

namespace ProtocolCraft
{
    class Packet;

    std::shared_ptr<Packet> CreateClientboundPacket(const ConnectionState state, const int id);
    std::shared_ptr<Packet> CreateServerboundPacket(const ConnectionState state, const int id);
} //ProtocolCraft
