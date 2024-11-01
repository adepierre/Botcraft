#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <array>

namespace ProtocolCraft
{
    class PositionMoveRotation : public NetworkType
    {
        SERIALIZED_FIELD(Position, std::array<double, 3>);
        SERIALIZED_FIELD(DeltaMovement, std::array<double, 3>);
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
