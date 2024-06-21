#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundDamageEventPacket : public BaseMessage<ClientboundDamageEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Damage Event";

        DECLARE_FIELDS(
            (VarInt,   VarInt,       VarInt,        VarInt,         std::optional<std::array<double, 3>>),
            (EntityId, SourceTypeId, SourceCauseId, SourceDirectId, SourcePosition)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(SourceTypeId);
        GETTER_SETTER(SourceCauseId);
        GETTER_SETTER(SourceDirectId);
        GETTER_SETTER(SourcePosition);
    };
} //ProtocolCraft
#endif
