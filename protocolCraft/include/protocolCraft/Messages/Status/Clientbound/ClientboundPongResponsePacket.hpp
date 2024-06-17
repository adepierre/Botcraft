#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPongResponseStatusPacket : public BaseMessage<ClientboundPongResponseStatusPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Pong Response (Status)";

        DECLARE_FIELDS(
            (long long int),
            (Time)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Time);
    };
} //ProtocolCraft
