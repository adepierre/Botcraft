#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundClientIntentionPacket : public BaseMessage<ServerboundClientIntentionPacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Client Intention";

        DECLARE_FIELDS_TYPES(VarInt         , std::string, unsigned short, VarInt);
        DECLARE_FIELDS_NAMES(ProtocolVersion, HostName   , Port          , Intention);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ProtocolVersion);
        GETTER_SETTER(HostName);
        GETTER_SETTER(Port);
        GETTER_SETTER(Intention);
    };
} //ProtocolCraft
