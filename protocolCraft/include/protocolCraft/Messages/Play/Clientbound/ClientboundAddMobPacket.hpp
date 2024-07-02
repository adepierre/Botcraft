#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddMobPacket : public BaseMessage<ClientboundAddMobPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Mob";

#if PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, double, double, double, unsigned char, unsigned char, unsigned char,    short, short, short, Internal::Vector<unsigned char, void, 0>),
            (Id_,    Uuid, Type,   X,      Y,      Z,      YRot,          XRot,                  YHeadRot, Xd,    Yd,    Zd,    RawMetadata)
        );
#else
        DECLARE_FIELDS(
            (VarInt, UUID, VarInt, double, double, double, unsigned char, unsigned char, unsigned char,    short, short, short),
            (Id_,    Uuid, Type,   X,      Y,      Z,      YRot,          XRot,                  YHeadRot, Xd,    Yd,    Zd)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Uuid);
        GETTER_SETTER(Type);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(YHeadRot);
        GETTER_SETTER(Xd);
        GETTER_SETTER(Yd);
        GETTER_SETTER(Zd);
#if PROTOCOL_VERSION < 573 /* < 1.15 */
        GETTER_SETTER(RawMetadata);
#endif
    };
} //ProtocolCraft
#endif
