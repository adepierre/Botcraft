#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStatePacket : public BaseMessage<ClientboundTickingStatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x6E;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x71;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Ticking State";

        DECLARE_FIELDS_TYPES(float,    bool);
        DECLARE_FIELDS_NAMES(TickRate, IsFrozen);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TickRate);
        GETTER_SETTER(IsFrozen);
    };
} //ProtocolCraft
#endif
