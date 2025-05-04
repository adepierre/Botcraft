#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundHurtAnimationPacket : public BasePacket<ClientboundHurtAnimationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Hurt Animation";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Yaw, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
