#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAnimatePacket : public BaseMessage<ClientboundAnimatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Animate";

        DECLARE_FIELDS(
            (VarInt, unsigned char),
            (Id_,    Action)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Action);
    };
} //ProtocolCraft
