#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerClosePacket : public BaseMessage<ServerboundContainerClosePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Close";

        DECLARE_FIELDS(
            (unsigned char),
            (ContainerId)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
    };
} //ProtocolCraft
