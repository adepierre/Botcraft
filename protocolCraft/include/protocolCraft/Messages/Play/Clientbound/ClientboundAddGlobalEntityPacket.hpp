#if PROTOCOL_VERSION < 721 /* < 1.16 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddGlobalEntityPacket : public BaseMessage<ClientboundAddGlobalEntityPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */ || PROTOCOL_VERSION == 393 /* 1.13 */ ||  \
      PROTOCOL_VERSION == 401 /* 1.13.1 */ || PROTOCOL_VERSION == 404 /* 1.13.2 */ ||  \
      PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x02;
#else
#error "Protocol version not implemented"
#endif

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
