#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <string>

namespace ProtocolCraft
{
    class ClientboundTransferConfigurationPacket : public BaseMessage<ClientboundTransferConfigurationPacket>
    {
    public:
        static constexpr int packet_id = 0x05;
        static constexpr std::string_view packet_name = "Transfer (Configuration)";

        DECLARE_FIELDS_TYPES(std::string, VarInt);
        DECLARE_FIELDS_NAMES(Host,        Port);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Host);
        GETTER_SETTER(Port);
    };
}
#endif
