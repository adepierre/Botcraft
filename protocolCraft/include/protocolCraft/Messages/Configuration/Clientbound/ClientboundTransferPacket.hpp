#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <string>

namespace ProtocolCraft
{
    class ClientboundTransferConfigurationPacket : public BaseMessage<ClientboundTransferConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Transfer (Configuration)";

        DECLARE_FIELDS(
            (std::string, VarInt),
            (Host,        Port)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Host);
        GETTER_SETTER(Port);
    };
}
#endif
