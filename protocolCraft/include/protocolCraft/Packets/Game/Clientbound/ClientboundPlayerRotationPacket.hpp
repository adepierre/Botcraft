#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerRotationPacket : public BasePacket<ClientboundPlayerRotationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Rotation";

        SERIALIZED_FIELD(YRot, float);
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        SERIALIZED_FIELD(RelativeY, bool);
#endif
        SERIALIZED_FIELD(XRot, float);
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
        SERIALIZED_FIELD(RelativeX, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
