#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundAnimatePacket : public BasePacket<ClientboundAnimatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Animate";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Action, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
