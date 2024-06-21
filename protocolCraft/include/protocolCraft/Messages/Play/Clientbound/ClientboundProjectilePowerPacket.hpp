#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundProjectilePowerPacket : public BaseMessage<ClientboundProjectilePowerPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Projectile Power";

#if PROTOCOL_VERSION < 767 /* < 1.21 */
        DECLARE_FIELDS(
            (VarInt, double, double, double),
            (Id_,    XPower, YPower, ZPower)
        );
#else
        DECLARE_FIELDS(
            (VarInt, double),
            (Id_,    AccelerationPower)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
#if PROTOCOL_VERSION < 767 /* < 1.21 */
        GETTER_SETTER(XPower);
        GETTER_SETTER(YPower);
        GETTER_SETTER(ZPower);
#else
        GETTER_SETTER(AccelerationPower);
#endif
    };
} //ProtocolCraft
#endif
