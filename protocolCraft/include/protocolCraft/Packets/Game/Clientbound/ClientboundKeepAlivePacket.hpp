#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundKeepAlivePacket : public BasePacket<ClientboundKeepAlivePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Keep Alive";

#if PROTOCOL_VERSION < 340 /* < 1.12.2 */
        SERIALIZED_FIELD(Id_, VarInt);
#else
        SERIALIZED_FIELD(Id_, long long int);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
