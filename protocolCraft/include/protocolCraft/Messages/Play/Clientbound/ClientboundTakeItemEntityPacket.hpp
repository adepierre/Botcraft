#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTakeItemEntityPacket : public BaseMessage<ClientboundTakeItemEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Take Item Entity";

        SERIALIZED_FIELD(ItemId, VarInt);
        SERIALIZED_FIELD(PlayerId, VarInt);
        SERIALIZED_FIELD(Amount, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
