#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#include <array>
#endif

namespace ProtocolCraft
{
    class ServerboundMoveVehiclePacket : public BaseMessage<ServerboundMoveVehiclePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Move Vehicle";

#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
#else
        SERIALIZED_FIELD(Position, std::array<double, 3>);
#endif
        SERIALIZED_FIELD(YRot, float);
        SERIALIZED_FIELD(XRot, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
