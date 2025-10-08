#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Debug/DebugSubscription.hpp"

namespace ProtocolCraft
{
    class ClientboundDebugEventPacket : public BasePacket<ClientboundDebugEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Event";

        SERIALIZED_FIELD(Event, DebugSubscriptionEvent);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
