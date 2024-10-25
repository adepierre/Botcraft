#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResetChatPacket : public BaseMessage<ClientboundResetChatPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Reset Chat";

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
