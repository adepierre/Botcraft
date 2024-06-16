#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopPacket : public BaseMessage<ClientboundResourcePackPopPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x45;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ressource Pack Pop";

        DECLARE_FIELDS_TYPES(std::optional<UUID>);
        DECLARE_FIELDS_NAMES(Uuid);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
    };
} //ProtocolCraft
#endif
