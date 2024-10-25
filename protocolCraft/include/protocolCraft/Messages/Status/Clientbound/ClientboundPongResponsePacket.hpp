#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPongResponseStatusPacket : public BaseMessage<ClientboundPongResponseStatusPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Pong Response (Status)";

        SERIALIZED_FIELD(Time, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
