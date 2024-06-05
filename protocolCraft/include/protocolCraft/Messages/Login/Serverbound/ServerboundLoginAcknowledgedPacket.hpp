#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundLoginAcknowledgedPacket : public BaseMessage<ServerboundLoginAcknowledgedPacket>
    {
    public:
        static constexpr int packet_id = 0x03;
        static constexpr std::string_view packet_name = "Login Acknowledged";

        DECLARE_EMPTY;
    };
} // ProtocolCraft
#endif
