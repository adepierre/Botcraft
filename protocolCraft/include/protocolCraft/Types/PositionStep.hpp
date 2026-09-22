#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <array>

namespace ProtocolCraft
{
    class PositionStep : public NetworkType
    {

        SERIALIZED_FIELD(Position, std::array<double, 3>);
        SERIALIZED_FIELD(TickOffset, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
