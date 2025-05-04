#if PROTOCOL_VERSION > 754 /* > 1.16.5 */ && PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Vibrations/VibrationPath.hpp"

namespace ProtocolCraft
{
    class ClientboundAddVibrationSignalPacket : public BasePacket<ClientboundAddVibrationSignalPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Vibration Signal";

        SERIALIZED_FIELD(VibrationPath, ProtocolCraft::VibrationPath);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
