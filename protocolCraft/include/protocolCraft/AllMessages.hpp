#pragma once

#include "protocolCraft/Utilities/Templates.hpp"
#include "protocolCraft/AllClientboundMessages.hpp"
#include "protocolCraft/AllServerboundMessages.hpp"

namespace ProtocolCraft
{
    using AllMessages = Internal::tuple_cat_t<
        AllClientboundMessages,
        AllServerboundMessages
    >;
} //ProtocolCraft
