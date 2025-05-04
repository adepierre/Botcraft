#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDelayPacket : public BasePacket<ClientboundSetBorderWarningDelayPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Border Warning Delay";

        SERIALIZED_FIELD(WarningDelay, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
