#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/Types/Debug/DebugSubscriptionData.hpp"

#include "protocolCraft/Types/NetworkPosition.hpp"

#include <optional>

namespace ProtocolCraft
{
    class DebugSubscriptionDataBreezeInfo : public DebugSubscriptionData
    {
        SERIALIZED_FIELD(AttackTarget, std::optional<VarInt>);
        SERIALIZED_FIELD(jumpTarget, std::optional<NetworkPosition>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
