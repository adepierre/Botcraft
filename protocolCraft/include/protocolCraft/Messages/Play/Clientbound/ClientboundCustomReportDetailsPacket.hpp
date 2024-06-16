#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomReportDetailsPacket : public BaseMessage<ClientboundCustomReportDetailsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x7A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Custom Report Details";

        DECLARE_FIELDS(
            (std::map<std::string, std::string>),
            (Details)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Details);
    };
} //ProtocolCraft
#endif
