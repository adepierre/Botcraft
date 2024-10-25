#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetDataPacket : public BaseMessage<ClientboundContainerSetDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Set Data";

        SERIALIZED_FIELD(ContainerId, unsigned char);
        SERIALIZED_FIELD(Id_, short);
        SERIALIZED_FIELD(Value, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
