#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomReportDetailsConfigurationPacket : public BaseMessage<ClientboundCustomReportDetailsConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x0F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Custom Report Details (Configuration)";

        DECLARE_FIELDS_TYPES(std::map<std::string, std::string>);
        DECLARE_FIELDS_NAMES(Details);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Details);
    };
} //ProtocolCraft
#endif
