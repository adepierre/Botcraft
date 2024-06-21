#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerPositionPacket : public BaseMessage<ClientboundPlayerPositionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Position";

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (double, double, double, float, float, char,              VarInt),
            (X,      Y,      Z,      YRot,  XRot,  RelativeArguments, Id_)
        );
#elif PROTOCOL_VERSION < 762 /* < 1.19.4 */
        DECLARE_FIELDS(
            (double, double, double, float, float, char,              VarInt, bool),
            (X,      Y,      Z,      YRot,  XRot,  RelativeArguments, Id_,    DismountVehicle)
        );
#else
        DECLARE_FIELDS(
            (double, double, double, float, float, char,              VarInt),
            (X,      Y,      Z,      YRot,  XRot,  RelativeArguments, Id_)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(YRot);
        GETTER_SETTER(XRot);
        GETTER_SETTER(RelativeArguments);
        GETTER_SETTER(Id_);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 762 /* < 1.19.4 */
        GETTER_SETTER(DismountVehicle);
#endif
    };
}
