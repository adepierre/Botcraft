#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundDebugSubscriptionRequestPacket : public BasePacket<ServerboundDebugSubscriptionRequestPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Subscription Request";

        SERIALIZED_FIELD(Subscriptions, std::vector<VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
