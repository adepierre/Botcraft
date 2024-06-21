#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerSlotStateChangedPacket : public BaseMessage<ServerboundContainerSlotStateChangedPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Container Slot State Changed";

        DECLARE_FIELDS(
            (VarInt, VarInt,      bool),
            (SlotId, ContainerId, NewState)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SlotId);
        GETTER_SETTER(ContainerId);
        GETTER_SETTER(NewState);
    };
} //ProtocolCraft
#endif
