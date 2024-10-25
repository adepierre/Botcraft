#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTeleportEntityPacket : public BaseMessage<ClientboundTeleportEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Teleport Entity";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, unsigned char);
        SERIALIZED_FIELD(XRot, unsigned char);
        SERIALIZED_FIELD(OnGround, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
