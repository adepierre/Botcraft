#if PROTOCOL_VERSION > 351 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerLookAtPacket : public BaseMessage<ClientboundPlayerLookAtPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Face Player";

        DECLARE_CONDITION(HasEntity, GetAtEntity());

        DECLARE_FIELDS(
            (VarInt,     double, double, double, bool,     Internal::Conditioned<VarInt, &THIS::HasEntity>, Internal::Conditioned<VarInt, &THIS::HasEntity>),
            (FromAnchor, X,      Y,      Z,      AtEntity, Entity,                                          ToAnchor)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(FromAnchor);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(AtEntity);
        GETTER_SETTER(Entity);
        GETTER_SETTER(ToAnchor);
    };
} //ProtocolCraft
#endif
