#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/ServerLinksUnstrustedEntry.hpp"

namespace ProtocolCraft
{
    class ClientboundServerLinksConfigurationPacket : public BaseMessage<ClientboundServerLinksConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x10;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Server Links (Configuration)";

        DECLARE_FIELDS_TYPES(std::vector<ServerLinksUnstrustedEntry>);
        DECLARE_FIELDS_NAMES(Links);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Links);
    };
} // ProtocolCraft
#endif
