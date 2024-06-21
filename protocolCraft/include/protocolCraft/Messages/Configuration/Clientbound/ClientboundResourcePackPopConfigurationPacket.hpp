#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopConfigurationPacket : public BaseMessage<ClientboundResourcePackPopConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Resource Pack Pop (Configuration)";

        DECLARE_FIELDS(
            (UUID),
            (Uuid)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
    };
} //ProtocolCraft
#endif
