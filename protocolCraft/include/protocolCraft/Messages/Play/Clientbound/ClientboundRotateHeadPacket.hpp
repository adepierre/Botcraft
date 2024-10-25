#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRotateHeadPacket : public BaseMessage<ClientboundRotateHeadPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Rotate Head";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(YHeadRot, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
