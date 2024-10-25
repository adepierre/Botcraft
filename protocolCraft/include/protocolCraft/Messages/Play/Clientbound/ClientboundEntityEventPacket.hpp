#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundEntityEventPacket : public BaseMessage<ClientboundEntityEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Entity Event";

        SERIALIZED_FIELD(EntityId, int);
        SERIALIZED_FIELD(EventId, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
