#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCooldownPacket : public BaseMessage<ClientboundCooldownPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Cooldown";

        SERIALIZED_FIELD(Item, VarInt);
        SERIALIZED_FIELD(Duration, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
