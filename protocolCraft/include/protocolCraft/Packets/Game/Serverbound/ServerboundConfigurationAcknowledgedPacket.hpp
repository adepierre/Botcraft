#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundConfigurationAcknowledgedPacket : public BasePacket<ServerboundConfigurationAcknowledgedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Configuration Acknowledged";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
