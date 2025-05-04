#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/ClientInformation.hpp"

namespace ProtocolCraft
{
    class ServerboundClientInformationConfigurationPacket : public BasePacket<ServerboundClientInformationConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Client Information (Configuration)";

        SERIALIZED_FIELD(ClientInformation, ProtocolCraft::ClientInformation);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
