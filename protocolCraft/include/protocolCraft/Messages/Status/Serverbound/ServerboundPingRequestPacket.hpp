#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestStatusPacket : public BaseMessage<ServerboundPingRequestStatusPacket>
    {
    public:
        static constexpr int packet_id = 0x01;
        static constexpr std::string_view packet_name = "Ping Request (Status)";

        DECLARE_FIELDS(
            (long long int),
            (Time)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Time);
    };
} // ProtocolCraft
