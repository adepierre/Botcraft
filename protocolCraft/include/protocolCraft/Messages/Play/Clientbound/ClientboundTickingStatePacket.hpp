#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStatePacket : public BaseMessage<ClientboundTickingStatePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Ticking State";

        DECLARE_FIELDS(
            (float,    bool),
            (TickRate, IsFrozen)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TickRate);
        GETTER_SETTER(IsFrozen);
    };
} //ProtocolCraft
#endif
