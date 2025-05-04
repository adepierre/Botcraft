#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Identifier.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundCooldownPacket : public BasePacket<ClientboundCooldownPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cooldown";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Item, VarInt);
#else
        SERIALIZED_FIELD(CooldownGroup, Identifier);
#endif
        SERIALIZED_FIELD(Duration, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
