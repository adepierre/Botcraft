#if PROTOCOL_VERSION > 768 /* > 1.21.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerLoadedPacket : public BasePacket<ServerboundPlayerLoadedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Loaded";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
