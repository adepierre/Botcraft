#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestPacket : public BaseMessage<ServerboundPingRequestPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Ping Request";

        DECLARE_FIELDS(
            (long long int),
            (Time)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Time);
    };
} //ProtocolCraft
#endif
