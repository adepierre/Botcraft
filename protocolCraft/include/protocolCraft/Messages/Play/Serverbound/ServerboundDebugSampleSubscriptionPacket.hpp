#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundDebugSampleSubscriptionPacket : public BaseMessage<ServerboundDebugSampleSubscriptionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Sample Subscription";

        SERIALIZED_FIELD(SampleType, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
