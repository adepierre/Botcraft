#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundDamageEventPacket : public BaseMessage<ClientboundDamageEventPacket>
    {
    public:
#if   PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x1A;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Damage Event";

        DECLARE_FIELDS_TYPES(VarInt,   VarInt,       VarInt,        VarInt,         std::optional<std::array<double, 3>>);
        DECLARE_FIELDS_NAMES(EntityId, SourceTypeId, SourceCauseId, SourceDirectId, SourcePosition);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(SourceTypeId);
        GETTER_SETTER(SourceCauseId);
        GETTER_SETTER(SourceDirectId);
        GETTER_SETTER(SourcePosition);
    };
} //ProtocolCraft
#endif
