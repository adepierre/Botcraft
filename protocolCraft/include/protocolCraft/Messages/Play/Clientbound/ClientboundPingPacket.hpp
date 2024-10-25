#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPingPacket : public BaseMessage<ClientboundPingPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ping";

        SERIALIZED_FIELD(Id_, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
