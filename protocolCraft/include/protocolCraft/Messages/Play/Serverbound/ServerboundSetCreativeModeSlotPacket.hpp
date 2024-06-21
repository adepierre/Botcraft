#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCreativeModeSlotPacket : public BaseMessage<ServerboundSetCreativeModeSlotPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Creative Mode Slot";

        DECLARE_FIELDS(
            (short,   Slot),
            (SlotNum, ItemStack)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(SlotNum);
        GETTER_SETTER(ItemStack);
    };
} //ProtocolCraft
