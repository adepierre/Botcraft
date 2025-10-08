#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataGameEventListenerInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(ListenerRadius, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
