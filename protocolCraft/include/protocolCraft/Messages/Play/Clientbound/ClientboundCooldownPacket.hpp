#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCooldownPacket : public BaseMessage<ClientboundCooldownPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Cooldown";

        DECLARE_FIELDS(
            (VarInt, VarInt),
            (Item,   Duration)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Item);
        GETTER_SETTER(Duration);
    };
} //ProtocolCraft
