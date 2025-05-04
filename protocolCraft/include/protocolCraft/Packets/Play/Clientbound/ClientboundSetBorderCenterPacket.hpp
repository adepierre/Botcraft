#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderCenterPacket : public BasePacket<ClientboundSetBorderCenterPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Border Center";

        SERIALIZED_FIELD(NewCenterX, double);
        SERIALIZED_FIELD(NewCenterZ, double);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
