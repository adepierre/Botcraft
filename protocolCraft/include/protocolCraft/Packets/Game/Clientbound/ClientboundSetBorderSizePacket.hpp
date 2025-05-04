#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderSizePacket : public BasePacket<ClientboundSetBorderSizePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Border Size";

        SERIALIZED_FIELD(Size, double);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
