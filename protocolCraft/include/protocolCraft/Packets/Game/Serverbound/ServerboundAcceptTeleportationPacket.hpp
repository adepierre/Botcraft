#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundAcceptTeleportationPacket : public BasePacket<ServerboundAcceptTeleportationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Accept Teleportation";

        SERIALIZED_FIELD(Id_, VarInt);
#if PROTOCOL_VERSION > 776 /* > 26.2 */
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
