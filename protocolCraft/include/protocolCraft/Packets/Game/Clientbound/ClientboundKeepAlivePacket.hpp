#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundKeepAlivePacket : public BasePacket<ClientboundKeepAlivePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Keep Alive";

        SERIALIZED_FIELD(Id_, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
