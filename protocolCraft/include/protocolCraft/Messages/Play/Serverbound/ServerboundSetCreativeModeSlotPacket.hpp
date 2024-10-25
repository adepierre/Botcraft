#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCreativeModeSlotPacket : public BaseMessage<ServerboundSetCreativeModeSlotPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Creative Mode Slot";

        SERIALIZED_FIELD(SlotNum, short);
        SERIALIZED_FIELD(ItemStack, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
