#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestPacket : public BasePacket<ServerboundPingRequestPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ping Request";

        SERIALIZED_FIELD(Time, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
