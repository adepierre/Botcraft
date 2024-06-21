#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRotateHeadPacket : public BaseMessage<ClientboundRotateHeadPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Rotate Head";

        DECLARE_FIELDS(
            (VarInt,   unsigned char),
            (EntityId, YHeadRot)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(EntityId);
        GETTER_SETTER(YHeadRot);
    };
} //ProtocolCraft
