#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityMotionPacket : public BaseMessage<ClientboundSetEntityMotionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Entity Motion";

        DECLARE_FIELDS(
            (VarInt, short, short, short),
            (Id_,    XA,    YA,    ZA)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(XA);
        GETTER_SETTER(YA);
        GETTER_SETTER(ZA);
    };
} //ProtocolCraft
