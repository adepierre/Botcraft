#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundRemoveMobEffectPacket : public BasePacket<ClientboundRemoveMobEffectPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Remove Mob Effect";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 758 /* < 1.18.2 */
        SERIALIZED_FIELD(Effect, char);
#else
        SERIALIZED_FIELD(Effect, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
