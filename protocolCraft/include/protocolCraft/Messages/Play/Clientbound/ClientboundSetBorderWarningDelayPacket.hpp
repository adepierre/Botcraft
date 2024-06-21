#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDelayPacket : public BaseMessage<ClientboundSetBorderWarningDelayPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Border Warning Delay";

        DECLARE_FIELDS(
            (VarInt),
            (WarningDelay)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(WarningDelay);
    };
} //ProtocolCraft
#endif
