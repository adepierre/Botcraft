#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPingRequestPacket : public BaseMessage<ServerboundPingRequestPacket>
    {
    public:
#if PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x21;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ping Request";

        DECLARE_FIELDS_TYPES(long long int);
        DECLARE_FIELDS_NAMES(Time);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Time);
    };
} //ProtocolCraft
#endif
