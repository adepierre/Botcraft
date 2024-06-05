#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStatusResponsePacket : public BaseMessage<ClientboundStatusResponsePacket>
    {
    public:
        static constexpr int packet_id = 0x00;
        static constexpr std::string_view packet_name = "Status Response";

        DECLARE_FIELDS_TYPES(std::string);
        DECLARE_FIELDS_NAMES(Status);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Status);
    };
} //ProtocolCraft
