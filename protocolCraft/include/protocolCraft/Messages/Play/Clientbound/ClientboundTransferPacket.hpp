#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <string>

namespace ProtocolCraft
{
    class ClientboundTransferPacket : public BaseMessage<ClientboundTransferPacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x73;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Transfer";

        DECLARE_FIELDS_TYPES(std::string, VarInt);
        DECLARE_FIELDS_NAMES(Host,        Port);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Host);
        GETTER_SETTER(Port);
    };
}
#endif
