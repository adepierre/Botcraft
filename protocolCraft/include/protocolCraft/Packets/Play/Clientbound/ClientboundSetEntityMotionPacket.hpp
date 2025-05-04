#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityMotionPacket : public BasePacket<ClientboundSetEntityMotionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity Motion";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(XA, short);
        SERIALIZED_FIELD(YA, short);
        SERIALIZED_FIELD(ZA, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
