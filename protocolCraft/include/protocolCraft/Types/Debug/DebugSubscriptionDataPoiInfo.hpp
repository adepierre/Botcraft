#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class DebugSubscriptionDataPoiInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(PoiType, VarInt);
        SERIALIZED_FIELD(FreeTicketCount, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
