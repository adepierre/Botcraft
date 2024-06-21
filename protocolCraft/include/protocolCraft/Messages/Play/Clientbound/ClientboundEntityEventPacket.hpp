#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundEntityEventPacket : public BaseMessage<ClientboundEntityEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Entity Event";

        DECLARE_FIELDS(
            (int,      char),
            (EntityId, EventId)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(EventId);
    };
} //ProtocolCraft
