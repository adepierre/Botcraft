#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerRotationPacket : public BaseMessage<ClientboundPlayerRotationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Rotation";

        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
