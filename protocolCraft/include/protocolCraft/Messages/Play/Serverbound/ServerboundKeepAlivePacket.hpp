#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundKeepAlivePacket : public BaseMessage<ServerboundKeepAlivePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Keep Alive";

        SERIALIZED_FIELD(Id_, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
