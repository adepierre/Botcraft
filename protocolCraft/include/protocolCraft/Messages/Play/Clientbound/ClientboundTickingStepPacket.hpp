#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStepPacket : public BaseMessage<ClientboundTickingStepPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Ticking Step";

        DECLARE_FIELDS(
            (VarInt),
            (TickingSteps)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TickingSteps);
    };
} //ProtocolCraft
#endif
