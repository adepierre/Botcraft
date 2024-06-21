#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundDebugSampleSubscriptionPacket : public BaseMessage<ServerboundDebugSampleSubscriptionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Debug Sample Subscription";

        DECLARE_FIELDS(
            (VarInt),
            (SampleType)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SampleType);
    };
} // ProtocolCraft
#endif
