#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPingConfigurationPacket : public BaseMessage<ClientboundPingConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ping (Configuration)";

        SERIALIZED_FIELD(Id_, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
