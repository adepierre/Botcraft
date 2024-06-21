#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddEntityPacket : public BaseMessage<ClientboundAddEntityPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Entity";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (VarInt, UUID, char, double, double, double, unsigned char, unsigned char, int,  short, short, short),
            (Id_,    Uuid, Type, X,      Y,      Z,      XRot,          YRot,          Data, Xa,    Ya,    Za)
        );
#elif PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, double, double, double, unsigned char, unsigned char, int,  short, short, short),
            (Id_,    Uuid, Type,   X,      Y,      Z,      XRot,          YRot,          Data, Xa,    Ya,    Za)
        );
#else
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, double, double, double, unsigned char, unsigned char, unsigned char,    VarInt, short, short, short),
            (Id_,    Uuid, Type,   X,      Y,      Z,      XRot,          YRot,          YHeadRot, Data,   Xa,    Ya,    Za)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Uuid);
        GETTER_SETTER(Type);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(XRot);
        GETTER_SETTER(YRot);
        GETTER_SETTER(Data);
        GETTER_SETTER(Xa);
        GETTER_SETTER(Ya);
        GETTER_SETTER(Za);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(YHeadRot);
#endif
    };
} //ProtocolCraft
