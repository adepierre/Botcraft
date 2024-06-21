#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerSetDataPacket : public BaseMessage<ClientboundContainerSetDataPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Set Data";

        DECLARE_FIELDS(
            (unsigned char, short, short),
            (ContainerId,   Id_,   Value)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Id_);
        GETTER_SETTER(Value);
    };
} //ProtocolCraft
