#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPingConfigurationPacket : public BaseMessage<ClientboundPingConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Ping (Configuration)";

        DECLARE_FIELDS(
            (int),
            (Id_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
    };
} //ProtocolCraft
#endif
