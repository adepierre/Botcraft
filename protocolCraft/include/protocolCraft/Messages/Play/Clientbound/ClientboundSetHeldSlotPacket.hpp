#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHeldSlotPacket : public BaseMessage<ClientboundSetHeldSlotPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Held Slot";

#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
        SERIALIZED_FIELD(Slot, char);
#else
        SERIALIZED_FIELD(Slot, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
