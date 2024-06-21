#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopPacket : public BaseMessage<ClientboundResourcePackPopPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Ressource Pack Pop";

        DECLARE_FIELDS(
            (std::optional<UUID>),
            (Uuid)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
    };
} //ProtocolCraft
#endif
