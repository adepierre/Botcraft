#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundResourcePackPopConfigurationPacket : public BaseMessage<ClientboundResourcePackPopConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x08;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Resource Pack Pop (Configuration)";

        DECLARE_FIELDS_TYPES(UUID);
        DECLARE_FIELDS_NAMES(Uuid);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Uuid);
    };
} //ProtocolCraft
#endif
