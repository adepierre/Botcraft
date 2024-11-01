#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <array>

namespace ProtocolCraft
{
    class MinecartBehaviorMinecartStep : public NetworkType
    {
        SERIALIZED_FIELD(Position, std::array<double, 3>);
        SERIALIZED_FIELD(Movement, std::array<double, 3>);
        SERIALIZED_FIELD(YRot, char);
        SERIALIZED_FIELD(XRot, char);
        SERIALIZED_FIELD(weight, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
