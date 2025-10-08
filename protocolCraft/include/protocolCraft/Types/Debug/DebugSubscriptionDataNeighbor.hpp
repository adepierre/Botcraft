#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataNeighbor : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Pos, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
