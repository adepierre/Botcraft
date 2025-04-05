#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/HashedSlot.hpp"
#endif
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#include <map>
#endif

namespace ProtocolCraft
{
    class ServerboundContainerClickPacket : public BaseMessage<ServerboundContainerClickPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Container Click";

#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(ContainerId, unsigned char);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        SERIALIZED_FIELD(StateId, VarInt);
#endif
        SERIALIZED_FIELD(SlotNum, short);
        SERIALIZED_FIELD(ButtonNum, char);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(Uid, short);
#endif
        SERIALIZED_FIELD(ClickType, VarInt);
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SERIALIZED_FIELD(ChangedSlots, std::map<short, Slot>);
#endif
        SERIALIZED_FIELD(CarriedItem, Slot);
#else
        SERIALIZED_FIELD(ChangedSlots, std::map<short, HashedSlot>);
        SERIALIZED_FIELD(CarriedItem, HashedSlot);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
