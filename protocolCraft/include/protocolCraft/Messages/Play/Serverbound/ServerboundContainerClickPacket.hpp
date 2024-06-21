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

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (unsigned char, short,   char,      short, VarInt,    Slot),
            (ContainerId,   SlotNum, ButtonNum, Uid,   ClickType, CarriedItem)
        );
#elif PROTOCOL_VERSION < 756 /* < 1.17.1 */
        DECLARE_FIELDS(
            (unsigned char, short,   char,      VarInt,    std::map<short, Slot>, Slot),
            (ContainerId,   SlotNum, ButtonNum, ClickType, ChangedSlots,          CarriedItem)
        );
#else
        DECLARE_FIELDS(
            (unsigned char, VarInt,  short,   char,      VarInt,    std::map<short, Slot>, Slot),
            (ContainerId,   StateId, SlotNum, ButtonNum, ClickType, ChangedSlots,          CarriedItem)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(SlotNum);
        GETTER_SETTER(ButtonNum);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(Uid);
#endif
        GETTER_SETTER(ClickType);
        GETTER_SETTER(CarriedItem);
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        GETTER_SETTER(ChangedSlots);
#endif
#if PROTOCOL_VERSION > 755 /* > 1.17 */
        GETTER_SETTER(StateId);
#endif
    };
} //ProtocolCraft
