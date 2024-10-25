#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerSlotStateChangedPacket : public BaseMessage<ServerboundContainerSlotStateChangedPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Slot State Changed";

        SERIALIZED_FIELD(SlotId, VarInt);
        SERIALIZED_FIELD(ContainerId, VarInt);
        SERIALIZED_FIELD(NewState, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
