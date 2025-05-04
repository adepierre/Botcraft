#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTimePacket : public BasePacket<ClientboundSetTimePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Time";

        SERIALIZED_FIELD(GameTime, long long int);
        SERIALIZED_FIELD(DayTime, long long int);
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SERIALIZED_FIELD(TickDayTime, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
