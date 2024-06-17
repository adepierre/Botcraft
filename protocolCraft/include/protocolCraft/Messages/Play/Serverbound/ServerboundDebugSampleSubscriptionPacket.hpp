#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundDebugSampleSubscriptionPacket : public BaseMessage<ServerboundDebugSampleSubscriptionPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x13;
#else
#error "Protocol version not implemented"
#endif

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
