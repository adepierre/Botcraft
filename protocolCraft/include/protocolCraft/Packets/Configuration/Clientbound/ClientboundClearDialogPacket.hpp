#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundClearDialogConfigurationPacket : public BasePacket<ClientboundClearDialogConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Clear Dialog (Configuration)";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
