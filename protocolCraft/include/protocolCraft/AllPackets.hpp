#pragma once

#include "protocolCraft/Utilities/Templates.hpp"
#include "protocolCraft/AllClientboundPackets.hpp"
#include "protocolCraft/AllServerboundPackets.hpp"

namespace ProtocolCraft
{
    using AllPackets = Internal::tuple_cat_t<
        AllClientboundPackets,
        AllServerboundPackets
    >;
} //ProtocolCraft
