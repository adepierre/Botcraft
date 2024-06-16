#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundContainerSlotStateChangedPacket : public BaseMessage<ServerboundContainerSlotStateChangedPacket>
    {
    public:
#if   PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x10;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Slot State Changed";

        DECLARE_FIELDS_TYPES(VarInt, VarInt,      bool);
        DECLARE_FIELDS_NAMES(SlotId, ContainerId, NewState);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SlotId);
        GETTER_SETTER(ContainerId);
        GETTER_SETTER(NewState);
    };
} //ProtocolCraft
#endif
