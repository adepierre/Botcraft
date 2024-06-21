#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHurtAnimationPacket : public BaseMessage<ClientboundHurtAnimationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Hurt Animation";

        DECLARE_FIELDS(
            (VarInt, float),
            (Id_, Yaw)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Yaw);
    };
} //ProtocolCraft
#endif
