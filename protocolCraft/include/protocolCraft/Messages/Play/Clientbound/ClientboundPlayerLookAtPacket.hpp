#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Face Player";

        DEFINE_CONDITION(HasEntity, GetAtEntity());

        SERIALIZED_FIELD(FromAnchor, VarInt);
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(AtEntity, bool);
        SERIALIZED_FIELD(Entity, Internal::Conditioned<VarInt, &THIS::HasEntity>);
        SERIALIZED_FIELD(ToAnchor, Internal::Conditioned<VarInt, &THIS::HasEntity>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
