#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTakeItemEntityPacket : public BaseMessage<ClientboundTakeItemEntityPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Take Item Entity";

        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt),
            (ItemId, PlayerId, Amount)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ItemId);
        GETTER_SETTER(PlayerId);
        GETTER_SETTER(Amount);
    };
} //ProtocolCraft
