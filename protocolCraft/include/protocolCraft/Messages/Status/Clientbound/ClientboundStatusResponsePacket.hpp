#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundStatusResponsePacket : public BaseMessage<ClientboundStatusResponsePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Status Response";

        DECLARE_FIELDS(
            (std::string),
            (Status)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Status);
    };
} //ProtocolCraft
