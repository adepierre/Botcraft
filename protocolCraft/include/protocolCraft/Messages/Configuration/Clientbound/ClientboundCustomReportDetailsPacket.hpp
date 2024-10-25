#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomReportDetailsConfigurationPacket : public BaseMessage<ClientboundCustomReportDetailsConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Report Details (Configuration)";

        SERIALIZED_FIELD(Details, std::map<std::string, std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
