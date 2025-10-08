#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataGameEventInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Event, VarInt);
        SERIALIZED_FIELD(Pos, std::array<double, 3>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
