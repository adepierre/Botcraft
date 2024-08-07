#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/ClientInformation.hpp"

namespace ProtocolCraft
{
    class ServerboundClientInformationConfigurationPacket : public BaseMessage<ServerboundClientInformationConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Client Information (Configuration)";

        DECLARE_FIELDS(
            (ClientInformation),
            (ClientInformation)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ClientInformation);
    };
} //ProtocolCraft
#endif
