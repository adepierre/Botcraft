#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestStatusPacket : public BasePacket<ServerboundPingRequestStatusPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ping Request (Status)";

        SERIALIZED_FIELD(Time, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
