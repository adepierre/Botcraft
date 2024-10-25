#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStatePacket : public BaseMessage<ClientboundTickingStatePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ticking State";

        SERIALIZED_FIELD(TickRate, float);
        SERIALIZED_FIELD(IsFrozen, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
