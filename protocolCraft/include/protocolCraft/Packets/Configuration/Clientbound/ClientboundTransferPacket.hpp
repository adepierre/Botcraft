#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include <string>

namespace ProtocolCraft
{
    class ClientboundTransferConfigurationPacket : public BasePacket<ClientboundTransferConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Transfer (Configuration)";

        SERIALIZED_FIELD(Host, std::string);
        SERIALIZED_FIELD(Port, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
