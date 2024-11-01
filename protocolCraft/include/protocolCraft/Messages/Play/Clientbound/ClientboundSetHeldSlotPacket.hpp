#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHeldSlotPacket : public BaseMessage<ClientboundSetHeldSlotPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Held Slot";

        SERIALIZED_FIELD(Slot, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
