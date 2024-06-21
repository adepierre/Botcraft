#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStartConfigurationPacket : public BaseMessage<ClientboundStartConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Start Configuration";

        DECLARE_EMPTY;
    };
} //ProtocolCraft
#endif
