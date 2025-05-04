#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundDamageEventPacket : public BasePacket<ClientboundDamageEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Damage Event";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(SourceTypeId, VarInt);
        SERIALIZED_FIELD(SourceCauseId, VarInt);
        SERIALIZED_FIELD(SourceDirectId, VarInt);
        SERIALIZED_FIELD(SourcePosition, std::optional<std::array<double, 3>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
