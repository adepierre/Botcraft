#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomReportDetailsPacket : public BasePacket<ClientboundCustomReportDetailsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Report Details";

        SERIALIZED_FIELD(Details, std::map<std::string, std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
