#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundTickingStepPacket : public BaseMessage<ClientboundTickingStepPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x6F;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x72;
#else
#error "Protocol version not implemented"
#endif

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
