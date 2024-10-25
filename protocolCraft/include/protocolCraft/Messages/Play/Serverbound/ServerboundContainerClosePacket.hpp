#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerClosePacket : public BaseMessage<ServerboundContainerClosePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Close";

        SERIALIZED_FIELD(ContainerId, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
