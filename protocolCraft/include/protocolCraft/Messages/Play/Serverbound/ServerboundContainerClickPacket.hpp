#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include <map>
#endif

namespace ProtocolCraft
{
    class ServerboundContainerClickPacket : public BaseMessage<ServerboundContainerClickPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Click";

        SERIALIZED_FIELD(ContainerId, unsigned char);
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        SERIALIZED_FIELD(StateId, VarInt);
#endif
        SERIALIZED_FIELD(SlotNum, short);
        SERIALIZED_FIELD(ButtonNum, char);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(Uid, short);
#endif
        SERIALIZED_FIELD(ClickType, VarInt);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SERIALIZED_FIELD(ChangedSlots, std::map<short, Slot>);
#endif
        SERIALIZED_FIELD(CarriedItem, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
