#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 756 /* < 1.17.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveEntityPacket : public BaseMessage<ClientboundRemoveEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */
        static constexpr int packet_id = 0x3A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Remove Entity";

        DECLARE_FIELDS(
            (VarInt),
            (EntityId)
        );
        DECLARE_READ_WRITE_SERIALIZE(EntityId);

        GETTER_SETTER(EntityId);
    };
} //ProtocolCraft
#endif
