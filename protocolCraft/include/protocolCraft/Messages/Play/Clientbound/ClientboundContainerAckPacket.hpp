#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerAckPacket : public BaseMessage<ClientboundContainerAckPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Ack";

        DECLARE_FIELDS(
            (char,        short, bool),
            (ContainerId, Uid,   Accepted)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Uid);
        GETTER_SETTER(Accepted);
    };
} //ProtocolCraft
#endif
