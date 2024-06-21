#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/ServerLinksUnstrustedEntry.hpp"

namespace ProtocolCraft
{
    class ClientboundServerLinksPacket : public BaseMessage<ClientboundServerLinksPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Server Links";

        DECLARE_FIELDS(
            (std::vector<ServerLinksUnstrustedEntry>),
            (Links)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Links);
    };
} //ProtocolCraft
#endif
