#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopConfigurationPacket : public BasePacket<ClientboundResourcePackPopConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Resource Pack Pop (Configuration)";

        SERIALIZED_FIELD(Uuid, UUID);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
