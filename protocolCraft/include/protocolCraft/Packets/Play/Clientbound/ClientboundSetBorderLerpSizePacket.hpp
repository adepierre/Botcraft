#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderLerpSizePacket : public BasePacket<ClientboundSetBorderLerpSizePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Border Lerp Size";

        SERIALIZED_FIELD(OldSize, double);
        SERIALIZED_FIELD(NewSize, double);
        SERIALIZED_FIELD(LerpTime, VarLong);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
