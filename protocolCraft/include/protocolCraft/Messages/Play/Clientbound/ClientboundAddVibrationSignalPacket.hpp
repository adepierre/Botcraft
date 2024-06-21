#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"

namespace ProtocolCraft
{
    class ClientboundAddVibrationSignalPacket : public BaseMessage<ClientboundAddVibrationSignalPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Add Vibration Signal";

        DECLARE_FIELDS(
            (VibrationPath),
            (VibrationPath)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(VibrationPath);
    };
} //ProtocolCraft
#endif
