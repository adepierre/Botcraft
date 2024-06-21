#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundKeepAliveConfigurationPacket : public BaseMessage<ClientboundKeepAliveConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Keep Alive (Configuration)";

        DECLARE_FIELDS(
            (long long int),
            (Id_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
    };
} //ProtocolCraft
#endif
