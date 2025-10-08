#if PROTOCOL_VERSION > 765 /* > 1.20.4 */ && PROTOCOL_VERSION < 773 /* < 1.21.9 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundDebugSampleSubscriptionPacket : public BasePacket<ServerboundDebugSampleSubscriptionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Debug Sample Subscription";

        SERIALIZED_FIELD(SampleType, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
