#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerAckPacket : public BaseMessage<ClientboundContainerAckPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Ack";

        SERIALIZED_FIELD(ContainerId, char);
        SERIALIZED_FIELD(Uid, short);
        SERIALIZED_FIELD(Accepted, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
