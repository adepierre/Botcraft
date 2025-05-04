#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundPongResponseStatusPacket : public BasePacket<ClientboundPongResponseStatusPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Pong Response (Status)";

        SERIALIZED_FIELD(Time, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
