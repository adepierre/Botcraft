#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundProjectilePowerPacket : public BasePacket<ClientboundProjectilePowerPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Projectile Power";

        SERIALIZED_FIELD(Id_, VarInt);
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        SERIALIZED_FIELD(XPower, double);
        SERIALIZED_FIELD(YPower, double);
        SERIALIZED_FIELD(ZPower, double);
#else
        SERIALIZED_FIELD(AccelerationPower, double);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
