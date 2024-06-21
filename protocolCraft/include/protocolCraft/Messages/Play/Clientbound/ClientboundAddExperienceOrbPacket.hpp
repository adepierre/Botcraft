#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddExperienceOrbPacket : public BaseMessage<ClientboundAddExperienceOrbPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Experience Orb";

        DECLARE_FIELDS(
            (VarInt, double, double, double, short),
            (Id_,    X,      Y,      Z,      Value)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(Value);
    };
} //ProtocolCraft
