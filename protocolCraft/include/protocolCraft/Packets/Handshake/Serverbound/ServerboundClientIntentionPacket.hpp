#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundClientIntentionPacket : public BasePacket<ServerboundClientIntentionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Client Intention";

        SERIALIZED_FIELD(ProtocolVersion, VarInt);
        SERIALIZED_FIELD(HostName, std::string);
        SERIALIZED_FIELD(Port, unsigned short);
        SERIALIZED_FIELD(Intention, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
