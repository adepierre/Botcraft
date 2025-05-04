#pragma once

#include "protocolCraft/GenericHandler.hpp"
#include "protocolCraft/Packet.hpp"
#include "protocolCraft/AllPackets.hpp"

namespace ProtocolCraft
{
    class Handler : public GenericHandler<Packet, AllPackets> {};
} //ProtocolCraft
