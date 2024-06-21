#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTeleportEntityPacket : public BaseMessage<ClientboundTeleportEntityPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Teleport Entity";

        DECLARE_FIELDS(
            (VarInt, double, double, double, unsigned char, unsigned char, bool),
            (Id_,    X,      Y,      Z,      YRot,          XRot,          OnGround)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(OnGround);
    };
} //ProtocolCraft
