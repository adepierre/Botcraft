#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStepPacket : public BasePacket<ClientboundTickingStepPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Ticking Step";

        SERIALIZED_FIELD(TickingSteps, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
