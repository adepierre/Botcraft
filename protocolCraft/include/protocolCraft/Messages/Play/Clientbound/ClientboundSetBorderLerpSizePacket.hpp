#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderLerpSizePacket : public BaseMessage<ClientboundSetBorderLerpSizePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Border Lerp Size";

        DECLARE_FIELDS(
            (double, double, VarLong),
            (OldSize, NewSize, LerpTime)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(OldSize);
        GETTER_SETTER(NewSize);
        GETTER_SETTER(LerpTime);
    };
} //ProtocolCraft
#endif
