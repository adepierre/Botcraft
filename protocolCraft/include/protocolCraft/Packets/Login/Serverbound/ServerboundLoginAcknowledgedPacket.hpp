#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundLoginAcknowledgedPacket : public BasePacket<ServerboundLoginAcknowledgedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Login Acknowledged";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
