#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientIntentionPacket : public BaseMessage<ServerboundClientIntentionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Client Intention";

        DECLARE_FIELDS(
            (VarInt         , std::string, unsigned short, VarInt),
            (ProtocolVersion, HostName   , Port          , Intention)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ProtocolVersion);
        GETTER_SETTER(HostName);
        GETTER_SETTER(Port);
        GETTER_SETTER(Intention);
    };
} //ProtocolCraft
