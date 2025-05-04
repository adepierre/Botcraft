#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundRotateHeadPacket : public BasePacket<ClientboundRotateHeadPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Rotate Head";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(YHeadRot, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
