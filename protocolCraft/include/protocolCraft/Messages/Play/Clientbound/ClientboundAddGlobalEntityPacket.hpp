#if PROTOCOL_VERSION < 721 /* < 1.16 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddGlobalEntityPacket : public BaseMessage<ClientboundAddGlobalEntityPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Global Entity";

        DECLARE_FIELDS(
            (VarInt, char, double, double, double),
            (Id_,    Type, X,      Y,      Z)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Type);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
    };
} //ProtocolCraft
#endif
