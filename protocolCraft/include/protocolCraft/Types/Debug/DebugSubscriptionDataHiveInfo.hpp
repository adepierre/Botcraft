#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataHiveInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD(OccupantCount, VarInt);
        SERIALIZED_FIELD(HoneyLevel, VarInt);
        SERIALIZED_FIELD(Sedated, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
