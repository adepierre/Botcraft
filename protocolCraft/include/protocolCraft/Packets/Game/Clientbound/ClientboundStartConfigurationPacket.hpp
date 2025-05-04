#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundStartConfigurationPacket : public BasePacket<ClientboundStartConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Start Configuration";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
