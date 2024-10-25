#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestStatusPacket : public BaseMessage<ServerboundPingRequestStatusPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ping Request (Status)";

        SERIALIZED_FIELD(Time, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
