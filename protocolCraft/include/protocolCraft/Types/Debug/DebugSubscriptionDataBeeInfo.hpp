#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

#include "protocolCraft/Types/NetworkPosition.hpp"

#include <optional>

namespace ProtocolCraft
{
    class DebugSubscriptionDataBeeInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(HivePos, std::optional<NetworkPosition>);
        SERIALIZED_FIELD(FlowerPos, std::optional<NetworkPosition>);
        SERIALIZED_FIELD(TravelTicks, VarInt);
        SERIALIZED_FIELD(BlacklistedHives, std::vector<NetworkPosition>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
