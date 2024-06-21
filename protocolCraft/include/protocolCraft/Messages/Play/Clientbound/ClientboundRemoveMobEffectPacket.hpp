#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveMobEffectPacket : public BaseMessage<ClientboundRemoveMobEffectPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Remove Mob Effect";

#if PROTOCOL_VERSION < 758 /* < 1.18.2 */
        DECLARE_FIELDS(
            (VarInt,   char),
            (EntityId, Effect)
        );
#else
        DECLARE_FIELDS(
            (VarInt,   VarInt),
            (EntityId, Effect)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(Effect);
    };
} //ProtocolCraft
