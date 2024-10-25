#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopConfigurationPacket : public BaseMessage<ClientboundResourcePackPopConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Resource Pack Pop (Configuration)";

        SERIALIZED_FIELD(Uuid, UUID);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
