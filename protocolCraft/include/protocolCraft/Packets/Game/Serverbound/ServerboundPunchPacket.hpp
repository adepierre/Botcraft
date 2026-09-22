#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundPunchPacket : public BasePacket<ServerboundPunchPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Punch";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
