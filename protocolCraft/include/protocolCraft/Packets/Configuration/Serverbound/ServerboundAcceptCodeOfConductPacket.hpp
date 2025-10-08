#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundAcceptCodeOfConductPacket : public BasePacket<ServerboundAcceptCodeOfConductPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Accept Code Of Conduct";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
